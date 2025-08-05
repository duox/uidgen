/*uuid.cxx*/
#include "pch.h"
#include "main.h"

uidgen::uuid	uidgen::uuid::null;

bool uidgen::uuid::operator==( const uuid& uuid ) const
{
	return qwData0 == uuid.qwData0 && qwData1 == uuid.qwData1;
}
bool uidgen::uuid::operator!=( const uuid& uuid ) const
{
	return !operator==( uuid );
}

/*END OF uuid.cxx*/
