/*IDL_interface_template_formatter.cxx*/
#include "pch.h"
#include "main.h"

// {19B100CF-A32D-469A-B05A-14A51C65B5F3}
const uidgen::uuid	uidgen::IDL_interface_template_formatter::m_uuid =
{ 0x19b100cf, 0xa32d, 0x469a, { 0xb0, 0x5a, 0x14, 0xa5, 0x1c, 0x65, 0xb5, 0xf3 } };
const uidgen::uuid & uidgen::IDL_interface_template_formatter::get_uuid() const
{
	return m_uuid;
}

bool uidgen::IDL_interface_template_formatter::get_string( uidgen::string& buf, string_id_t id ) const
{
	switch( id )
	{
	case sid_name:
		buf = "IDL_interface_template";
		break;
	case sid_description:
		buf = "IDL interface template";
		break;
	case sid_help_text:
		buf = "IDL interface template";
		break;
	default:
		return false;
	}
	return true;
}

const char * uidgen::IDL_interface_template_formatter::get_format_string( uidgen::context & ctx ) const
{
	if( !ctx.get_flags( uidgen::context::fl_format_lower_case ) )	// fl_format_upper_case and default
		return
			"// {%{!D0}-%{!W2}-%{!W3}-%{!B8}%{!B9}-%{!B10}%{!B11}%{!B12}%{!B13}%{!B14}%{!B15}}\r\n"
			"[\r\n"
			"uuid(%{!D0}-%{!W2}-%{!W3}-%{!B8}%{!B9}-%{!B10}%{!B11}%{!B12}%{!B13}%{!B14}%{!B15})\r\n"
			"version(1.0)\r\n"
			"]\r\n"
			"interface %{s'INTERFACENAME'}\r\n"
			"{\r\n"
			"\r\n"
			"}\r\n";
	else
		return
			"// {%{!D0}-%{!W2}-%{!W3}-%{!B8}%{!B9}-%{!B10}%{!B11}%{!B12}%{!B13}%{!B14}%{!B15}}\r\n"
			"[\r\n"
			"uuid(%{!d0}-%{!w2}-%{!w3}-%{!b8}%{!b9}-%{!b10}%{!b11}%{!b12}%{!b13}%{!b14}%{!b15})\r\n"
			"version(1.0)\r\n"
			"]\r\n"
			"interface %{s'INTERFACENAME'}\r\n"
			"{\r\n"
			"\r\n"
			"}\r\n";
}

/*END OF IDL_interface_template_formatter.cxx*/
