/*console.cpp*/
#include "pch.h"
#include "main.h"

BOOL IsConsoleApp( void )
{
	if( NULL == GetStdHandle( STD_OUTPUT_HANDLE ) )
		return false;

	DWORD buf[3];
	if( 1 < GetConsoleProcessList( buf, 3 ) )
		return true;

	FreeConsole();

	return false;
}

SIZE_T ConsolePrintf( PCSTR Format, ... )
{
	SIZE_T n;
	va_list ap;

	va_start( ap, Format );
	n = ConsoleVPrintf( Format, ap );
	va_end( ap );

	return n;
}
SIZE_T ConsoleVPrintf( PCSTR Format, va_list ap )
{
	CHAR Buf[2048];
	wvsprintf( Buf/*, sizeof(Buf)*/, Format, ap);
	return ConsolePrint( Buf, (SIZE_T) -1 );
}
SIZE_T ConsolePrint( PCSTR String, SIZE_T Count )
{
	DWORD nb;

	if( -1 == Count )
		Count = lstrlen( String );

	WriteFile( GetStdHandle( STD_OUTPUT_HANDLE ), String, DWORD( Count ), &nb, NULL );

	return Count;
}

/*END OF console.cpp*/
