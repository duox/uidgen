/*cppheap.cpp*/
#include "pch.h"
#include "main.h"

void* operator new(size_t n)
{
	return HeapAlloc( GetProcessHeap(), 0, n );
}
void operator delete(void * p)
{
	HeapFree( GetProcessHeap(), 0, p );
	return;
}
void operator delete(void* p, size_t )
{
	HeapFree( GetProcessHeap(), 0, p );
	return;
}

void operator delete[](void * p)
{
	HeapFree( GetProcessHeap(), 0, p );
	return;
}
void operator delete[](void* p, size_t )
{
	HeapFree( GetProcessHeap(), 0, p );
	return;
}

/*END OF cppheap.cpp*/
