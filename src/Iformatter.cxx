/*Iformatter.cxx*/
#include "pch.h"
#include "main.h"

const uidgen::uuid& uidgen::Iformatter::get_uuid() const
{
	break_on_purecall();
	return uuid::null;
}

bool uidgen::Iformatter::get_string( uidgen::string& buf, string_id_t id ) const
{
	break_on_purecall();
	unreferenced_parameter( buf );
	unreferenced_parameter( id );
	return false;
}

bool uidgen::Iformatter::format( uidgen::string& buf, uidgen::context& ctx, const uuid& uid ) const
{
	break_on_purecall();
	unreferenced_parameter( buf );
	unreferenced_parameter( ctx );
	unreferenced_parameter( uid );
	return false;
}

/*END OF Iformatter.cxx*/
