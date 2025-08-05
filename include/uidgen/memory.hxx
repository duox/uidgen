/*memory.hxx*/

class UIDGEN_INLINE_API uidgen::memory
{
public:
	static void *	copy( void * RESTRICT dst_ptr, const void * RESTRICT src_ptr, size_t count );
	static void *	move( void * RESTRICT dst_ptr, const void * RESTRICT src_ptr, size_t count );
	static int		compare( const void * RESTRICT ptr1, const void * RESTRICT ptr2, size_t count );
	static bool		equal( const void * RESTRICT ptr1, const void * RESTRICT ptr2, size_t count );
};

/*END OF memory.hxx*/
