/*manual_uuid_generator.cxx*/
#include "pch.h"
#include "main.h"

// {39A366BE-742C-4086-80A1-21325525E82B}
const uidgen::uuid	uidgen::manual_uuid_generator::m_uuid =
{ 0x39a366be, 0x742c, 0x4086, { 0x80, 0xa1, 0x21, 0x32, 0x55, 0x25, 0xe8, 0x2b } };
const uidgen::uuid & uidgen::manual_uuid_generator::get_uuid() const
{
	return m_uuid;
}

bool uidgen::manual_uuid_generator::get_string( uidgen::string& buf, string_id_t id ) const
{
	switch( id )
	{
	case sid_name:
		buf = "manual_uuid";
		break;
	case sid_description:
		buf = "Manual UUID";
		break;
	case sid_help_text:
		buf = "UUID value supplied by -u option, in braced format";
		break;
	default:
		return false;
	}
	return true;
}

/**
* @brief Parse GUID representation.
*
* @param[out] buf (GUID &) reference to variable receiving parsed GUID data.
* @param[in] data (const char *) pointer to string.
*
* @return (bool) operation status.
*/
static bool ParseGuid( UUID & buf, const char * data )
{
	wchar_t wdata[128], *wbuf = wdata;
	if( '{' != *data )
	{
		wdata[0] = L'{';
		wbuf = wdata + 1;
	}
	*wbuf = L'\0';

	SetLastError( NO_ERROR );
	MultiByteToWideChar( CP_ACP, 0, data, -1, wbuf, (int) (countof(wdata) - (wbuf - wdata)) );
	if( NO_ERROR != GetLastError() )
		return false;

	if( '{' != *data )
		lstrcatW( wbuf, L"}" );

	return !!SUCCEEDED( IIDFromString( wdata, &buf ) );
}

bool uidgen::manual_uuid_generator::generate( uuid & uid, uidgen::context & ctx ) const
{
	return ParseGuid( (UUID &) uid, ctx.get_user_data().c_str() );
}

/*END OF manual_uuid_generator.cxx*/
