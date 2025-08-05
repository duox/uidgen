/*VbNet_field_definition_formatter.cxx*/
#include "pch.h"
#include "main.h"

// {12A8CF78-D455-4F10-AC13-43510E3046AD}
const uidgen::uuid	uidgen::VbNet_field_definition_formatter::m_uuid =
{ 0x12a8cf78, 0xd455, 0x4f10, { 0xac, 0x13, 0x43, 0x51, 0x0e, 0x30, 0x46, 0xad } };
const uidgen::uuid & uidgen::VbNet_field_definition_formatter::get_uuid() const
{
	return m_uuid;
}

bool uidgen::VbNet_field_definition_formatter::get_string( uidgen::string& buf, string_id_t id ) const
{
	switch( id )
	{
	case sid_name:
		buf = "VbNet_field_definition";
		break;
	case sid_description:
		buf = "VB.NET field definition";
		break;
	case sid_help_text:
		buf = "VB.NET field definition";
		break;
	default:
		return false;
	}
	return true;
}

const char * uidgen::VbNet_field_definition_formatter::get_format_string( uidgen::context & ctx ) const
{
	if( !ctx.get_flags( uidgen::context::fl_format_lower_case ) )	// fl_format_upper_case and default
		return
			"' {%{!D0}-%{!W2}-%{!W3}-%{!B8}%{!B9}-%{!B10}%{!B11}%{!B12}%{!B13}%{!B14}%{!B15}}\r\n"
			"Shared ReadOnly %{s'Name'} As Guid = New Guid(&H%{d0}, &H%{w2}, &H%{w3}, &H%{b8}, &H%{b9}, &H%{b10}, &H%{b11}, &H%{b12}, &H%{b13}, &H%{b14}, &H%{b15})"
			;
	else
		return
			"' {%{!D0}-%{!W2}-%{!W3}-%{!B8}%{!B9}-%{!B10}%{!B11}%{!B12}%{!B13}%{!B14}%{!B15}}\r\n"
			"Shared ReadOnly %{s'Name'} As Guid = New Guid(&H%{D0}, &H%{W2}, &H%{W3}, &H%{B8}, &H%{B9}, &H%{B10}, &H%{B11}, &H%{B12}, &H%{B13}, &H%{B14}, &H%{B15})"
			;
}

/*END OF VbNet_field_definition_formatter.cxx*/
