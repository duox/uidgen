/*Igenerator.cxx*/
#include "pch.h"
#include "main.h"

const uidgen::uuid& uidgen::Igenerator::get_uuid() const
{
	break_on_purecall();
	return uuid::null;
}

bool uidgen::Igenerator::get_string( uidgen::string& buf, string_id_t id ) const
{
	break_on_purecall();
	unreferenced_parameter( buf );
	unreferenced_parameter( id );
	return false;
}

bool uidgen::Igenerator::generate( uuid& uid, uidgen::context& ctx ) const
{
	break_on_purecall();
	unreferenced_parameter( uid );
	unreferenced_parameter( ctx );
	return false;
}

/*END OF Igenerator.cxx*/
