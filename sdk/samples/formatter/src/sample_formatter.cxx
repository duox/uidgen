/*sample_formatter.cxx*/
#include "pch.h"
#include "main.h"

// {BD28541D-C3BC-4575-B554-B4205FDCE95C}
const uidgen::uuid	uidgen::sample_formatter::m_uuid =
{ 0x92deef8c, 0x164f, 0x4823, { 0xae, 0xfa, 0x4f, 0xfb, 0x70, 0x4a, 0x35, 0xad } };
const uidgen::uuid & uidgen::sample_formatter::get_uuid() const
{
	return m_uuid;
}

bool uidgen::sample_formatter::get_string( uidgen::string& buf, string_id_t id ) const
{
	switch( id )
	{
	case sid_name:
		buf = "Sample_formatter";
		break;
	case sid_description:
		buf = "Sample formatter";
		break;
	case sid_help_text:
		buf = "Sample formatter";
		break;
	default:
		return false;
	}
	return true;
}

bool uidgen::sample_formatter::format( uidgen::string & buf, uidgen::context & ctx, const uidgen::uuid & uid ) const
{
	char sz[4] = "-00";
	for( const char * data = (const char *) &uid, * const data_end = data + sizeof( uid ); data < data_end; ++ data )
	{
		const int ch0 = (*data >> 4) & 0x0f;
		const int ch1 = *data & 0x0f;

		if( !ctx.get_flags( uidgen::context::fl_format_upper_case ) )	// fl_format_lower_case and default
		{
			sz[1] = uidgen::string::to_hexdigit_lc( ch0 );
			sz[2] = uidgen::string::to_hexdigit_lc( ch1 );
		}
		else
		{
			sz[1] = uidgen::string::to_hexdigit_uc( ch0 );
			sz[2] = uidgen::string::to_hexdigit_uc( ch1 );
		}
		buf.append( data == (const char *) &uid ? sz + 1 : sz );
	}
	return true;
}

/*END OF sample_formatter.cxx*/
