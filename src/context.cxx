/*context.cxx*/
#include "pch.h"
#include "main.h"

uidgen::context::context():
	m_active_generator( nullptr ), m_active_formatter( nullptr ),
	m_generation_count( 1 ), m_generation_index( unsigned(-1) ),
	m_provider( nullptr ),
	m_flags( 0 )
{
	set_provider( nullptr );
}
uidgen::context::~context()
{
	remove_all_generators();
	remove_all_formatters();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Properties

unsigned uidgen::context::set_flags( unsigned new_flags )
{
	const unsigned old_flags = m_flags;
	m_flags = new_flags;
	return old_flags;
}
unsigned uidgen::context::modify_flags( unsigned flags_to_set, unsigned flags_to_clear )
{
	const unsigned old_flags = m_flags;
	m_flags = (m_flags & ~flags_to_clear) | flags_to_set;
	return old_flags;
}
unsigned uidgen::context::get_flags( unsigned mask ) const
{
	return m_flags & mask;
}

uidgen::Iprovider* uidgen::context::get_provider()
{
	return m_provider;
}
bool uidgen::context::set_provider( uidgen::Iprovider* provider )
{
	m_provider = nullptr == provider ? &m_null_provider : provider;
	return true;
}

unsigned uidgen::context::get_generation_count() const
{
	return m_generation_count;
}
bool uidgen::context::set_generation_count( unsigned count )
{
	m_generation_count = count;
	return true;
}

unsigned uidgen::context::get_generation_index() const
{
	return m_generation_index;
}
bool uidgen::context::set_generation_index( unsigned index )
{
	m_generation_index = index;
	return true;
}

const uidgen::string & uidgen::context::get_default_format_string() const
{
	return m_default_format;
}
bool uidgen::context::set_default_format_string( const uidgen::string & str )
{
	m_default_format.assign( str );
	return true;
}
bool uidgen::context::set_default_format_string( const char * str, size_t length )
{
	m_default_format.assign( str, length );
	return true;
}

const uidgen::string & uidgen::context::get_user_format_string() const
{
	return m_user_format;
}
bool uidgen::context::set_user_format_string( const uidgen::string & str )
{
	m_user_format.assign( str );
	return true;
}
bool uidgen::context::set_user_format_string( const char * str, size_t length )
{
	m_user_format.assign( str, length );
	return true;
}

const uidgen::string& uidgen::context::get_user_data() const
{
	return m_user_data;
}
bool uidgen::context::set_user_data( const uidgen::string & str )
{
	m_user_data.assign( str );
	return true;
}
bool uidgen::context::set_user_data( const char* text, size_t length )
{
	if( nullptr == text )
		m_user_data.clear();
	else
		m_user_data.assign( text, length );
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Formatters

bool uidgen::context::append_generator( uidgen::Igenerator& obj )
{
	if( m_generator_list.end() != _find_generator( &obj ) )
		return false;

	m_generator_list.push_back( &obj );

	return true;
}
bool uidgen::context::remove_generator( uidgen::Igenerator& obj )
{
	generator_list_t::iterator it = _find_generator( &obj );
	if( m_generator_list.end() == it )
		return false;

	delete *it;
	m_generator_list.erase( it );

	return true;
}
bool uidgen::context::remove_all_generators()
{
	for( generator_list_t::iterator it = m_generator_list.begin(), st = m_generator_list.end(); it != st; ++ it )
		delete* it;

	m_generator_list.clear();

	return true;
}

const uidgen::Igenerator* uidgen::context::get_active_generator() const
{
	return m_active_generator;
}
bool uidgen::context::set_active_generator( uidgen::Igenerator* obj )
{
	m_active_generator = obj;
	obj->generate( m_last_uid, *this );
	return true;
}
bool uidgen::context::set_active_generator( const char * name, size_t len )
{
	for( generator_list_t::iterator it = m_generator_list.begin(), st = m_generator_list.end(); it != st; ++ it )
	{
		uidgen::string nm;
		if( (*it)->get_string( nm, Igenerator::sid_name ) && nm.equal( name, len ) )
		{
			set_active_generator( *it );
			return true;
		}
	}
	return false;
}

uidgen::Igenerator* uidgen::context::find_generator( const uuid& uid ) const
{
	generator_list_t::const_iterator it = _find_generator( uid );
	if( m_generator_list.end() == it )
		return nullptr;
	return *it;
}

const uidgen::generator_list_t& uidgen::context::get_generator_list() const
{
	return m_generator_list;
}

uidgen::generator_list_t::const_iterator uidgen::context::_find_generator( const uuid& uid ) const
{
	generator_list_t::const_iterator it = m_generator_list.begin();
	generator_list_t::const_iterator st = m_generator_list.end();
	for( ; it != st; ++ it )
	{
		if( (*it)->get_uuid() == uid )
			break;
	}
	return it;
}
uidgen::generator_list_t::iterator uidgen::context::_find_generator( const Igenerator* generator )
{
	generator_list_t::iterator it = m_generator_list.begin();
	generator_list_t::iterator st = m_generator_list.end();
	for( ; it != st; ++ it )
	{
		if( (*it) == generator )
			break;
	}
	return it;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Formatters

bool uidgen::context::append_formatter( uidgen::Iformatter& obj )
{
	if( m_formatter_list.end() != _find_formatter( &obj ) )
		return false;

	m_formatter_list.push_back( &obj );

	return true;
}
bool uidgen::context::remove_formatter( uidgen::Iformatter& obj )
{
	formatter_list_t::iterator it = _find_formatter( &obj );
	if( m_formatter_list.end() == it )
		return false;

	delete* it;
	m_formatter_list.erase( it );

	return true;
}
bool uidgen::context::remove_all_formatters()
{
	for( formatter_list_t::iterator it = m_formatter_list.begin(), st = m_formatter_list.end(); it != st; ++ it )
		delete* it;

	m_formatter_list.clear();

	return true;
}

const uidgen::Iformatter* uidgen::context::get_active_formatter() const
{
	return m_active_formatter;
}
bool uidgen::context::set_active_formatter( uidgen::Iformatter* obj )
{
	m_active_formatter = obj;
	return true;
}

uidgen::Iformatter* uidgen::context::find_formatter( const uuid& uid ) const
{
	formatter_list_t::const_iterator it = _find_formatter( uid );
	if( m_formatter_list.end() == it )
		return nullptr;
	return *it;
}

const uidgen::formatter_list_t& uidgen::context::get_formatter_list() const
{
	return m_formatter_list;
}

uidgen::formatter_list_t::const_iterator uidgen::context::_find_formatter( const uuid& uid ) const
{
	formatter_list_t::const_iterator it = m_formatter_list.begin();
	formatter_list_t::const_iterator st = m_formatter_list.end();
	for( ; it != st; ++ it )
	{
		if( (*it)->get_uuid() == uid )
			break;
	}
	return it;
}
uidgen::formatter_list_t::iterator uidgen::context::_find_formatter( const Iformatter* formatter )
{
	formatter_list_t::iterator it = m_formatter_list.begin();
	formatter_list_t::iterator st = m_formatter_list.end();
	for( ; it != st; ++ it )
	{
		if( (*it) == formatter )
			break;
	}
	return it;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Operations

bool uidgen::context::begin_generation()
{
	// Check current state
	if( unsigned( -1 ) != m_generation_index )
		return false;

	// Begin generation
	set_generation_index( 0 );

	// Exit
	return true;
}
bool uidgen::context::generation_uid( uidgen::string & buf, uidgen::string & msg_buf )
{
	// Check current state
	if( unsigned( -1 ) == m_generation_index )
		return false;
	if( m_generation_index >= m_generation_count )
		return false;

	if( nullptr == m_active_generator )
	{
		msg_buf = "no generator selected";
		return false;
	}
	if( nullptr == m_active_formatter )
	{
		msg_buf = "no formatter selected";
		return false;
	}

	// Generate UID
	if( false == m_active_generator->generate( m_last_uid, *this ) )
	{
		msg_buf = "error generating UUID";
		return false;
	}

	// Formaty GUID
	if( false == m_active_formatter->format( buf, *this, m_last_uid ) )
	{
		msg_buf = "error formatting UID";
		return false;
	}

	// Done, advance
	set_generation_index( m_generation_index + 1 );

	// Exit
	return true;
}
bool uidgen::context::reformat_last_uid( uidgen::string & buf, uidgen::string & msg_buf )
{
	// Check current state
	if( unsigned( -1 ) == m_generation_index )
		return false;

	if( nullptr == m_active_formatter )
	{
		msg_buf = "no formatter selected";
		return false;
	}

	// Formaty GUID
	if( false == m_active_formatter->format( buf, *this, m_last_uid ) )
	{
		msg_buf = "error formatting UID";
		return false;
	}

	// Done, advance
	set_generation_index( m_generation_index + 1 );

	// Exit
	return true;
}
bool uidgen::context::end_generation()
{
	// Check current state
	if( unsigned( -1 ) == m_generation_index )
		return false;

	// End generation
	set_generation_index( unsigned(-1) );

	// Exit
	return true;
}
bool uidgen::context::can_generate_more_uids() const
{
	return m_generation_index < m_generation_count;
}


/*END OF context.cxx*/
