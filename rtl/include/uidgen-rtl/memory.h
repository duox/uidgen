/*memory.h*/
#pragma once

LPVOID UIDGEN_RTL_API RtlMemoryCopy( LPVOID RESTRICT Dst, LPCVOID RESTRICT Src, SIZE_T Count );
LPVOID UIDGEN_RTL_API RtlMemoryMove( LPVOID Dst, LPCVOID Src, SIZE_T Count );
int UIDGEN_RTL_API RtlMemoryCompare( LPCVOID Mem1, LPCVOID Mem2, SIZE_T Count );

/*END OF memory.h*/
