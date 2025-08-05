/*memory.inl*/

inline
void * uidgen::memory::copy( void * RESTRICT dst_ptr, const void * RESTRICT src_ptr, size_t count )
{
	unsigned char * dst;
	unsigned char * dst_end;
	const unsigned char * src;

	if( dst_ptr == src_ptr )
		return dst_ptr;
	if( 0 == count )
		return dst_ptr;

	dst = (unsigned char *) dst_ptr;
	dst_end = dst + count;
	src = (const unsigned char *) src_ptr;

	while( dst < dst_end )
		*dst++ = *src++;

	return dst_ptr;
}

inline
void * uidgen::memory::move( void * RESTRICT dst_ptr, const void * RESTRICT src_ptr, size_t count )
{
	unsigned char * dst;
	unsigned char * dst_end;
	const unsigned char * src;
	const unsigned char * src_end;

	if( dst_ptr == src_ptr )
		return dst_ptr;
	if( 0 == count )
		return dst_ptr;

	dst = (unsigned char *) dst_ptr;
	dst_end = dst + count;
	src = (const unsigned char *) src_ptr;
	src_end = src + count;

	if( dst < src )
	{
		while( dst < dst_end )
			*dst++ = *src++;
	}
	else
	{
		do
			*--dst_end = *--src_end;
		while( dst < dst_end );
	}

	return dst_ptr;
}

inline
int uidgen::memory::compare( const void * RESTRICT ptr1, const void * RESTRICT ptr2, size_t count )
{
	const unsigned char * byte1 = (const unsigned char *) ptr1;
	const unsigned char * byte2 = (const unsigned char *) ptr2;
	const unsigned char * end_byte1 = byte1 + count;
	INT result = FALSE;
	while( byte1 < end_byte1 )
	{
		result = (INT) *byte1 - *byte2;
		if( 0 != result )
			break;
		byte1 ++;
		byte2 ++;
	}
	return result;
}

inline
bool uidgen::memory::equal( const void * RESTRICT ptr1, const void * RESTRICT ptr2, size_t count )
{
	return 0 == compare( ptr1, ptr2, count );
}

/*END OF memory.inl*/
