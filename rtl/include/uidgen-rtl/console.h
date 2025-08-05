/*console.h*/
#pragma once

BOOL UIDGEN_RTL_API IsConsoleApp( void );
SIZE_T UIDGEN_RTL_API ConsolePrintf( PCSTR Format, ... );
SIZE_T UIDGEN_RTL_API ConsoleVPrintf( PCSTR Format, va_list ap );
SIZE_T UIDGEN_RTL_API ConsolePrint( PCSTR String, SIZE_T Count );
#define ConsolePrintString( String )	ConsolePrint( String, (SIZE_T) -1 )

/*END OF console.h*/
