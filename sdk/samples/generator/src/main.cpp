/*main.cpp*/
#include "pch.h"
#include "main.h"

extern "C" __declspec(dllexport) bool _cdecl uidgen_install_plugin( uidgen::context * uidgen_context )
{
	uidgen_context->append_generator( *new uidgen::sample_generator );
	return true;
}

/*END OF main.cpp*/
