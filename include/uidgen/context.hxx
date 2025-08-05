/*context.hxx*/

class UIDGEN_API uidgen::context : public uidgen::object
{
public:
	context();
	~context();

	// Properties
public:
	static const unsigned fl_remove_leading_zeroes		= 0x0001;
	static const unsigned fl_use_angle_brackets			= 0x0002;
	static const unsigned fl_new_lines_in_user_format	= 0x0004;
	static const unsigned fl_format_upper_case			= 0x0010;
	static const unsigned fl_format_lower_case			= 0x0020;
	static const unsigned fl_format_big_endian			= 0x0040;
	unsigned	set_flags( unsigned new_flags );
	unsigned	modify_flags( unsigned flags_to_set, unsigned flags_to_clear = 0 );
	unsigned	get_flags( unsigned mask = unsigned(-1) ) const;

	uidgen::Iprovider* get_provider();
	bool set_provider( uidgen::Iprovider* provider );

	unsigned	get_generation_count() const;
	bool	set_generation_count( unsigned count );

	unsigned	get_generation_index() const;
	bool	set_generation_index( unsigned index );

	const uidgen::string & get_default_format_string() const;
	bool set_default_format_string( const uidgen::string & str );
	bool set_default_format_string( const char * str, size_t length = size_t(-1) );

	const uidgen::string & get_user_format_string() const;
	bool set_user_format_string( const uidgen::string & str );
	bool set_user_format_string( const char * str, size_t length = size_t(-1) );

	const uidgen::string& get_user_data() const;
	bool	set_user_data( const uidgen::string & str );
	bool	set_user_data( const char* text, size_t length = size_t(- 1) );
protected:
	uidgen::string	m_user_data;
	uidgen::string	m_user_format;
	uidgen::string	m_default_format;
	uidgen::null_provider	m_null_provider;
	uidgen::Iprovider *		m_provider;
	unsigned	m_generation_count;
	unsigned	m_generation_index;
	unsigned	m_flags;

	// Formatters
public:
	bool	append_generator( uidgen::Igenerator& obj );
	bool	remove_generator( uidgen::Igenerator& obj );
	bool	remove_all_generators();

	const Igenerator*	get_active_generator() const;
	bool	set_active_generator( uidgen::Igenerator * obj );
	bool	set_active_generator( const char * name, size_t len = size_t(-1) );

	Igenerator *	find_generator( const uuid& uid ) const;

	const generator_list_t& get_generator_list() const;
protected:
	generator_list_t	m_generator_list;
	uidgen::Igenerator* m_active_generator;
	generator_list_t::const_iterator	_find_generator( const uuid & uid ) const;
	generator_list_t::iterator	_find_generator( const Igenerator * generator );

	// Formatters
public:
	bool	append_formatter( uidgen::Iformatter& obj );
	bool	remove_formatter( uidgen::Iformatter& obj );
	bool	remove_all_formatters();

	const Iformatter *	get_active_formatter() const;
	bool	set_active_formatter( uidgen::Iformatter * obj );
	bool	set_active_formatter( const char * name, size_t len = size_t(-1) );

	Iformatter* find_formatter( const uuid& uid ) const;

	const formatter_list_t& get_formatter_list() const;
protected:
	formatter_list_t	m_formatter_list;
	uidgen::Iformatter* m_active_formatter;
	formatter_list_t::const_iterator	_find_formatter( const uuid& uid ) const;
	formatter_list_t::iterator	_find_formatter( const Iformatter* formatter );

	// Operations
public:
	bool	begin_generation();
	bool		can_generate_more_uids() const;
	bool		generation_uid( uidgen::string & buf, uidgen::string & msg_buf );
	bool		reformat_last_uid( uidgen::string & buf, uidgen::string & msg_buf );
	bool	end_generation();
protected:
	uidgen::uuid	m_last_uid;
};

/*END OF context.hxx*/
