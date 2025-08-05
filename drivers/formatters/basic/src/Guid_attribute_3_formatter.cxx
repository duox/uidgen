/*Guid_attribute_3_formatter.cxx*/
#include "pch.h"
#include "main.h"

// {C277CCB2-F342-4D4A-8165-9D75FB6547B9}
const uidgen::uuid	uidgen::Guid_attribute_3_formatter::m_uuid =
{ 0xc277ccb2, 0xf342, 0x4d4a, { 0x81, 0x65, 0x9d, 0x75, 0xfb, 0x65, 0x47, 0xb9 } };
const uidgen::uuid & uidgen::Guid_attribute_3_formatter::get_uuid() const
{
	return m_uuid;
}

bool uidgen::Guid_attribute_3_formatter::get_string( uidgen::string& buf, string_id_t id ) const
{
	switch( id )
	{
	case sid_name:
		buf = "Guid_attribute_3";
		break;
	case sid_description:
		buf = "guid(xxxxxxxx-xxxx ... xxxx)";
		break;
	case sid_help_text:
		buf = "guid(xxxxxxxx-xxxx ... xxxx)";
		break;
	default:
		return false;
	}
	return true;
}

const char * uidgen::Guid_attribute_3_formatter::get_format_string( uidgen::context & ctx ) const
{
	if( !ctx.get_flags( uidgen::context::fl_format_lower_case ) )	// fl_format_upper_case and default
		return
			"// {%{!D0}-%{!W2}-%{!W3}-%{!B8}%{!B9}-%{!B10}%{!B11}%{!B12}%{!B13}%{!B14}%{!B15}}\r\n"
			"guid(%{D0}-%{W2}-%{W3}-%{B8}%{B9}-%{B10}%{B11}%{B12}%{B13}%{B14}%{B15})"
			;
	else
		return
			"// {%{!D0}-%{!W2}-%{!W3}-%{!B8}%{!B9}-%{!B10}%{!B11}%{!B12}%{!B13}%{!B14}%{!B15}}\r\n"
			"guid(%{d0}-%{w2}-%{w3}-%{b8}%{b9}-%{b10}%{b11}%{b12}%{b13}%{b14}%{b15})"
			;
}

/*END OF Guid_attribute_3_formatter.cxx*/
