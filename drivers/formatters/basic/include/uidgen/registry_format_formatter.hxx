/*registry_format_formatter.hxx*/

class UIDGEN_API uidgen::registry_format_formatter : public uidgen::Iuser_formatter
{
public:
	typedef uidgen::Iuser_formatter			super;
	typedef registry_format_formatter		self;

	static const uuid		m_uuid;
	virtual const uuid &	get_uuid() const override;

	virtual bool			get_string( uidgen::string& buf, string_id_t id ) const override;

	virtual const char *	get_format_string( uidgen::context & ctx ) const override;
};

/*END OF registry_format_formatter.hxx*/
