/*heap.h*/
#pragma once

PVOID UIDGEN_RTL_API MmHeapAlloc( SIZE_T Size );
PVOID UIDGEN_RTL_API MmHeapRealloc( PVOID Block, SIZE_T Size );
BOOL UIDGEN_RTL_API MmHeapReallocPtr( PVOID* Block, SIZE_T Size );
VOID UIDGEN_RTL_API MmHeapFree( PVOID Block );

/*END OF heap.h*/
