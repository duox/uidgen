/*user_string_formatter.hxx*/

class UIDGEN_API uidgen::user_string_formatter : public uidgen::Iuser_formatter
{
public:
	typedef uidgen::Iuser_formatter		super;
	typedef user_string_formatter		self;

	static const uuid		m_uuid;
	virtual const uuid &	get_uuid() const override;

	virtual bool			get_string( uidgen::string& buf, string_id_t id ) const override;

	virtual const char *	get_format_string( uidgen::context & ctx ) const override;
};

/*END OF user_string_formatter.hxx*/
