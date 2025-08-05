/*raw_format_formatter.cxx*/
#include "pch.h"
#include "main.h"

// {5876866F-D6B1-4B37-9F5A-5EA01FB7D4C3}
const uidgen::uuid	uidgen::raw_format_formatter::m_uuid =
{ 0x5876866f, 0xd6b1, 0x4b37, { 0x9f, 0x5a, 0x5e, 0xa0, 0x1f, 0xb7, 0xd4, 0xc3 } };
const uidgen::uuid & uidgen::raw_format_formatter::get_uuid() const
{
	return m_uuid;
}

bool uidgen::raw_format_formatter::get_string( uidgen::string& buf, string_id_t id ) const
{
	switch( id )
	{
	case sid_name:
		buf = "raw_format";
		break;
	case sid_description:
		buf = "Raw format xxxxxxxxxxxx ... xxxx";
		break;
	case sid_help_text:
		buf = "Raw format xxxxxxxxxxxx ... xxxx";
		break;
	default:
		return false;
	}
	return true;
}

const char * uidgen::raw_format_formatter::get_format_string( uidgen::context & ctx ) const
{
	if( !ctx.get_flags( uidgen::context::fl_format_lower_case ) )	// fl_format_upper_case and default
		return
			"%{0B0}%{0B1}%{0B2}%{0B3}%{0B4}%{0B5}%{0B6}%{0B7}"
			"%{0B8}%{0B9}%{0B10}%{0B11}%{0B12}%{0B13}%{0B14}%{0B15}"
			;
	else
		return
			"%{0b0}%{0b1}%{0b2}%{0b3}%{0b4}%{0b5}%{0b6}%{0b7}"
			"%{0b8}%{0b9}%{0b10}%{0b11}%{0b12}%{0b13}%{0b14}%{0b15}"
			;
}

/*END OF raw_format_formatter.cxx*/
