/*Guid_attribute_2_formatter.cxx*/
#include "pch.h"
#include "main.h"

// {0C7B554B-7595-49D1-95F6-9FDBB4F54481}
const uidgen::uuid	uidgen::Guid_attribute_2_formatter::m_uuid =
{ 0x0c7b554b, 0x7595, 0x49d1, { 0x95, 0xf6, 0x9f, 0xdb, 0xb4, 0xf5, 0x44, 0x81 } };
const uidgen::uuid & uidgen::Guid_attribute_2_formatter::get_uuid() const
{
	return m_uuid;
}

bool uidgen::Guid_attribute_2_formatter::get_string( uidgen::string& buf, string_id_t id ) const
{
	switch( id )
	{
	case sid_name:
		buf = "Guid_attribute_2";
		break;
	case sid_description:
		buf = "<Guid(\"xxxxxxxx-xxxx ... xxxx\")>";
		break;
	case sid_help_text:
		buf = "<Guid(\"xxxxxxxx-xxxx ... xxxx\")>";
		break;
	default:
		return false;
	}
	return true;
}

const char * uidgen::Guid_attribute_2_formatter::get_format_string( uidgen::context & ctx ) const
{
	if( !ctx.get_flags( uidgen::context::fl_format_lower_case ) )	// fl_format_upper_case and default
		return
			"<Guid(\"%{D0}-%{W2}-%{W3}-%{B8}%{B9}-%{B10}%{B11}%{B12}%{B13}%{B14}%{B15}\")>"
			;
	else
		return
			"<Guid(\"%{d0}-%{w2}-%{w3}-%{b8}%{b9}-%{b10}%{b11}%{b12}%{b13}%{b14}%{b15}\")>"
			;
}

/*END OF Guid_attribute_2_formatter.cxx*/
