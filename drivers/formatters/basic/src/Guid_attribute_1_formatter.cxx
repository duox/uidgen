/*Guid_attribute_1_formatter.cxx*/
#include "pch.h"
#include "main.h"

// {FF12C707-A277-4DFA-B08C-7DAC9B3D4CE3}
const uidgen::uuid	uidgen::Guid_attribute_1_formatter::m_uuid =
{ 0xff12c707, 0xa277, 0x4dfa, { 0xb0, 0x8c, 0x7d, 0xac, 0x9b, 0x3d, 0x4c, 0xe3 } };
const uidgen::uuid & uidgen::Guid_attribute_1_formatter::get_uuid() const
{
	return m_uuid;
}

bool uidgen::Guid_attribute_1_formatter::get_string( uidgen::string& buf, string_id_t id ) const
{
	switch( id )
	{
	case sid_name:
		buf = "Guid_attribute_1";
		break;
	case sid_description:
		buf = "[Guid(\"xxxxxxxx-xxxx ... xxxx\")]";
		break;
	case sid_help_text:
		buf = "[Guid(\"xxxxxxxx-xxxx ... xxxx\")]";
		break;
	default:
		return false;
	}
	return true;
}

const char * uidgen::Guid_attribute_1_formatter::get_format_string( uidgen::context & ctx ) const
{
	if( !ctx.get_flags( uidgen::context::fl_format_lower_case ) )	// fl_format_upper_case and default
		return
			"[Guid(\"%{D0}-%{W2}-%{W3}-%{B8}%{B9}-%{B10}%{B11}%{B12}%{B13}%{B14}%{B15}\")]"
			;
	else
		return
			"[Guid(\"%{d0}-%{w2}-%{w3}-%{b8}%{b9}-%{b10}%{b11}%{b12}%{b13}%{b14}%{b15}\")]"
			;
}

/*END OF Guid_attribute_1_formatter.cxx*/
