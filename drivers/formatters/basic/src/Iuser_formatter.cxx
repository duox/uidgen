/*Iuser_formatter.cxx.cpp*/
#include "pch.h"
#include "main.h"

const char * uidgen::Iuser_formatter::get_format_string( uidgen::context & ctx ) const
{
	break_on_purecall();
	unreferenced_parameter( ctx );
	return nullptr;
}
bool uidgen::Iuser_formatter::format( uidgen::string & buf, uidgen::context & ctx, const uidgen::uuid & uid ) const
{
	bool ignore_next_nl = false;
	int forced_upper_case;

	// Check current state
	const char * format_string = get_format_string( ctx );
	if( nullptr == format_string )
		format_string = ctx.get_default_format_string().c_str();
	if( '\0' == *format_string )
		return false;

	if( ctx.get_flags( context::fl_format_upper_case ) )
		forced_upper_case = 1;
	else if( ctx.get_flags( context::fl_format_lower_case ) )
		forced_upper_case = 0;
	else
		forced_upper_case = -1;

	// Format GUID now
	const char * src = format_string, * const src_end = format_string + lstrlen( format_string );
	while( src < src_end )
	{
		if( '%' != *src || '%' == *++ src )
		{
			if( ignore_next_nl )
			{
				if( '\n' == *src )
				{
					++ src;
					if( '\r' == *src )
						++ src;
					ignore_next_nl = false;
					continue;
				}
				if( '\r' == *src )
				{
					++ src;
					if( '\n' == *src )
						++ src;
					ignore_next_nl = false;
					continue;
				}
			}

			if( '\\' == *src )
			{
				int n;
				++ src;
				switch( *src )
				{
				case 'a':	buf.append( '\a' );	break;
				case 'b':	buf.append( '\b' );	break;
				case 'e':	buf.append( 0x1b );	break;	// ESC
				case 'f':	buf.append( '\f' );	break;
				case 'n':	buf.append( '\n' );	break;
				case 'r':	buf.append( '\r' );	break;
				case 't':	buf.append( '\t' );	break;
				case 'v':	buf.append( '\v' );	break;
				case '\\':	buf.append( '\\' );	break;
				case '\'':	buf.append( '\'' );	break;
				case '\"':	buf.append( '\"' );	break;
				case '\?':	buf.append( '\?' );	break;
				case 'N':	buf.append( '\r' );	buf.append( '\n' );	break;
				case 'x':
					++ src;
					n = parse_hex( src, src_end - src, 1, src_end - src, &src );
					if( -1 == n )
						return false;
					buf.append( (char) n );
					continue;
				case 'u':
					++ src;
					n = parse_hex( src, src_end - src, 4, 4, &src );
					if( -1 == n )
						return false;
					buf.append( (char) /*n*/'?' );	// TODO: UTF-16 to ANSI conversion
					continue;
				case 'U':
					++ src;
					n = parse_hex( src, src_end - src, 8, 8, &src );
					if( -1 == n )
						return false;
					buf.append( (char) /*n*/'?' );	// TODO: UTF-32 to ANSI conversion
					continue;
				default:
					if( '0' <= *src && *src <= '7' )
					{
						n = *src++ - '0';
						if( '0' <= *src && *src <= '7' )
						{
							n = n*8 + *src++ - '0';
							if( '0' <= *src && *src <= '7' )
								n = n*8 + *src++ - '0';
						}
						if( n > 255 )
							return false;
						buf.append( (char) n );
						continue;
					}

					return false;
				}
				++ src;
				continue;
			}

			buf.append( *src ++ );
			continue;
		}
		if( '{' != *src )
			return false;
		++ src;

		// Parse width
		signed int width = 0;
		bool leading_zero = false;
		if( string::is_digit( *src ) )
		{
			if( '0' == *src )
				leading_zero = true;
			src += string::parse_int32( &width, src );
			if( 0 > width )
				return false;
		}
		if( !ctx.get_flags( context::fl_remove_leading_zeroes ) )
			leading_zero = true;

		// Get flag
		bool disable_leading_zero = true;
		if( '!' == *src )
		{
			disable_leading_zero = false;
			++ src;
		}

		// Check for generator
/*		if( src[0] == 'g' && src[1] == 'e' && src[2] == 'n' )
		{
			bool res = false;

			src += 3;
			if( *src == '}' )	// default: random generator
			{
				res = generate( guid_type_random, uid, nullptr );
				-- src;
			}
			else if( *src == ':' )
			{
				// Generate GUID according to the type of generator
				src ++;
				switch( *src )
				{
				case 'r':
					res = generate( guid_type_random, uid, nullptr );
					break;
				case '1':
					res = generate( guid_type_ones, guid, nullptr );
					break;
				case '0':
					res = generate( guid_type_null, guid, nullptr );
					break;
				case '{':{
					++ src;

					char bf[128], * p = bf, * bf_end = p + countof(bf) - 1;
					*p ++ = '{';
					while( p < bf_end && ( isalpha( *src ) || isxdigit( *src ) || '-' == *src ) )
						*p ++ = *src ++;
					if( p >= bf_end )
						return false;
					*p ++ = '}';
					*p = '\0';

					if( '}' != *src )
						return false;

					res = generate( guid_type_manual, guid, bf );
				}break;
				default:
					return false;
				}
			}
			if( !res )
				return false;

			// Check for closing brace
			if( '}' != *++ src )
				return false;
			++ src;

			// Remove previous and next new lines
			ignore_next_nl = true;
			if( buf.length() > 0 )
			{
				if( '\n' == *buf.rbegin() )
				{
					pop_back( buf );
					if( '\r' == *buf.rbegin() )
						pop_back( buf );
				}
				else if( '\r' == *buf.rbegin() )
				{
					pop_back( buf );
					if( '\n' == *buf.rbegin() )
						pop_back( buf );
				}
			}

			// Iterate
			continue;
		}
*/
		// Get data type
		int type;
		bool upper_case;
		switch( *src )
		{
		case 'B':	type = 1;	upper_case = true;	break;
		case 'W':	type = 2;	upper_case = true;	break;
		case 'D':	type = 4;	upper_case = true;	break;
		case 'b':	type = 1;	upper_case = false;	break;
		case 'w':	type = 2;	upper_case = false;	break;
		case 'd':	type = 4;	upper_case = false;	break;
		/*case 'i':
		case 'I':
			char temp[64];
			_ultoa( ctx.get_generation_index(), temp, 10);
			buf.append( temp );
			if( '}' != *++src )
				return false;
			++ src;
			continue;*/
		case 's':
		case 'S':
			upper_case = 'S' == *src ++;

			if( ctx.get_flags( context::fl_use_angle_brackets ) )
			{
				buf.append( '<' );
				buf.append( '<' );
			}

			if( '\'' == *src )
			{
				++ src;
				while( src < src_end && '\'' != *src )
					buf.append( *src ++ );
				if( '\'' == *src )
					++ src;
			}

			if( ctx.get_flags( context::fl_use_angle_brackets ) )
			{
				buf.append( '>' );
				buf.append( '>' );
			}

			if( '}' != *src )
				return false;
			++ src;

			continue;
		default:
			return false;
		}
		++ src;
		if( -1 != forced_upper_case )
			upper_case = !!forced_upper_case;

		// Get size
		signed int index = -1;
		if( !string::is_digit( *src ) )
			return false;
		src += string::parse_int32( &index, src );
		if( 0 > index )
			return false;
		if( index >= 16 || type * index >= 16 )
			return false;

		// Skip '}'
		if( '}' != *src )
			return false;
		++ src;

		// Load data
		unsigned long data;
		switch( type )
		{
		case 1:	data = ((const unsigned  char *) &uid)[index];	break;
		case 2:	data = ((const unsigned short *) &uid)[index];	break;
		case 4:	data = ((const unsigned  long *) &uid)[index];	break;
		default:
			return false;
		}

		// All data is gathered, generate the string
		char dst[128];
		format_hex( dst, countof( dst ), data, type, leading_zero || !disable_leading_zero, upper_case );
		buf.append( dst );
	}

	// Exit
	return true;
}

static char toxdigit( int n )
{
	return (char)( n < 10 ? '0' + n : n < 16 ? 'a' + n - 10 : 0 );
}
static char toXdigit( int n )
{
	return (char)( n < 10 ? '0' + n : n < 16 ? 'A' + n - 10 : 0 );
}

int uidgen::Iuser_formatter::format_hex( char * dst, size_t dst_size, unsigned long data, int type, bool leading_zero, bool upper_case )
{
	if( dst_size < 9 )
	{
		unsigned long max_value = unsigned long( (1UL << (dst_size * 4)) - 1 );
		if( data > max_value )
			data = max_value;
	}

	signed shift = type*8 - 4;
	char * buf = dst;
	do {
		int num = (data >> shift) & 0xf;
		shift -= 4;

		if( 0 == num && !leading_zero && 0 != shift )
			continue;

		*buf ++ = upper_case ? toXdigit( num ) : toxdigit( num );
	} while( shift >= 0 );
	*buf = '\0';

	return 0;
}
int uidgen::Iuser_formatter::parse_hex( const char * src, size_t src_size, size_t min_digits, size_t max_digits, const char ** src_ptr )
{
	// Check current state
	if( min_digits > src_size )
		return -1;
	if( max_digits > src_size )
		max_digits = src_size;
	if( min_digits > max_digits )
		return -1;
	if( !string::is_hexdigit( *src ) )
		return -1;

	// Gather all digits
	int n = 0, digit;
	size_t count;
	for( count = 0; count < max_digits; ++ count, ++ src )
	{
		if( '0' <= *src && *src <= '9' )
			digit = *src - '0';
		else if( 'A' <= *src && *src <= 'F' )
			digit = 10 + *src - 'A';
		else if( 'a' <= *src && *src <= 'f' )
			digit = 10 + *src - 'a';
		else
			break;

		n = n*16 + digit;
	}

	// Check current state
	if( count < min_digits )
		return -1;

	// Exit
	*src_ptr = src;
	return n;
}

/*END OF Iuser_formatter.cxx.cpp*/
