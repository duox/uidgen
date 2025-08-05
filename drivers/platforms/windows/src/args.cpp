/*args.cpp*/
/** @file
 *
 * @brief Command line management.
 * SPDX-License-Identifier: MIT
 *
 *	Valid both for console and GUI versions.
 */
#include "pch.h"
#include "main.h"

#define STR_LEN_PAIR(str)	str, countof(str) - 1

static void SwtHelp( INT ArgCount, LPCSTR * Args, INT * ArgIndex );
static void SwtConsole( INT ArgCount, LPCSTR * Args, INT * ArgIndex );
static void SwtFormat( INT ArgCount, LPCSTR * Args, INT * ArgIndex );
static void SwtGUI( INT ArgCount, LPCSTR * Args, INT * ArgIndex );
static void SwtNumber( INT ArgCount, LPCSTR * Args, INT * ArgIndex );
static void SwtString( INT ArgCount, LPCSTR * Args, INT * ArgIndex );
static void SwtType( INT ArgCount, LPCSTR * Args, INT * ArgIndex );
static void SwtUser( INT ArgCount, LPCSTR * Args, INT * ArgIndex );
static void SwtVersion( INT ArgCount, LPCSTR * Args, INT * ArgIndex );
static void SwtZeroes( INT ArgCount, LPCSTR * Args, INT * ArgIndex );

/**
 * @brief List of all supported switches.
 */
static const struct SWITCH_DESC {
	const char * Name;
	SIZE_T		Len;
	void (* Pfn)( INT ArgCount, LPCSTR * Args, INT * ArgIndex );
} SwtDesc[] = 
{
	{ STR_LEN_PAIR("?"),		SwtHelp },		{ STR_LEN_PAIR("h"),		SwtHelp },	{ STR_LEN_PAIR("-help"), SwtHelp },
	{ STR_LEN_PAIR("-console"),	SwtConsole },
	{ STR_LEN_PAIR("f"),		SwtFormat },	{ STR_LEN_PAIR("-format"),	SwtFormat },
	{ STR_LEN_PAIR("-gui"),		SwtGUI },
	{ STR_LEN_PAIR("n"),		SwtNumber },	{ STR_LEN_PAIR("-number"),	SwtNumber },
	{ STR_LEN_PAIR("s"),		SwtString },	{ STR_LEN_PAIR("-string"),	SwtString },
	{ STR_LEN_PAIR("t"),		SwtType },		{ STR_LEN_PAIR("-type"),	SwtType },
	{ STR_LEN_PAIR("u"),		SwtType },		{ STR_LEN_PAIR("-user"),	SwtUser },
	{ STR_LEN_PAIR("-version"),	SwtVersion },
	{ STR_LEN_PAIR("z"),		SwtZeroes },	{ STR_LEN_PAIR("-zeroes"),	SwtZeroes },
};

/**
 * @brief Process command line switch at the specified position.
 * @param[in] ArgCount (INT) number of arguments.
 * @param[in] Args (LPCSTR *) pointer to array of arguments.
 * @param[in] ArgIndex (INT *) index of the currently processed argument.
 */
static void ProcessSwitch( INT ArgCount, LPCSTR * Args, INT * ArgIndex )
{
#if 1
	LPCSTR Switch = Args[*ArgIndex];
	SIZE_T ArgLen = uidgen::string::length( Switch, (size_t) -1 ) - 1;
	for( SIZE_T i = 0; i < countof( SwtDesc ); ++ i )
	{
		if( SwtDesc[i].Len == ArgLen && uidgen::memory::equal( Switch + 1, SwtDesc[i].Name, SwtDesc[i].Len ) )
		{
			SwtDesc[i].Pfn( ArgCount, Args, ArgIndex );
			return;
		}
	}

	ConsolePrint( "Unknown switch: -", (SIZE_T) -1 );
	ConsolePrint( Switch, (SIZE_T) -1 );
	ConsolePrint( ".\n", 2 );
	gSystemFlags |= SF_REQUEST_EXIT;

	return;
#else
	LPCSTR Switch = Args[*ArgIndex];
	SSIZE_T BestLen = - 1;
	SSIZE_T BestIndex = -1;
	for( SIZE_T i = 0; i < countof( SwtDesc ); ++ i )
	{
		if( 0 == RtlMemoryCompare( Switch, SwtDesc[i].Name, SwtDesc[i].Len ) && SwtDesc[i].Len > BestLen )
		{
			BestLen = SwtDesc[i].Len;
			BestIndex = i;
		}
	}

	if( -1 == BestIndex )
	{
		ConsolePrint( "Unknown switch: -", (SIZE_T) -1 );
		ConsolePrint( Switch, (SIZE_T) -1 );
		return;
	}

	if( '=' == Switch[BestLen] )
		++ BestLen;
	SwtDesc[BestIndex].Pfn( Switch + BestLen );
#endif
}

/**
 * @brief Process command line file name.
 * @param[in] FileName (LPCSTR) pointer to file name.
 */
static void ProcessFileName( LPCSTR FileName )
{
	ConsolePrint( "Unsupported parameter: ", (SIZE_T) -1 );
	ConsolePrint( FileName, (SIZE_T) -1 );
	ConsolePrint( ".\n", 1 );
	gSystemFlags |= SF_REQUEST_EXIT;
}

/**
 * @brief Process command line arguments.
 * @param[in] ArgCount (INT) number of arguments.
 * @param[in] Args (LPCSTR *) pointer to array of arguments.
 */
void ProcessCmdLineArgs( INT ArgCount, LPCSTR * Args )
{
	for( INT i = 1; i < ArgCount; ++ i )
	{
		if( '-' == *Args[i] )
			ProcessSwitch( ArgCount, Args, &i );
		else
			ProcessFileName( Args[i] );
	}
	return;
}

static const char HelpText[] =
"UIDgen version " UIDGEN_VERSION ". Copyright 2025 duox, licensed under MIT.\n"
"Usage: uidgen [{switch [param]}]\n"
"Switches:\n"
" -? -h --help\t: display command line help and exit.\n"
"    --console\t: launch console version (reverst --gui).\n"
" -f --format\t: specify GUID format type (see below).\n"
"    --format dump\t: dump all supported formats.\n"
"    --format list\t: list all supported formats.\n"
"    --format help\t: display user format string help.\n"
"    --gui\t: launch GUI version (reverst --console).\n"
" -n --number\t: generate specified number of guids: -n 10.\n"
" -s --string\t: specify GUID format string (see below).\n"
" -t --type\t: specify GUID source type.\n"
"    --type dump\t: dump all GUID source type.\n"
"    --type list\t: list all GUID source type.\n"
" -u --user\t: specify user GUID string in braced format.\n"
"    --version\t: display program version and exit.\n"
" -z --zeroes\t: remove leading zeroes.\n"
"For more information, please refer to https://github.com/duox/uidgen\n"
;
static void SwtHelp( INT ArgCount, LPCSTR * Args, INT * ArgIndex )
{
	ConsolePrint( HelpText, countof(HelpText) - 1 );
	gSystemFlags |= SF_REQUEST_EXIT | SF_HELP_PRINTED;

	UNREFERENCED_PARAMETER( ArgCount );
	UNREFERENCED_PARAMETER( Args );
	UNREFERENCED_PARAMETER( ArgIndex );
	return;
}
static void SwtConsole( INT ArgCount, LPCSTR * Args, INT * ArgIndex )
{
	gSystemFlags |= SF_FORCE_CONSOLE;
	gSystemFlags &= ~SF_FORCE_GUI;

	UNREFERENCED_PARAMETER( ArgCount );
	UNREFERENCED_PARAMETER( Args );
	UNREFERENCED_PARAMETER( ArgIndex );
	return;
}
static void SwtGUI( INT ArgCount, LPCSTR * Args, INT * ArgIndex )
{
	gSystemFlags |= SF_FORCE_GUI;
	gSystemFlags &= ~SF_FORCE_CONSOLE;

	UNREFERENCED_PARAMETER( ArgCount );
	UNREFERENCED_PARAMETER( Args );
	UNREFERENCED_PARAMETER( ArgIndex );
	return;
}

static const char sz_format_help[] =
"Format string consists of format specifiers and ordinal characters.\n"
"Specifiers use %{flags width spec index} format and listed below:\n"
" B\t: upper case 8-bit value.\tb\t: lower case 8-bit value.\n"
" W\t: upper case 16-bit value.\tw\t: lower case 16-bit value\n"
" D\t: upper case 32-bit value.\td\t: lower case 32-bit value.\n"
" i\t: GUID index (for multi-GUID sequences).\n"
" s\t: string value (index parameter is not used).\n"
"Specifier flags\n"
" 0\t: print leading zeroes.\n"
"Index follows numeric type specifier: 0..16 for B/b, 0..8 for W/w, 0..4 for D/d\n"
"Example usage: %{04B1} - display 1st byte in 4-char field with leading zeroes.\n"
;
static void SwtFormat( INT ArgCount, LPCSTR * Args, INT * ArgIndex )
{
	LPCSTR Format;

	if( *ArgIndex + 1 >= ArgCount )
	{
		ConsolePrint( "--format: format id argument required.\n", (SIZE_T) - 1 );
		gSystemFlags |= SF_REQUEST_EXIT;
		return;
	}

	++ *ArgIndex;
	Format = Args[*ArgIndex];
	SIZE_T FormatLength = uidgen::string::length( Format );

	if( 4 == FormatLength )
	{
		if( uidgen::memory::equal( Format, "list", FormatLength ) )
		{
			for( uidgen::formatter_list_t::const_iterator it = g_uidgen_context->get_formatter_list().begin(), st = g_uidgen_context->get_formatter_list().end(); it != st; ++ it )
			{
				uidgen::string buf;
				(*it)->get_string( buf, uidgen::Iformatter::sid_name );

				ConsolePrint( buf.c_str(), (SIZE_T) -1 );
				ConsolePrint( "\n", 1 );
			}
		}
		else if( uidgen::memory::equal( Format, "dump", FormatLength ) )
		{
			for( uidgen::formatter_list_t::const_iterator it = g_uidgen_context->get_formatter_list().begin(), st = g_uidgen_context->get_formatter_list().end(); it != st; ++ it )
			{
				uidgen::string name;
				(*it)->get_string( name, uidgen::Iformatter::sid_name );
				uidgen::string desc;
				(*it)->get_string( desc, uidgen::Iformatter::sid_description );

				ConsolePrint( name.c_str(), name.length() );
				ConsolePrint( ": ", 2 );
				ConsolePrint( desc.c_str(), desc.length() );
				ConsolePrint( "\n", 1 );
			}
		}
		else if( uidgen::memory::equal( Format, "help", FormatLength ) )
		{
			ConsolePrint( sz_format_help, countof(sz_format_help) - 1);
		}
	}
	else
	{
		for( uidgen::formatter_list_t::const_iterator it = g_uidgen_context->get_formatter_list().begin(), st = g_uidgen_context->get_formatter_list().end(); it != st; ++ it )
		{
			uidgen::string buf;
			(*it)->get_string( buf, uidgen::Iformatter::sid_name );
			if( FormatLength == buf.length() && uidgen::memory::equal( Format, buf.data(), FormatLength ) )
			{
				g_uidgen_context->set_active_formatter( *it );
				return;
			}
		}

		ConsolePrint( "--format: unknown format: ", (SIZE_T) - 1 );
		ConsolePrint( Format, FormatLength );
		ConsolePrint( "\n", 1 );
	}
	gSystemFlags |= SF_REQUEST_EXIT;

	return;
}
static void SwtNumber( INT ArgCount, LPCSTR * Args, INT * ArgIndex )
{
	++ *ArgIndex;
	if( *ArgIndex >= ArgCount || !uidgen::string::is_digit( *Args[*ArgIndex] ) )
	{
		ConsolePrint( "--format: numeric argument required.\n", (SIZE_T) - 1 );
		gSystemFlags |= SF_REQUEST_EXIT;
		return;
	}

	signed int Count;
	size_t num_parsed = uidgen::string::parse_int32( &Count, Args[*ArgIndex] );
	if( 0 == num_parsed )
	{
		ConsolePrint( "--format: numeric argument required.\n", (SIZE_T) - 1 );
		return;
	}

	g_uidgen_context->set_generation_count( Count );

	return;
}
static void SwtString( INT ArgCount, LPCSTR * Args, INT * ArgIndex )
{
	++ *ArgIndex;
	if( *ArgIndex >= ArgCount )
	{
		ConsolePrint( "--string: argument required.\n", (SIZE_T) - 1 );
		gSystemFlags |= SF_REQUEST_EXIT;
		return;
	}

	g_uidgen_context->set_user_format_string( Args[*ArgIndex] );

	g_uidgen_context->set_active_formatter( g_uidgen_context->find_formatter( uidgen::user_string_formatter::m_uuid ) );

	return;
}
static const char sz_generator_help[] =
""
;
static void SwtType( INT ArgCount, LPCSTR * Args, INT * ArgIndex )
{
	LPCSTR Generator;

	if( *ArgIndex + 1 >= ArgCount )
	{
		ConsolePrint( "--type: generator id argument required.\n", (SIZE_T) - 1 );
		gSystemFlags |= SF_REQUEST_EXIT;
		return;
	}

	++ *ArgIndex;
	Generator = Args[*ArgIndex];
	SIZE_T GeneratorLength = uidgen::string::length( Generator, (SIZE_T) -1 );

	if( 4 == GeneratorLength )
	{
		if( uidgen::memory::equal( Generator, "list", GeneratorLength ) )
		{
			for( uidgen::generator_list_t::const_iterator it = g_uidgen_context->get_generator_list().begin(), st = g_uidgen_context->get_generator_list().end(); it != st; ++ it )
			{
				uidgen::string buf;
				(*it)->get_string( buf, uidgen::Igenerator::sid_name );

				ConsolePrint( buf.c_str(), (SIZE_T) -1 );
				ConsolePrint( "\n", 1 );
			}
		}
		else if( uidgen::memory::equal( Generator, "dump", GeneratorLength ) )
		{
			for( uidgen::generator_list_t::const_iterator it = g_uidgen_context->get_generator_list().begin(), st = g_uidgen_context->get_generator_list().end(); it != st; ++ it )
			{
				uidgen::string name;
				(*it)->get_string( name, uidgen::Igenerator::sid_name );
				uidgen::string desc;
				(*it)->get_string( desc, uidgen::Igenerator::sid_description );

				ConsolePrint( name.c_str(), name.length() );
				ConsolePrint( ": ", 2 );
				ConsolePrint( desc.c_str(), desc.length() );
				ConsolePrint( "\n", 1 );
			}
		}
		else if( uidgen::memory::equal( Generator, "help", GeneratorLength ) )
		{
			ConsolePrint( sz_format_help, countof(sz_generator_help) - 1);
		}
	}
	else
	{
		for( uidgen::generator_list_t::const_iterator it = g_uidgen_context->get_generator_list().begin(), st = g_uidgen_context->get_generator_list().end(); it != st; ++ it )
		{
			uidgen::string buf;
			(*it)->get_string( buf, uidgen::Igenerator::sid_name );
			if( GeneratorLength == buf.length() && uidgen::memory::equal( Generator, buf.data(), GeneratorLength ) )
			{
				g_uidgen_context->set_active_generator( *it );
				return;
			}
		}

		ConsolePrint( "--type: unknown generator: ", (SIZE_T) - 1 );
		ConsolePrint( Generator, GeneratorLength );
		ConsolePrint( "\n", 1 );
	}
	gSystemFlags |= SF_REQUEST_EXIT;

	return;
}
static void SwtUser( INT ArgCount, LPCSTR * Args, INT * ArgIndex )
{
	++ *ArgIndex;
	if( *ArgIndex >= ArgCount )
	{
		ConsolePrint( "--user: argument required.\n", (SIZE_T) - 1 );
		gSystemFlags |= SF_REQUEST_EXIT;
		return;
	}

	g_uidgen_context->set_user_data( Args[*ArgIndex] );

	g_uidgen_context->set_active_generator( g_uidgen_context->find_generator( uidgen::manual_uuid_generator::m_uuid ) );

	return;
}
static void SwtVersion( INT ArgCount, LPCSTR * Args, INT * ArgIndex )
{
	ConsolePrint( UIDGEN_VERSION, countof(UIDGEN_VERSION) - 1 );

	gSystemFlags |= SF_REQUEST_EXIT;	// exit app

	UNREFERENCED_PARAMETER( ArgCount );
	UNREFERENCED_PARAMETER( Args );
	UNREFERENCED_PARAMETER( ArgIndex );
	return;
}
static void SwtZeroes( INT ArgCount, LPCSTR * Args, INT * ArgIndex )
{
	g_uidgen_context->modify_flags( uidgen::context::fl_remove_leading_zeroes );

	UNREFERENCED_PARAMETER( ArgCount );
	UNREFERENCED_PARAMETER( Args );
	UNREFERENCED_PARAMETER( ArgIndex );
	return;
}

/*END OF args.cpp*/
