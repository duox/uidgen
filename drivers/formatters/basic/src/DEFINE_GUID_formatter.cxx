/*DEFINE_GUID_formatter.cxx*/
#include "pch.h"
#include "main.h"

// {3BF59E3F-F49C-49FA-A920-570936BB9B72}
const uidgen::uuid	uidgen::DEFINE_GUID_formatter::m_uuid =
{ 0x3bf59e3f, 0xf49c, 0x49fa, { 0xa9, 0x20, 0x57, 0x09, 0x36, 0xbb, 0x9b, 0x72 } };
const uidgen::uuid & uidgen::DEFINE_GUID_formatter::get_uuid() const
{
	return m_uuid;
}

bool uidgen::DEFINE_GUID_formatter::get_string( uidgen::string& buf, string_id_t id ) const
{
	switch( id )
	{
	case sid_name:
		buf = "DEFINE_GUID";
		break;
	case sid_description:
		buf = "DEFINE_GUID( Name, ...);";
		break;
	case sid_help_text:
		buf = "DEFINE_GUID( Name, ...);";
		break;
	default:
		return false;
	}
	return true;
}

const char * uidgen::DEFINE_GUID_formatter::get_format_string( uidgen::context & ctx ) const
{
	if( !ctx.get_flags( uidgen::context::fl_format_upper_case ) )	// fl_format_lower_case and default
		return
			"// {%{!D0}-%{!W2}-%{!W3}-%{!B8}%{!B9}-%{!B10}%{!B11}%{!B12}%{!B13}%{!B14}%{!B15}}\r\n"
			"DEFINE_GUID( %{s'Name'}, 0x%{d0}, 0x%{w2}, 0x%{w3}, 0x%{b8}, 0x%{b9}, 0x%{b10}, 0x%{b11}, 0x%{b12}, 0x%{b13}, 0x%{b14}, 0x%{b15} );"
			;
	else
		return
			"// {%{!D0}-%{!W2}-%{!W3}-%{!B8}%{!B9}-%{!B10}%{!B11}%{!B12}%{!B13}%{!B14}%{!B15}}\r\n"
			"DEFINE_GUID( %{s'Name'}, 0x%{D0}, 0X%{W2}, 0X%{W3}, 0X%{B8}, 0X%{B9}, 0X%{B10}, 0X%{B11}, 0X%{B12}, 0X%{B13}, 0X%{B14}, 0X%{B15} );"
			;
}

/*END OF DEFINE_GUID_formatter.cxx*/
