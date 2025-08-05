/*cmdline.cpp*/
#include "pch.h"
#include "main.h"

void PxCmdlineParse( LPCSTR SrcCmdLine, INT * OutArgCount, LPCSTR ** OutArgs )
{
	SIZE_T CmdLineLength;
	LPSTR DstCmdLine, DstCmdLineFinal;
	LPCSTR SrcPtr;
	LPSTR DstPtr, DstStart;
	SIZE_T ArgsAllocated = 0;
	SIZE_T ArgsCount = 0;
	SIZE_T Index;
	LPCSTR * ArgsArray = NULL;
	BOOL Quotes = FALSE;

	// Check current state
	if( NULL == SrcCmdLine )
		SrcCmdLine = GetCommandLineA();

	CmdLineLength = uidgen::string::length( SrcCmdLine ) + 1;
	DstCmdLine = (LPSTR) MmHeapAlloc( CmdLineLength );	// size of the target command line will be less or equal than the source command line

	ArgsArray = (LPCSTR *) MmHeapAlloc( sizeof( LPSTR ) * (1) + CmdLineLength + 1 );

	// Split command line in substrings
	DstPtr = DstCmdLine;
	SrcPtr = SrcCmdLine;
	while( '\0' != *SrcPtr )
	{
		// Skip initial spaces
		while( uidgen::string::is_space( *SrcPtr ) )
			++ SrcPtr;
		if( '\0' == *SrcPtr )
			break;

		// Reallocate buffer if needed
		if( ArgsCount >= ArgsAllocated )
		{
			MmHeapReallocPtr( (PVOID *) &ArgsArray, sizeof( LPSTR ) * (ArgsAllocated + 8 + 1) + CmdLineLength + 1 );
			ArgsAllocated += 8;
		}

		// Skip argument contents
		DstStart = DstPtr;
		while( '\0' != *SrcPtr && (Quotes || !uidgen::string::is_space(*SrcPtr)) )
		{
			if( '\\' == *SrcPtr && '\"' == SrcPtr[1] )
				++ SrcPtr,
				*DstPtr++ = *SrcPtr;
			else if( '\"' == *SrcPtr )
			{
				if( '\"' == SrcPtr[1] )
					++ SrcPtr,
					*DstPtr++ = *SrcPtr;
				else
					Quotes = !Quotes;
			}
			else
				*DstPtr++ = *SrcPtr;
			++ SrcPtr;
		}
		*DstPtr++ = '\0';

		// Add item
		ArgsArray[ArgsCount] = DstStart;
		++ ArgsCount;
	}
	ArgsArray[ArgsCount] = NULL;

	// Rebase destination command line string right after the last argument
	DstCmdLineFinal = (LPSTR) &ArgsArray[ArgsCount + 1];
	uidgen::memory::copy(
		DstCmdLineFinal,
		DstCmdLine,
		DstPtr - DstCmdLine
		);
	for( Index = 0; Index < ArgsCount; ++ Index )
	{
		ArgsArray[Index] -= DstCmdLine - DstCmdLineFinal;
	}
	MmHeapFree( DstCmdLine );

	// Done
	*OutArgCount = (INT) ArgsCount;
	*OutArgs = ArgsArray;

	// Exit
	return;
}

/*void PxCmdlineProcess(LPCSTR CmdLine)
{
	SIZE_T ArgAllocated = 0;
	SIZE_T ArgCount = 0;
	UINT Index;
	LPCSTR SrcPtr;
	BOOL Quotes = FALSE;
	BYTE * Buffer;
	LPSTR * Args = NULL;
	LPSTR DstPtr, DstStart;
	SIZE_T CmdLineLength;

	if( NULL == CmdLine )
		CmdLine = GetCommandLineA();

	CmdLineLength = lstrlenA( CmdLine ) + 1;
	Buffer = (LPBYTE) MmHeapAlloc( CmdLineLength );

	SrcPtr = CmdLine;
	while( '\0' != *SrcPtr )
	{
		MmHeapReallocPtr( (PVOID *) &Buffer, CmdLineLength + sizeof(LPSTR)*(ArgAllocated + 8 + 1) );
		Args = (LPSTR *) (Buffer + CmdLineLength + sizeof( LPSTR ) * ArgAllocated);
		ArgAllocated += 8;

		DstPtr = (LPSTR) Buffer;
		for( Index = 0; Index < 8 && '\0' != *SrcPtr; ++ Index )
		{
			// Skip initial spaces
			while( IsCharSpace( *SrcPtr ) )
				++ SrcPtr;

			// Skip argument contents
			DstStart = DstPtr;
			while( '\0' != *SrcPtr && (Quotes || !IsCharSpace(*SrcPtr)) )
			{
				if( '\\' == *SrcPtr && '\"' == SrcPtr[1] )
					++ SrcPtr,
					*DstPtr++ = *SrcPtr;
				else if( '\"' == *SrcPtr )
				{
					if( '\"' == SrcPtr[1] )
						++ SrcPtr,
						*DstPtr++ = *SrcPtr;
					else
						Quotes = !Quotes;
				}
				else
					*DstPtr++ = *SrcPtr;
				++ SrcPtr;
			}
			*DstPtr++ = '\0';

			// Add item
			Args[ArgCount] = DstStart;
			++ ArgCount;
		}
	}
	if( NULL == Args )
		return;

	Args[ArgCount] = NULL;

	PxCmdlineProcessArgList( ArgCount, (LPCSTR*) (Buffer + CmdLineLength) );

	MmHeapFree( Buffer );
}*/

/*END OF cmdline.cpp*/
