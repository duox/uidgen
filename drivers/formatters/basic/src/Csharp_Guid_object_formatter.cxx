/*Csharp_Guid_object_formatter.cxx*/
#include "pch.h"
#include "main.h"

// {BD28541D-C3BC-4575-B554-B4205FDCE95C}
const uidgen::uuid	uidgen::Csharp_Guid_object_formatter::m_uuid =
{ 0xbd28541d, 0xc3bc, 0x4575, { 0xb5, 0x54, 0xb4, 0x20, 0x5f, 0xdc, 0xe9, 0x5c } };
const uidgen::uuid & uidgen::Csharp_Guid_object_formatter::get_uuid() const
{
	return m_uuid;
}

bool uidgen::Csharp_Guid_object_formatter::get_string( uidgen::string& buf, string_id_t id ) const
{
	switch( id )
	{
	case sid_name:
		buf = "Csharp_Guid_object";
		break;
	case sid_description:
		buf = "C# Guid object initializer";
		break;
	case sid_help_text:
		buf = "C# Gui object initializer";
		break;
	default:
		return false;
	}
	return true;
}

const char * uidgen::Csharp_Guid_object_formatter::get_format_string( uidgen::context & ctx ) const
{
	if( !ctx.get_flags( uidgen::context::fl_format_lower_case ) )	// fl_format_upper_case and default
		return
			"// {%{!D0}-%{!W2}-%{!W3}-%{!B8}%{!B9}-%{!B10}%{!B11}%{!B12}%{!B13}%{!B14}%{!B15}}\r\n"
			"Guid %{s'Name'} = new Guid(\"%{!D0}-%{!W2}-%{!W3}-%{!B8}%{!B9}-%{!B10}%{!B11}%{!B12}%{!B13}%{!B14}%{!B15}\");"
			;
	else
		return
			"// {%{!D0}-%{!W2}-%{!W3}-%{!B8}%{!B9}-%{!B10}%{!B11}%{!B12}%{!B13}%{!B14}%{!B15}}\r\n"
			"Guid %{s'Name'} = new Guid(\"%{!d0}-%{!w2}-%{!w3}-%{!b8}%{!b9}-%{!b10}%{!b11}%{!b12}%{!b13}%{!b14}%{!b15}\");"
			;
}

/*END OF Csharp_Guid_object_formatter.cxx*/
