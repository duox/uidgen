/*string.hxx*/

template<typename C, typename A>
struct UIDGEN_INLINE_API uidgen::Tstring_traits
{
};

template<typename C, typename A, typename TR>
class UIDGEN_INLINE_API uidgen::Tstring : public TR
{
public:
	typedef TR							super;
	typedef uidgen::Tstring<C, A, TR>	self;

	Tstring();
	Tstring( const Tstring<C, A, TR> & str );
#if _MSC_VER >= 1400
	Tstring( Tstring<C, A, TR> && str );
#endif // _MSC_VER >= 1400
	~Tstring();

	bool	empty() const;
	const C * c_str() const;
		  C * c_str();

	using super::append;
	bool	append( C ch );

	self & operator=( const self & obj );
	self & operator=( const char * str );

	bool	equal( const C * str, size_t length = size_t(-1) ) const;
	bool	equal( const self & str ) const;

	using super::length;
	static size_t	length( const C * string );
	static size_t	length( const C * string, size_t max_len );

	static size_t	parse_int32( signed int * result, const C * string, size_t length = size_t(-1), unsigned radix = 10 );

	static bool		is_space( C ch );
	static bool		is_digit( C c );
	static bool		is_hexdigit( C c );

	static unsigned	from_hex_digit( C c );
	static C		to_hexdigit_lc( unsigned n );
	static C		to_hexdigit_uc( unsigned n );
};

template<typename C, typename A>
class UIDGEN_INLINE_API uidgen::Theap_string_traits : public A
{
public:
	Theap_string_traits();
	~Theap_string_traits();

	bool	reserve( size_t n );
	size_t	capacity() const;
	bool	resize( size_t n );
	bool	resize( size_t n, C ch );
	size_t	size() const;
	size_t	length() const;
	static size_t	length( const C * s, size_t length = size_t(-1) );

	const C * data() const;
		  C * data();

	bool	clear();
	bool	copy( const Theap_string_traits<C, A> & str );
	bool	move(		Theap_string_traits<C, A> & str );

	bool	assign( const Theap_string_traits<C, A> & str );
	bool	append( const Theap_string_traits<C, A> & str );
	bool	assign( const C * str, size_t length = size_t(-1) );
	bool	append( const C * str, size_t length = size_t(-1) );
protected:
	C *		m_buffer;
	size_t	m_allocated;
	size_t	m_size;
	static C	m_nullchar;
};

/*END OF string.hxx*/
