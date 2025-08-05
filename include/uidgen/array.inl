/*array.inl*/

template<typename T, typename A, typename TR>
inline
uidgen::Tarray<T, A, TR>::Tarray() noexcept
{
}
template<typename T, typename A, typename TR>
inline
uidgen::Tarray<T, A, TR>::Tarray( const Tarray<T, A, TR> & arr ) noexcept
{
	copy( arr );
}
#if _MSC_VER >= 1400
template<typename T, typename A, typename TR>
inline
uidgen::Tarray<T, A, TR>::Tarray( Tarray<T, A, TR> && arr ) noexcept
{
	move( arr );
}
#endif // _MSC_VER >= 1400
template<typename T, typename A, typename TR>
inline
uidgen::Tarray<T, A, TR>::~Tarray() noexcept
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T, typename A, typename TR>
inline
bool uidgen::Tarray<T, A, TR>::empty() const noexcept
{
	return 0 == size();
}

template<typename T, typename A, typename TR>
inline
bool uidgen::Tarray<T, A, TR>::push_back( T t ) noexcept
{
	if( m_count == m_allocated )
	{
		if( !reserve( m_count + 1 ) )	// ask for one new item; the real reservation policy depends on the traits
			return false;
	}

	m_buffer[m_count] = t;
	++ m_count;

	return true;
}

template<typename T, typename A, typename TR>
inline
typename uidgen::Tarray<T, A, TR>::iterator
uidgen::Tarray<T, A, TR>::erase( iterator it ) noexcept
{
	return it;
}
template<typename T, typename A, typename TR>
inline
typename uidgen::Tarray<T, A, TR>::reverse_iterator
uidgen::Tarray<T, A, TR>::erase( reverse_iterator it ) noexcept
{
	return it;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T, typename A, typename TR>
inline
typename uidgen::Tarray<T, A, TR>::iterator
uidgen::Tarray<T, A, TR>::begin() noexcept
{
	return iterator( m_buffer );
}
template<typename T, typename A, typename TR>
inline
typename uidgen::Tarray<T, A, TR>::iterator
uidgen::Tarray<T, A, TR>::end() noexcept
{
	return iterator( m_buffer + m_count );
}
template<typename T, typename A, typename TR>
inline
typename uidgen::Tarray<T, A, TR>::const_iterator
uidgen::Tarray<T, A, TR>::begin() const noexcept
{
	return const_iterator( m_buffer );
}
template<typename T, typename A, typename TR>
inline
typename uidgen::Tarray<T, A, TR>::const_iterator
uidgen::Tarray<T, A, TR>::end() const noexcept
{
	return const_iterator( m_buffer + m_count );
}
template<typename T, typename A, typename TR>
inline
typename uidgen::Tarray<T, A, TR>::const_iterator
uidgen::Tarray<T, A, TR>::cbegin() noexcept
{
	return const_iterator( m_buffer );
}
template<typename T, typename A, typename TR>
inline
typename uidgen::Tarray<T, A, TR>::const_iterator
uidgen::Tarray<T, A, TR>::cend() noexcept
{
	return const_iterator( mm_buffer_ptr + m_count );
}
template<typename T, typename A, typename TR>
inline
typename uidgen::Tarray<T, A, TR>::const_iterator
uidgen::Tarray<T, A, TR>::cbegin() const noexcept
{
	return const_iterator( m_buffer );
}
template<typename T, typename A, typename TR>
inline
typename uidgen::Tarray<T, A, TR>::const_iterator
uidgen::Tarray<T, A, TR>::cend() const noexcept
{
	return const_iterator( m_buffer + m_count );
}

template<typename T, typename A, typename TR>
inline
typename uidgen::Tarray<T, A, TR>::reverse_iterator
uidgen::Tarray<T, A, TR>::rbegin() noexcept
{
	return reverse_iterator( m_buffer + m_count - 1 );
}
template<typename T, typename A, typename TR>
inline
typename uidgen::Tarray<T, A, TR>::reverse_iterator
uidgen::Tarray<T, A, TR>::rend() noexcept
{
	return reverse_iterator( m_buffer - 1 );
}
template<typename T, typename A, typename TR>
inline
typename uidgen::Tarray<T, A, TR>::const_reverse_iterator
uidgen::Tarray<T, A, TR>::rbegin() const noexcept
{
	return const_reverse_iterator( m_buffer - m_count - 1 );
}
template<typename T, typename A, typename TR>
inline
typename uidgen::Tarray<T, A, TR>::const_reverse_iterator
uidgen::Tarray<T, A, TR>::rend() const noexcept
{
	return const_reverse_iterator( m_buffer - 1 );
}
template<typename T, typename A, typename TR>
inline
typename uidgen::Tarray<T, A, TR>::const_reverse_iterator
uidgen::Tarray<T, A, TR>::crbegin() noexcept
{
	return const_reverse_iterator( m_buffer + m_count - 1 );
}
template<typename T, typename A, typename TR>
inline
typename uidgen::Tarray<T, A, TR>::const_reverse_iterator
uidgen::Tarray<T, A, TR>::crend() noexcept
{
	return const_reverse_iterator( m_buffer - 1 );
}
template<typename T, typename A, typename TR>
inline
typename uidgen::Tarray<T, A, TR>::const_reverse_iterator
uidgen::Tarray<T, A, TR>::crbegin() const noexcept
{
	return const_reverse_iterator( m_buffer + m_count - 1 );
}
template<typename T, typename A, typename TR>
inline
typename uidgen::Tarray<T, A, TR>::const_reverse_iterator
uidgen::Tarray<T, A, TR>::crend() const noexcept
{
	return const_reverse_iterator( m_buffer - 1 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T, typename A, typename TR>
inline
uidgen::Tarray<T, A, TR>::base_iterator::base_iterator() noexcept:
	m_ptr( -1 )
{
}
template<typename T, typename A, typename TR>
inline
uidgen::Tarray<T, A, TR>::base_iterator::base_iterator( const base_iterator & it ) noexcept:
	m_ptr( it.m_ptr )
{
}
template<typename T, typename A, typename TR>
inline
uidgen::Tarray<T, A, TR>::base_iterator::base_iterator( T * ptr ) noexcept:
	m_ptr( ptr )
{
}

template<typename T, typename A, typename TR>
inline
bool
uidgen::Tarray<T, A, TR>::base_iterator::operator==( const base_iterator & obj ) const noexcept
{
	return m_ptr == obj.m_ptr;
}
template<typename T, typename A, typename TR>
inline
bool
uidgen::Tarray<T, A, TR>::base_iterator::operator!=( const base_iterator & obj ) const noexcept
{
	return m_ptr != obj.m_ptr;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T, typename A, typename TR>
inline
uidgen::Tarray<T, A, TR>::iterator::iterator() noexcept
{
}
template<typename T, typename A, typename TR>
inline
uidgen::Tarray<T, A, TR>::iterator::iterator( const iterator & it ) noexcept :
	super( it )
{
}
template<typename T, typename A, typename TR>
inline
uidgen::Tarray<T, A, TR>::iterator::iterator( T * ptr ) noexcept :
	super( ptr )
{
}

template<typename T, typename A, typename TR>
inline
void
uidgen::Tarray<T, A, TR>::iterator::operator++() noexcept
{
	++ m_ptr;
}
template<typename T, typename A, typename TR>
inline
void
uidgen::Tarray<T, A, TR>::iterator::operator++( int ) noexcept
{
	++ m_ptr;
}

template<typename T, typename A, typename TR>
inline
T &
uidgen::Tarray<T, A, TR>::iterator::operator*() noexcept
{
	return *m_ptr;
}
template<typename T, typename A, typename TR>
inline
const T &
uidgen::Tarray<T, A, TR>::iterator::operator*() const noexcept
{
	return *m_ptr;
}

template<typename T, typename A, typename TR>
inline
bool uidgen::Tarray<T, A, TR>::iterator::operator>( const iterator it ) const noexcept
{
	return m_ptr > it.m_ptr;
}
template<typename T, typename A, typename TR>
inline
bool
uidgen::Tarray<T, A, TR>::iterator::operator>=( const iterator it ) const noexcept
{
	return m_ptr >= it.m_ptr;
}
template<typename T, typename A, typename TR>
inline
bool
uidgen::Tarray<T, A, TR>::iterator::operator<( const iterator it ) const noexcept
{
	return m_ptr < it.m_ptr;
}
template<typename T, typename A, typename TR>
inline
bool
uidgen::Tarray<T, A, TR>::iterator::operator<=( const iterator it ) const noexcept
{
	return m_ptr <= it.m_ptr;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T, typename A, typename TR>
inline
uidgen::Tarray<T, A, TR>::const_iterator::const_iterator() noexcept
{
}
template<typename T, typename A, typename TR>
inline
uidgen::Tarray<T, A, TR>::const_iterator::const_iterator( const const_iterator & it ) noexcept :
	super( it )
{
}
template<typename T, typename A, typename TR>
inline
uidgen::Tarray<T, A, TR>::const_iterator::const_iterator( const T * ptr ) noexcept :
	super( const_cast<T *>(ptr) )
{
}

template<typename T, typename A, typename TR>
inline
const T &
uidgen::Tarray<T, A, TR>::const_iterator::operator*() noexcept
{
	return *m_ptr;
}
template<typename T, typename A, typename TR>
inline
const T &
uidgen::Tarray<T, A, TR>::const_iterator::operator*() const noexcept
{
	return *m_ptr;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T, typename A, typename TR>
inline
uidgen::Tarray<T, A, TR>::reverse_iterator::reverse_iterator() noexcept
{
}
template<typename T, typename A, typename TR>
inline
uidgen::Tarray<T, A, TR>::reverse_iterator::reverse_iterator( const reverse_iterator & it ) noexcept :
	super( it )
{
}
template<typename T, typename A, typename TR>
inline
uidgen::Tarray<T, A, TR>::reverse_iterator::reverse_iterator( T * ptr ) noexcept :
	super( ptr )
{
}

template<typename T, typename A, typename TR>
inline
void
uidgen::Tarray<T, A, TR>::reverse_iterator::operator++() noexcept
{
	++ m_ptr;
}
template<typename T, typename A, typename TR>
inline
void
uidgen::Tarray<T, A, TR>::reverse_iterator::operator++( int ) noexcept
{
	++ m_ptr;
}

template<typename T, typename A, typename TR>
inline
T &
uidgen::Tarray<T, A, TR>::reverse_iterator::operator*() noexcept
{
	return *m_ptr;
}
template<typename T, typename A, typename TR>
inline
const T &
uidgen::Tarray<T, A, TR>::reverse_iterator::operator*() const noexcept
{
	return *m_ptr;
}

template<typename T, typename A, typename TR>
inline
bool uidgen::Tarray<T, A, TR>::reverse_iterator::operator>( const reverse_iterator it ) const noexcept
{
	return m_ptr > it.m_ptr;
}
template<typename T, typename A, typename TR>
inline
bool
uidgen::Tarray<T, A, TR>::reverse_iterator::operator>=( const reverse_iterator it ) const noexcept
{
	return m_ptr >= it.m_ptr;
}
template<typename T, typename A, typename TR>
inline
bool
uidgen::Tarray<T, A, TR>::reverse_iterator::operator<( const reverse_iterator it ) const noexcept
{
	return m_ptr < it.m_ptr;
}
template<typename T, typename A, typename TR>
inline
bool
uidgen::Tarray<T, A, TR>::reverse_iterator::operator<=( const reverse_iterator it ) const noexcept
{
	return m_ptr <= it.m_ptr;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T, typename A, typename TR>
inline
uidgen::Tarray<T, A, TR>::const_reverse_iterator::const_reverse_iterator() noexcept
{
}
template<typename T, typename A, typename TR>
inline
uidgen::Tarray<T, A, TR>::const_reverse_iterator::const_reverse_iterator( const const_reverse_iterator & it ) noexcept :
	super( it )
{
}
template<typename T, typename A, typename TR>
inline
uidgen::Tarray<T, A, TR>::const_reverse_iterator::const_reverse_iterator( const T * ptr ) noexcept :
	super( const_cast<T *>(ptr) )
{
}

template<typename T, typename A, typename TR>
inline
const T &
uidgen::Tarray<T, A, TR>::const_reverse_iterator::operator*() noexcept
{
	return *m_ptr;
}
template<typename T, typename A, typename TR>
inline
const T &
uidgen::Tarray<T, A, TR>::const_reverse_iterator::operator*() const noexcept
{
	return *m_ptr;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T, typename A>
inline
uidgen::Theap_array_traits<T, A>::Theap_array_traits() noexcept:
	m_buffer( nullptr ), m_allocated( 0 ), m_count( 0 )
{
}
template<typename T, typename A>
inline
uidgen::Theap_array_traits<T, A>::~Theap_array_traits() noexcept
{
	A::free( m_buffer, (m_allocated + 1) * sizeof(T) );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T, typename A>
inline
bool uidgen::Theap_array_traits<T, A>::reserve( size_t n ) noexcept
{
	if( n <= m_allocated )
		return true;

	void * new_buffer = A::realloc( m_buffer, (m_allocated + 1) * sizeof(T), (n + 1) * sizeof(T) );
	if( nullptr == new_buffer )
		return false;

	m_buffer = (T *) new_buffer;
	m_allocated = n;

	return true;
}
template<typename T, typename A>
inline
size_t uidgen::Theap_array_traits<T, A>::capacity() const noexcept
{
	return m_allocated;
}
template<typename T, typename A>
inline
bool uidgen::Theap_array_traits<T, A>::resize( size_t n, T ch ) noexcept
{
	if( m_count == n )
		return true;

	if( m_count > n )
	{
		m_buffer[n] = T(0);
		m_count = n;
		return true;
	}

	if( n > m_allocated )
	{
		if( !reserve( n ) )
			return false;
	}

	while( m_count < n )
		m_buffer[m_count ++] = ch;
	m_buffer[n] = T(0);

	return true;
}
template<typename T, typename A>
inline
size_t uidgen::Theap_array_traits<T, A>::size() const noexcept
{
	return m_count;
}
template<typename T, typename A>
inline
size_t uidgen::Theap_array_traits<T, A>::count() const noexcept
{
	return m_count;
}

template<typename T, typename A>
inline
const T * uidgen::Theap_array_traits<T, A>::data() const noexcept
{
	return m_buffer;
}
template<typename T, typename A>
inline
T * uidgen::Theap_array_traits<T, A>::data() noexcept
{
	return m_buffer;
}

template<typename T, typename A>
inline
bool uidgen::Theap_array_traits<T, A>::clear() noexcept
{
	A::free( m_buffer, (m_allocated + 1) * sizeof(T) );
	m_buffer	= nullptr;
	m_allocated = 0;
	m_count		= 0;
	return true;
}

template<typename T, typename A>
inline
bool uidgen::Theap_array_traits<T, A>::copy( const Theap_array_traits<T, A> & str ) noexcept
{
	T * buf;
	T * dst;
	T * end_dst;
	const T * src;

	buf = (T *) A::malloc( (str.m_allocated + 1) * sizeof(T) );
	if( nullptr == buf )
		return false;
	m_allocated = str.m_allocated;

	A::free( m_buffer, (m_allocated + 1) * sizeof(T) );	// free and then malloc buffer to avoid memory copy during realloc
	m_buffer = buf;

	src = str.data();
	for( dst = buf, end_dst = buf + str.m_count; dst < end_dst; ++ dst, ++ src )
		*dst = *src;
	*dst = T(0);
	m_count = str.m_count;

	return true;
}
template<typename T, typename A>
inline
bool uidgen::Theap_array_traits<T, A>::move( Theap_array_traits<T, A> & str ) noexcept
{
	A::free( m_buffer, (m_allocated + 1) * sizeof(T) );

	m_allocated = str.m_allocated;
	m_buffer	= str.m_buffer;
	m_count		= str.m_count;

	str.m_buffer	= nullptr;
	str.m_allocated = 0;
	str.m_count		= 0;

	return true;
}

template<typename T, typename A>
inline
bool uidgen::Theap_array_traits<T, A>::assign( const T * str, size_t length ) noexcept
{
	// If null array is given, clean up the array
	if( nullptr == str || T(0) == *str )
		return clear();

	length = Theap_array_traits<T, A>::length( str, length );

	T * buf = (T *) A::malloc( (length + 1) * sizeof(T) );
	if( nullptr == buf )
		return false;
	m_allocated = length * sizeof(T);

	A::free( m_buffer, (m_allocated + 1) * sizeof(T) );	// free and then malloc buffer to avoid memory copy during realloc
	m_buffer = buf;

	{
	T * dst = buf;
	T * end_dst = buf + length;
	while( dst < end_dst )
		*dst++ = *str++;
	*dst = T(0);
	}

	return true;
}

/*END OF array.inl*/
