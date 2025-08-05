/*string.inl*/

template<typename C, typename A, typename TR>
inline
uidgen::Tstring<C, A, TR>::Tstring()
{
}
template<typename C, typename A, typename TR>
inline
uidgen::Tstring<C, A, TR>::Tstring( const Tstring<C, A, TR> & str )
{
	assign( str );
}
#if _MSC_VER >= 1400
template<typename C, typename A, typename TR>
inline
uidgen::Tstring<C, A, TR>::Tstring( Tstring<C, A, TR> && str )
{
	move( str );
}
#endif // _MSC_VER >= 1400
template<typename C, typename A, typename TR>
inline
uidgen::Tstring<C, A, TR>::~Tstring()
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename C, typename A, typename TR>
inline
bool uidgen::Tstring<C, A, TR>::empty() const
{
	return 0 == length();
}

template<typename C, typename A, typename TR>
inline
const C * uidgen::Tstring<C, A, TR>::c_str() const
{
	return super::data();
}
template<typename C, typename A, typename TR>
inline
C * uidgen::Tstring<C, A, TR>::c_str()
{
	return super::data();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename C, typename A, typename TR>
inline
bool uidgen::Tstring<C, A, TR>::append( C ch )
{
	return super::append( (const C *) & ch, 1);
}

template<typename C, typename A, typename TR>
inline
uidgen::Tstring<C, A, TR> &
uidgen::Tstring<C, A, TR>::operator=( const uidgen::Tstring<C, A, TR> & obj )
{
	assign( obj );
	return *this;
}
template<typename C, typename A, typename TR>
inline
uidgen::Tstring<C, A, TR> &
uidgen::Tstring<C, A, TR>::operator=( const char * str )
{
	assign( str );
	return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename C, typename A, typename TR>
inline
bool
uidgen::Tstring<C, A, TR>::equal( const C * str, size_t length ) const
{
	if( -1 == length )
		return !lstrcmp( m_buffer, str );
	else
		return !StrCmpNA( m_buffer, str, (int) length );
}
template<typename C, typename A, typename TR>
inline
bool
uidgen::Tstring<C, A, TR>::equal( const self & str ) const
{
	return !lstrcmp( m_data, str.m_data );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename C, typename A, typename TR>
inline
size_t
uidgen::Tstring<C, A, TR>::length( const C * string )
{
	size_t len;

	if( nullptr == string )
		return 0;

	for( len = 0; '\0' != *string ++; )
		++ len;

	return len;
}
template<typename C, typename A, typename TR>
inline
size_t
uidgen::Tstring<C, A, TR>::length( const C * string, size_t max_len )
{
	size_t len;

	if( size_t( -1 ) == max_len )
		return length( string );

	if( nullptr == string )
		return 0;

	for( len = 0; '\0' != *string ++ && len < max_len; )
		++ len;

	return len;
}

template<typename C, typename A, typename TR>
inline
size_t
uidgen::Tstring<C, A, TR>::parse_int32( signed int * result, const C * string, size_t length, unsigned radix )
{
	const C * string_start = string;
	const C * string_end;
	signed sign = 0;
	signed value = 0;
	signed next_value;

	// Calculate length of the string, if needed
	if( size_t( -1 ) == length )
	{
		length = Tstring<C, A, TR>::length( string );
		if( size_t( -1 ) == length )
			return 0;
	}
	if( 0 == length )
		return 0;
	string_end = string + length;

	// Skip initial spaces
	while( string < string_end && is_space( *string ) )
		++string;
	if( string >= string_end )
		return 0;

	// Parse sign
	if( '-' == *string )
		++ string,
		sign = 0x80000000;	// sign bit
	if( '+' == *string )
		++ string;

	// Skip spaces between the sign and the number
	while( string < string_end && is_space( *string ) )
		++string;
	if( string >= string_end )
		return 0;

	// Parse numeric prefix
	if( '0' == *string )	// override radix if prefix found
	{
		++ string;
		if( string >= string_end )
			return 0;

		if( 'X' == *string || 'x' == *string )
			++ string,
			radix = 16;
		else if( 0 == radix )
		{
			if( 'B' == *string || 'b' == *string )
				++ string,
				radix = 2;
			else if( 0 == radix )
				radix = 8;		// treat leading '0' as an octal prefix only if radix hasn't been specified
		}
	}
	else
	{
		if( 0 == radix )
			radix = 10;
	}
	if( string >= string_end )
		return 0;

	// Parse digits
	while( string < string_end && '\0' != *string )
	{
		unsigned digit = *string - '0';
		if( digit > radix - 1 )
			break;
		++ string;

		next_value = value * radix + digit;
		if( next_value < value )
			break_on_purecall();// Status = STATUS_ERROR_OVERFLOW;
		value = next_value;
	}

	// Store result and exit
	*result = sign | value;
	return string - string_start;
}

template<typename C, typename A, typename TR>
inline
bool
uidgen::Tstring<C, A, TR>::is_space( C c )
{
	return '\x20' == c || '\f' == c || '\n' == c || '\t' == c || '\r' == c || '\v' == c;
}
template<typename C, typename A, typename TR>
inline
bool
uidgen::Tstring<C, A, TR>::is_digit( C c )
{
	return '0' <= c && c <= '9';
}
template<typename C, typename A, typename TR>
inline
bool
uidgen::Tstring<C, A, TR>::is_hexdigit( C c )
{
	return is_digit( c ) || ('A' <= c && c <= 'F') || ('a' <= c && c <= 'f');
}

template<typename C, typename A, typename TR>
inline
unsigned
uidgen::Tstring<C, A, TR>::from_hex_digit( C c )
{
	return	   is_digit( c ) ? c - '0' :
		'A' <= c && c <= 'F' ? c - 'A' + 10 :
		'a' <= c && c <= 'f' ? c - 'a' + 10 :
		-1;
}
template<typename C, typename A, typename TR>
inline
C
uidgen::Tstring<C, A, TR>::to_hexdigit_lc( unsigned n )
{
	return C(
		 0 <= n && n <  10 ? n + '0' :
		10 <= n && n <= 15 ? n - 10 + 'a' :
		'\0');
}
template<typename C, typename A, typename TR>
inline
C
uidgen::Tstring<C, A, TR>::to_hexdigit_uc( unsigned n )
{
	return C(
		 0 <= n && n <  10 ? n + '0' :
		10 <= n && n <= 15 ? n - 10 + 'A' :
		'\0');
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename C, typename A>
inline
uidgen::Theap_string_traits<C, A>::Theap_string_traits():
	m_buffer( nullptr ), m_allocated( 0 ), m_size( 0 )
{
}
template<typename C, typename A>
inline
uidgen::Theap_string_traits<C, A>::~Theap_string_traits()
{
	(A::free)( m_buffer, (m_allocated + 1) * sizeof(C) );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


template<typename C, typename A>
C uidgen::Theap_string_traits<C, A>::m_nullchar = C(0);

template<typename C, typename A>
inline
bool uidgen::Theap_string_traits<C, A>::reserve( size_t n )
{
	if( n <= m_allocated )
		return true;

	void * new_buffer = (A::realloc)( m_buffer, nullptr == m_buffer ? 0 : (m_allocated + 1) * sizeof(C), (n + 1) * sizeof(C) );
	if( nullptr == new_buffer )
		return false;

	m_buffer = (C *) new_buffer;
	m_allocated = n;

	return true;
}
template<typename C, typename A>
inline
size_t uidgen::Theap_string_traits<C, A>::capacity() const
{
	return m_allocated;
}
template<typename C, typename A>
inline
bool uidgen::Theap_string_traits<C, A>::resize( size_t n )
{
	if( m_size == n )
		return true;

	if( m_size > n )
	{
		m_buffer[n] = C(0);
		m_size = n;
		return true;
	}

	if( n > m_allocated )
	{
		if( !reserve( n ) )
			return false;
	}

	m_buffer[n] = C(0);
	m_size = n;

	return true;
}
template<typename C, typename A>
inline
bool uidgen::Theap_string_traits<C, A>::resize( size_t n, C ch )
{
	if( m_size == n )
		return true;

	if( m_size > n )
	{
		m_buffer[n] = C(0);
		m_size = n;
		return true;
	}

	if( n > m_allocated )
	{
		if( !reserve( n ) )
			return false;
	}

	while( m_size < n )
		m_buffer[m_size ++] = ch;
	m_buffer[n] = C(0);

	return true;
}
template<typename C, typename A>
inline
size_t uidgen::Theap_string_traits<C, A>::size() const
{
	return m_size;
}
template<typename C, typename A>
inline
size_t uidgen::Theap_string_traits<C, A>::length() const
{
	return m_size;
}
template<typename C, typename A>
inline
size_t uidgen::Theap_string_traits<C, A>::length( const C * s, size_t length )
{
	const C * eol = s;
	if( size_t(-1) == length )
	{
		while( C( 0 ) != *eol )
			++ eol;
	}
	else
	{
		const C * end_s = s + length;
		while( C(0) != *eol && eol < end_s )
			++ eol;
	}
	return eol - s;
}

template<typename C, typename A>
inline
const C * uidgen::Theap_string_traits<C, A>::data() const
{
	return nullptr == m_buffer ? (const C *)&m_nullchar : m_buffer;
}
template<typename C, typename A>
inline
C * uidgen::Theap_string_traits<C, A>::data()
{
	return nullptr == m_buffer ? (C *)&m_nullchar : m_buffer;
}

template<typename C, typename A>
inline
bool uidgen::Theap_string_traits<C, A>::clear()
{
	(A::free)( m_buffer, (m_allocated + 1) * sizeof(C) );
	m_buffer	= nullptr;
	m_allocated = 0;
	m_size		= 0;
	return true;
}

template<typename C, typename A>
inline
bool uidgen::Theap_string_traits<C, A>::copy( const Theap_string_traits<C, A> & str )
{
	C * buf;
	C * dst;
	C * end_dst;
	const C * src;

	buf = (C *) (A::malloc)( (str.m_allocated + 1) * sizeof(C) );
	if( nullptr == buf )
		return false;
	m_allocated = str.m_allocated;

	(A::free)( m_buffer, (m_allocated + 1) * sizeof(C) );	// free and then malloc buffer to avoid memory copy during realloc
	m_buffer = buf;

	src = str.data();
	for( dst = buf, end_dst = buf + str.m_size; dst < end_dst; ++ dst, ++ src )
		*dst = *src;
	*dst = C(0);
	m_size = str.m_size;

	return true;
}
template<typename C, typename A>
inline
bool uidgen::Theap_string_traits<C, A>::move( Theap_string_traits<C, A> & str )
{
	A::free( m_buffer, (m_allocated + 1) * sizeof(C) );

	m_allocated = str.m_allocated;
	m_buffer	= str.m_buffer;
	m_size		= str.m_size;

	str.m_buffer	= nullptr;
	str.m_allocated = 0;
	str.m_size		= 0;

	return true;
}

template<typename C, typename A>
inline
bool uidgen::Theap_string_traits<C, A>::assign( const C * str, size_t length )
{
	// If null string is given, clean up the string
	if( nullptr == str || C(0) == *str )
		return clear();

	length = Theap_string_traits<C, A>::length( str, length );

	C * buf = (C *) (A::malloc)( (length + 1) * sizeof(C) );
	if( nullptr == buf )
		return false;
	m_allocated = length * sizeof(C);

	(A::free)( m_buffer, (m_allocated + 1) * sizeof(C) );	// free and then malloc buffer to avoid memory copy during realloc
	m_buffer = buf;

	{
	C * dst = buf;
	C * end_dst = buf + length;
	while( dst < end_dst )
		*dst++ = *str++;
	*dst = C(0);
	}
	m_size = length;

	return true;
}
template<typename C, typename A>
inline
bool uidgen::Theap_string_traits<C, A>::assign( const Theap_string_traits<C, A> & str )
{
	return copy( str );
}
template<typename C, typename A>
inline
bool uidgen::Theap_string_traits<C, A>::append( const C * str, size_t length )
{
	// If null string is given, do nothing
	if( nullptr == str || C(0) == *str )
		return true;

	length = Theap_string_traits<C, A>::length( str, length );

	const size_t offset = m_size;
	if( !resize( m_size + length ) )
		return false;

	{
	C * dst = m_buffer + offset;
	C * end_dst = dst + length;
	while( dst < end_dst )
		*dst++ = *str++;
	*dst = C(0);
	}

	return true;
}
template<typename C, typename A>
inline
bool uidgen::Theap_string_traits<C, A>::append( const Theap_string_traits<C, A> & str )
{
	return append( str.m_buffer, str.m_size );
}

/*END OF string.inl*/
