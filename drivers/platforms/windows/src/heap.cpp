/*heap.cpp*/
#include "pch.h"
#include "main.h"

PVOID MmHeapAlloc( SIZE_T Size )
{
	return HeapAlloc( GetProcessHeap(), 0, Size );
}
PVOID MmHeapRealloc( PVOID Block, SIZE_T Size )
{
	if( NULL == Block )
		return HeapAlloc( GetProcessHeap(), 0, Size );
	return HeapReAlloc( GetProcessHeap(), 0, Block, Size );
}
BOOL MmHeapReallocPtr( PVOID * Block, SIZE_T Size )
{
	PVOID NewBlock;

	if( NULL == Block )
		return FALSE;

	if( NULL == *Block )
		NewBlock = HeapAlloc( GetProcessHeap(), 0, Size );
	else
		NewBlock = HeapReAlloc( GetProcessHeap(), 0, *Block, Size );
	if( NULL == NewBlock )
		return FALSE;

	*Block = NewBlock;
	return TRUE;
}
VOID MmHeapFree( PVOID Block )
{
	HeapFree( GetProcessHeap(), 0, Block );
}

/*END OF heap.cpp*/
