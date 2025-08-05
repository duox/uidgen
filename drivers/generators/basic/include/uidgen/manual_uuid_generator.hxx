/*manual_generator.hxx*/

class UIDGEN_API uidgen::manual_uuid_generator : public uidgen::Igenerator
{
public:
	typedef uidgen::Igenerator		super;
	typedef manual_uuid_generator	self;

	static const uuid		m_uuid;
	virtual const uuid &	get_uuid() const override;

	virtual bool			get_string( uidgen::string& buf, string_id_t id ) const override;

	virtual bool			generate( uuid & uid, uidgen::context & ctx ) const override;
};

/*END OF DEFINE_GUID_formatter.hxx*/
