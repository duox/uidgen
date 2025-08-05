/*null_uuid_generator.cxx*/
#include "pch.h"
#include "main.h"

// {DDB4578C-9350-494C-A06C-357F804B0F91}
const uidgen::uuid	uidgen::null_uuid_generator::m_uuid =
{ 0xddb4578c, 0x9350, 0x494c, { 0xa0, 0x6c, 0x35, 0x7f, 0x80, 0x4b, 0x0f, 0x91 } };
const uidgen::uuid & uidgen::null_uuid_generator::get_uuid() const
{
	return m_uuid;
}

bool uidgen::null_uuid_generator::get_string( uidgen::string& buf, string_id_t id ) const
{
	switch( id )
	{
	case sid_name:
		buf = "null_uuid";
		break;
	case sid_description:
		buf = "Null UID generator";
		break;
	case sid_help_text:
		buf = "All-zeroes UUID";
		break;
	default:
		return false;
	}
	return true;
}

bool uidgen::null_uuid_generator::generate( uuid & uid, uidgen::context & ctx ) const
{
	uid.qwData0 = uid.qwData1 = 0;

	unreferenced_parameter( ctx );
	return true;
}

/*END OF null_uuid_generator.cxx*/
