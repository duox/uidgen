/*Csharp_field_definition_formatter.cxx*/
#include "pch.h"
#include "main.h"

// {BD28541D-C3BC-4575-B554-B4205FDCE95C}
const uidgen::uuid	uidgen::Csharp_field_definition_formatter::m_uuid =
{ 0xbd28541d, 0xc3bc, 0x4575, { 0xb5, 0x54, 0xb4, 0x20, 0x5f, 0xdc, 0xe9, 0x5c } };
const uidgen::uuid & uidgen::Csharp_field_definition_formatter::get_uuid() const
{
	return m_uuid;
}

bool uidgen::Csharp_field_definition_formatter::get_string( uidgen::string& buf, string_id_t id ) const
{
	switch( id )
	{
	case sid_name:
		buf = "Csharp_field_definition";
		break;
	case sid_description:
		buf = "C# field definition";
		break;
	case sid_help_text:
		buf = "C# field definition";
		break;
	default:
		return false;
	}
	return true;
}

const char * uidgen::Csharp_field_definition_formatter::get_format_string( uidgen::context & ctx ) const
{
	if( !ctx.get_flags( uidgen::context::fl_format_upper_case ) )	// fl_format_lower_case and default
		return
			"// {%{!D0}-%{!W2}-%{!W3}-%{!B8}%{!B9}-%{!B10}%{!B11}%{!B12}%{!B13}%{!B14}%{!B15}}\r\n"
			"static readonly Guid %{s'Name'} = new Guid(0x%{d0}, 0x%{w2}, 0x%{w3}, 0x%{b8}, 0x%{b9}, 0x%{b10}, 0x%{b11}, 0x%{b12}, 0x%{b13}, 0x%{b14}, 0x%{b15});"
			;
	else
		return
			"// {%{!D0}-%{!W2}-%{!W3}-%{!B8}%{!B9}-%{!B10}%{!B11}%{!B12}%{!B13}%{!B14}%{!B15}}\r\n"
			"static readonly Guid %{s'Name'} = new Guid(0x%{D0}, 0X%{W2}, 0X%{W3}, 0X%{B8}, 0X%{B9}, 0X%{B10}, 0X%{B11}, 0X%{B12}, 0X%{B13}, 0X%{B14}, 0X%{B15});"
			;
}

/*END OF Csharp_field_definition_formatter.cxx*/
