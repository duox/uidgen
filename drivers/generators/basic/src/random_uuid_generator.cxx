/*random_uuid_generator.cxx*/
#include "pch.h"
#include "main.h"

// {29E99FC1-9CAF-41C9-93FA-4A5D0B72C9E6}
const uidgen::uuid	uidgen::random_uuid_generator::m_uuid =
{ 0x29e99fc1, 0x9caf, 0x41c9, { 0x93, 0xfa, 0x4a, 0x5d, 0x0b, 0x72, 0xc9, 0xe6 } };
const uidgen::uuid & uidgen::random_uuid_generator::get_uuid() const
{
	return m_uuid;
}

bool uidgen::random_uuid_generator::get_string( uidgen::string& buf, string_id_t id ) const
{
	switch( id )
	{
	case sid_name:
		buf = "random_uuid";
		break;
	case sid_description:
		buf = "Random UUID generator";
		break;
	case sid_help_text:
		buf = "Random UUID generator";
		break;
	default:
		return false;
	}
	return true;
}

bool uidgen::random_uuid_generator::generate( uuid & uid, uidgen::context & ctx ) const
{
	HRESULT hResult = CoCreateGuid( (GUID *) & uid );
	if( FAILED(hResult) )
	{
		RPC_STATUS RpcStatus = UuidCreate( (GUID *) &uid );
		if( RPC_S_OK != RpcStatus && RPC_S_UUID_LOCAL_ONLY != RpcStatus )
			return false;
	}

	if( ctx.get_flags( context::fl_format_big_endian ) )
	{
		uid.Data1 = htonl( uid.Data1 );
		uid.Data2 = htons( uid.Data2 );
		uid.Data3 = htons( uid.Data3 );
	}

	unreferenced_parameter( ctx );
	return true;
}

/*END OF random_uuid_generator.cxx*/
