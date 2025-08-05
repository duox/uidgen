/*array.hxx*/

template<typename T, typename A>
struct UIDGEN_INLINE_API uidgen::Tarray_traits
{
};

template<typename T, typename A, typename TR>
class UIDGEN_INLINE_API uidgen::Tarray : public TR
{
public:
	typedef TR							super;
	typedef uidgen::Tarray<T, A, TR>	self;

	class base_iterator;
	class iterator;
	class const_iterator;
	class reverse_iterator;
	class const_reverse_iterator;

			 Tarray() noexcept;
	explicit Tarray( const Tarray<T, A, TR> & str ) noexcept;
#if _MSC_VER >= 1400
	explicit Tarray( Tarray<T, A, TR> && str ) noexcept;
#endif // _MSC_VER >= 1400
			~Tarray() noexcept;

	bool	empty() const noexcept;

	bool	push_back( T t ) noexcept;

	iterator			erase( iterator it ) noexcept;
	reverse_iterator	erase( reverse_iterator it ) noexcept;

	iterator		begin() noexcept;
	iterator		end() noexcept;
	const_iterator	begin() const noexcept;
	const_iterator	end() const noexcept;
	const_iterator	cbegin() noexcept;
	const_iterator	cend() noexcept;
	const_iterator	cbegin() const noexcept;
	const_iterator	cend() const noexcept;

	reverse_iterator		rbegin() noexcept;
	reverse_iterator		rend() noexcept;
	const_reverse_iterator	rbegin() const noexcept;
	const_reverse_iterator	rend() const noexcept;
	const_reverse_iterator	crbegin() noexcept;
	const_reverse_iterator	crend() noexcept;
	const_reverse_iterator	crbegin() const noexcept;
	const_reverse_iterator	crend() const noexcept;
};
template<typename T, typename A, typename TR>
class UIDGEN_INLINE_API uidgen::Tarray<T, A, TR>::base_iterator
{
public:
	typedef base_iterator	self;

	base_iterator() noexcept;
	base_iterator( const base_iterator & it ) noexcept;
	base_iterator( T * ptr ) noexcept;

	bool	operator==( const base_iterator & obj ) const noexcept;
	bool	operator!=( const base_iterator & obj ) const noexcept;
protected:
	friend class uidgen::Tarray<T, A, TR>;

	T * m_ptr;
};
template<typename T, typename A, typename TR>
class UIDGEN_INLINE_API uidgen::Tarray<T, A, TR>::iterator : public base_iterator
{
public:
	typedef base_iterator	super;
	typedef iterator		self;

	iterator() noexcept;
	iterator( const iterator & it ) noexcept;
	iterator( T * ptr ) noexcept;

	void	operator++() noexcept;
	void	operator++( int ) noexcept;

		  T	&	operator*() noexcept;
	const T &	operator*() const noexcept;

	bool	operator> ( const iterator it ) const noexcept;
	bool	operator>=( const iterator it ) const noexcept;
	bool	operator< ( const iterator it ) const noexcept;
	bool	operator<=( const iterator it ) const noexcept;
};
template<typename T, typename A, typename TR>
class UIDGEN_INLINE_API uidgen::Tarray<T, A, TR>::const_iterator : public iterator
{
public:
	typedef iterator		super;
	typedef const_iterator	self;

	const_iterator() noexcept;
	const_iterator( const const_iterator & it ) noexcept;
	const_iterator( const T * ptr ) noexcept;

	const T	&	operator*() noexcept;
	const T &	operator*() const noexcept;
};
template<typename T, typename A, typename TR>
class UIDGEN_INLINE_API uidgen::Tarray<T, A, TR>::reverse_iterator : public base_iterator
{
public:
	typedef base_iterator		super;
	typedef reverse_iterator	self;

	reverse_iterator() noexcept;
	reverse_iterator( const reverse_iterator & it ) noexcept;
	reverse_iterator( T * ptr ) noexcept;

	void	operator++() noexcept;
	void	operator++( int ) noexcept;

		  T	&	operator*() noexcept;
	const T &	operator*() const noexcept;

	bool	operator> ( const reverse_iterator it ) const noexcept;
	bool	operator>=( const reverse_iterator it ) const noexcept;
	bool	operator< ( const reverse_iterator it ) const noexcept;
	bool	operator<=( const reverse_iterator it ) const noexcept;
};
template<typename T, typename A, typename TR>
class UIDGEN_INLINE_API uidgen::Tarray<T, A, TR>::const_reverse_iterator : public reverse_iterator
{
public:
	typedef reverse_iterator		super;
	typedef const_reverse_iterator	self;

	const_reverse_iterator() noexcept;
	const_reverse_iterator( const const_reverse_iterator & it ) noexcept;
	const_reverse_iterator( const T * ptr ) noexcept;

	const T	&	operator*() noexcept;
	const T &	operator*() const noexcept;
};

template<typename T, typename A>
class UIDGEN_INLINE_API uidgen::Theap_array_traits : public A
{
public:
	Theap_array_traits() noexcept;
	~Theap_array_traits() noexcept;

	bool	reserve( size_t n ) noexcept;
	size_t	capacity() const noexcept;
	bool	resize( size_t n, T t = T(0) ) noexcept;
	size_t	size() const noexcept;
	size_t	count() const noexcept;

	const T * data() const noexcept;
		  T * data() noexcept;

	bool	clear() noexcept;
	bool	copy( const Theap_array_traits<T, A> & str ) noexcept;
	bool	move(		Theap_array_traits<T, A> & str ) noexcept;

	bool	assign( const T * arr, size_t count ) noexcept;
	bool	remove( size_t index ) noexcept;
protected:
	T *		m_buffer;
	size_t	m_allocated;
	size_t	m_count;
};

/*END OF array.hxx*/
