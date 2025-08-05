/*main.cpp*/
/** @file
 *
 * @brief The main file of the UIDGEN application.
 * SPDX-License-Identifier: MIT
 *
 *	The code in this file detects currently active mode (GUI or console and calls corresponding secondary
 * main function.
 */
#include "pch.h"
#include "main.h"
#include "uidgen/uidgen_context.hxx"

uidgen::context	* g_uidgen_context;			// currently active uidgen context
DWORD	gSystemFlags = SF_ESC_CLOSES_APP;	// system flags (see SF_* constants)
UINT	gWindowHotKey;						// hot key for opening the main window
UINT	gGeneratorHotKey;					// hot key for background generation
STARTUPINFO gStartupInfo = { sizeof( STARTUPINFO ), 0 };

/**
 * @brief Application entry point.
 * @return (DWORD) application exit code.
 * 
 * This function is specified in the linker command line for the /ENTRY switch.
 */
DWORD __stdcall EntryPoint( void )
{
	DWORD ExitCode = (DWORD) -1;

	// Set local context as active; additional perk is that no C++ start up code is needed
	uidgen_context	context;
	g_uidgen_context = &context;

	// Get process start up information
	gStartupInfo.dwFlags = STARTF_USESHOWWINDOW;
	GetStartupInfo( &gStartupInfo );
#ifdef _DEBUG	// there's a bug under MSVS debugger that the process is created with gStartupInfo.wShowWindow == 0
	gStartupInfo.wShowWindow = SW_SHOWDEFAULT;
#endif // def _DEBUG

	// Process command line
	INT ArgCount;
	LPCSTR * Args;
	PxCmdlineParse( NULL, &ArgCount, &Args );
	ProcessCmdLineArgs( ArgCount, Args );

	// Detect correct working mode and call the corresponding main function
	if( !(gSystemFlags & SF_REQUEST_EXIT) )
	{
		if( (gSystemFlags & SF_FORCE_CONSOLE) || (!(gSystemFlags & SF_FORCE_GUI) && IsConsoleApp()) )
		{
			LoadPlugins();
			// Call console entry point function
			ExitCode = ConsoleMain();
		}
		else
		{
			// Hide console window
#if(_WIN32_WINNT >= 0x0500)
			HWND hwndConsole = GetConsoleWindow();
			if( GetCurrentThreadId() == GetWindowThreadProcessId( hwndConsole, NULL ) )
				ShowWindow( hwndConsole, SW_HIDE );
#endif // (_WIN32_WINNT >= 0x0500)

			// If GUI application is specified to run hidden, ignore this
			if( SW_HIDE == gStartupInfo.wShowWindow )
				gStartupInfo.wShowWindow = SW_SHOWDEFAULT;	// there's no reason to run GUI application hidden

			LoadPlugins();
			// Call GUI entry point function
			ExitCode = WinMain( (HINSTANCE) GetModuleHandle( NULL ), NULL, GetCommandLineA(), gStartupInfo.wShowWindow );
		}
	}

	// Reset pointer to the active context
	g_uidgen_context = nullptr;

	// Exit from the process
	ExitProcess( ExitCode );
}

/*END OF main.cpp*/
