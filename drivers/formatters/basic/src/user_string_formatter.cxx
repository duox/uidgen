/*user_string_formatter.cxx*/
#include "pch.h"
#include "main.h"

// {43917179-6B0B-4BA9-A847-BCA4B56ABC82}
const uidgen::uuid	uidgen::user_string_formatter::m_uuid =
{ 0x43917179, 0x6b0b, 0x4ba9, { 0xa8, 0x47, 0xbc, 0xa4, 0xb5, 0x6a, 0xbc, 0x82 } };
const uidgen::uuid & uidgen::user_string_formatter::get_uuid() const
{
	return m_uuid;
}

bool uidgen::user_string_formatter::get_string( uidgen::string& buf, string_id_t id ) const
{
	switch( id )
	{
	case sid_name:
		buf = "user_string";
		break;
	case sid_description:
		buf = "User string formatter";
		break;
	case sid_help_text:
		buf = "User string formatter";
		break;
	default:
		return false;
	}
	return true;
}

const char * uidgen::user_string_formatter::get_format_string( uidgen::context & ctx ) const
{
	return ctx.get_user_format_string().c_str();
}

/*END OF user_string_formatter.cxx*/
