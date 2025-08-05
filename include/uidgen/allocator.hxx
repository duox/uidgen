/*allocator.hxx*/

#if 0
class UIDGEN_INLINE_API uidgen::PosixHeapAllocator
{
public:
	static void * (malloc)( size_t n ) { return ::malloc( n ); }
	static void * (calloc)( size_t m, size_t n ) { return ::calloc( m, n ); }
	static void * (realloc)( void * p, size_t n ) { return ::realloc( p, n ); }
	static void (free)( void * p, size_t /*n*/ ) { ::free(p); }
};
#endif

#ifdef _WINDOWS_
class UIDGEN_INLINE_API uidgen::WindowsHeapAllocator
{
public:
	static void * (malloc)( size_t size ) { return ::HeapAlloc( ::GetProcessHeap(), 0, size ); }
	static void * (calloc)( size_t num, size_t size ) { return ::HeapAlloc( ::GetProcessHeap(), HEAP_ZERO_MEMORY, num*size ); }
	static void * (realloc)( void * ptr, size_t /*cur_size*/, size_t new_size) {
		if( NULL == ptr )
			return ::HeapAlloc( ::GetProcessHeap(), 0, new_size );
		return ::HeapReAlloc(::GetProcessHeap(), 0, ptr, new_size);
	}
	static void (free)( void * ptr, size_t /*cur_size*/ ) { ::HeapFree( ::GetProcessHeap(), 0, ptr ); }
};
#endif // def _WINDOWS_

/*END OF allocator.hxx*/
