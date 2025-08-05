/*conmain.cpp*/
/** @file
 *
 * @brief Console entry point.
 * SPDX-License-Identifier: MIT
 *
 */
#include "pch.h"
#include "main.h"

/**
 * @brief Console entry point function.
 * @return (DWORD) process exit code.
 */
DWORD ConsoleMain( void )
{
	// Set up console
	SetConsoleMode( GetStdHandle( STD_OUTPUT_HANDLE ), ENABLE_PROCESSED_OUTPUT | ENABLE_WRAP_AT_EOL_OUTPUT );

	// Initialize context
	if( nullptr == g_uidgen_context->get_active_generator() )
		g_uidgen_context->set_active_generator( g_uidgen_context->find_generator( uidgen::random_uuid_generator::m_uuid ) );
	if( nullptr == g_uidgen_context->get_active_formatter() )
		g_uidgen_context->set_active_formatter( g_uidgen_context->find_formatter( uidgen::registry_format_formatter::m_uuid ) );

	// Generate GUID and display it
	g_uidgen_context->begin_generation();
	while( g_uidgen_context->can_generate_more_uids() )
	{
		uidgen::string buf;
		uidgen::string msg_buf;
		if( !g_uidgen_context->generation_uid( buf, msg_buf ) )
		{
			ConsolePrintString( "*** fatal error: " );
			ConsolePrintString( msg_buf.c_str() );
			ConsolePrintString( ".\n" );
			return 2;
		}

		ConsolePrint( buf.c_str(), DWORD( buf.size() ) );
		ConsolePrint( "\n", 1 );
	}
	g_uidgen_context->end_generation();

	// Exit
	return 0;
}

/*END OF conmain.cpp*/
