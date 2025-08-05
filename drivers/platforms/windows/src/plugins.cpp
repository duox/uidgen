/*args.cpp*/
/** @file
 *
 * @brief Command line management.
 * SPDX-License-Identifier: MIT
 *
 *	Plugin management.
 */
#include "pch.h"
#include "main.h"

typedef bool (_cdecl *PFN_PLUGIN_INIT)( uidgen::context * uidgen_context );

/**
 * @brief Load plugins from the current directory.
 */
void LoadPlugins()
{
	HANDLE hFind;
	WIN32_FIND_DATAA fd;
	HMODULE hPlugin;
	PFN_PLUGIN_INIT pfnInit;

	hFind = FindFirstFileA( "*.uidgen", &fd );
	if( INVALID_HANDLE_VALUE != hFind )
	{
		do
		{
			hPlugin = LoadLibraryA( fd.cFileName );
			if( NULL == hPlugin )
				continue;

			pfnInit = (PFN_PLUGIN_INIT) GetProcAddress( hPlugin, "uidgen_install_plugin" );
			if( NULL == pfnInit )
			{
				OutputDebugStringA( "uidfen: the plugin doesn't contain uidgen_install_plugin: " );
				OutputDebugStringA( fd.cFileName );
				OutputDebugStringA( "\n" );
				FreeLibrary( hPlugin );
				continue;
			}

			if( false == (*pfnInit)( g_uidgen_context ) )
				FreeLibrary( hPlugin );
		} while( FindNextFileA( hFind, &fd ) );
		FindClose( hFind );
	}
	return;
}

/*END OF args.cpp*/
