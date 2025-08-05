/*Iprovider.cxx*/
#include "pch.h"
#include "main.h"

void uidgen::Iprovider::printf( const char* format, ... )
{
	unreferenced_parameter( format );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void uidgen::null_provider::printf( const char* , ... )
{
}

/*END OF Iprovider.cxx*/
