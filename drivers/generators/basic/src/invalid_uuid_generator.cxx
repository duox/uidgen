/*invalid_uuid_generator.cxx*/
#include "pch.h"
#include "main.h"

// {361D667B-D7B9-497F-868A-95D38083DB15}
const uidgen::uuid	uidgen::invalid_uuid_generator::m_uuid =
{ 0x361d667b, 0xd7b9, 0x497f, { 0x86, 0x8a, 0x95, 0xd3, 0x80, 0x83, 0xdb, 0x15 } };
const uidgen::uuid & uidgen::invalid_uuid_generator::get_uuid() const
{
	return m_uuid;
}

bool uidgen::invalid_uuid_generator::get_string( uidgen::string& buf, string_id_t id ) const
{
	switch( id )
	{
	case sid_name:
		buf = "invalid_uuid";
		break;
	case sid_description:
		buf = "Invalid UUID generator";
		break;
	case sid_help_text:
		buf = "Use all-ones GUID";
		break;
	default:
		return false;
	}
	return true;
}

bool uidgen::invalid_uuid_generator::generate( uuid & uid, uidgen::context & ctx ) const
{
	uid.qwData0 = uid.qwData1 = (unsigned long long) -1;

	unreferenced_parameter( ctx );
	return true;
}

/*END OF invalid_uuid_generator.cxx*/
