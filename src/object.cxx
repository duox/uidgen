/*object.cxx*/
#include "pch.h"
#include "main.h"

uidgen::object::~object()
{
}
void uidgen::object::release()
{
//	if( (SIZE_T) -1 != HeapSize(GetProcessHeap(), HEAP_NO_SERIALIZE, this) )
//		delete this;
}

/*END OF object.cxx*/
