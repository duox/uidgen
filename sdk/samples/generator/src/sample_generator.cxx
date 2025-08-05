/*sample_generator.cxx*/
#include "pch.h"
#include "main.h"

// {67E06AF3-B9B7-446D-BBBD-E91FEE22BD54}
const uidgen::uuid	uidgen::sample_generator::m_uuid =
{ 0x67e06af3, 0xb9b7, 0x446d, { 0xbb, 0xbd, 0xe9, 0x1f, 0xee, 0x22, 0xbd, 0x54 } };
const uidgen::uuid & uidgen::sample_generator::get_uuid() const
{
	return m_uuid;
}

bool uidgen::sample_generator::get_string( uidgen::string& buf, string_id_t id ) const
{
	switch( id )
	{
	case sid_name:
		buf = "sample_generator";
		break;
	case sid_description:
		buf = "Sample UUID generator";
		break;
	case sid_help_text:
		buf = "Sample UUID generator";
		break;
	default:
		return false;
	}
	return true;
}

bool uidgen::sample_generator::generate( uuid & uid, uidgen::context & ctx ) const
{
	memset( &uid, 0xCC, sizeof( uid ) );

	unreferenced_parameter( ctx );
	return true;
}

/*END OF sample_generator.cxx*/
