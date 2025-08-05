/*registry_format_formatter.cxx*/
#include "pch.h"
#include "main.h"

// {F8CFD87E-DF21-466E-9B21-C4D802914813}
const uidgen::uuid	uidgen::registry_format_formatter::m_uuid =
{ 0xf8cfd87e, 0xdf21, 0x466e, { 0x9b, 0x21, 0xc4, 0xd8, 0x02, 0x91, 0x48, 0x13 } };
const uidgen::uuid & uidgen::registry_format_formatter::get_uuid() const
{
	return m_uuid;
}

bool uidgen::registry_format_formatter::get_string( uidgen::string& buf, string_id_t id ) const
{
	switch( id )
	{
	case sid_name:
		buf = "registry_format";
		break;
	case sid_description:
		buf = "Registry format { xxxxxxxx-xxxx ... xxxx }";
		break;
	case sid_help_text:
		buf = "Registry format { xxxxxxxx-xxxx ... xxxx }";
		break;
	default:
		return false;
	}
	return true;
}

const char * uidgen::registry_format_formatter::get_format_string( uidgen::context & ctx ) const
{
	if( !ctx.get_flags( uidgen::context::fl_format_lower_case ) )	// fl_format_upper_case and default
		return SZ_UID_FORMAT_REGISTRY;
	else
		return SZ_UID_FORMAT_REGISTRY_LC;
}

/*END OF registry_format_formatter.cxx*/
