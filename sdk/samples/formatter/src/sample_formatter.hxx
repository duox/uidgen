/*sample_formatter.hxx*/

class uidgen::sample_formatter : public uidgen::Iformatter
{
public:
	typedef uidgen::Iformatter		super;
	typedef sample_formatter		self;

	static const uuid		m_uuid;
	virtual const uuid &	get_uuid() const override;

	virtual bool	get_string( uidgen::string& buf, string_id_t id ) const override;

	virtual bool	format( uidgen::string & buf, uidgen::context & ctx, const uidgen::uuid & uid ) const override;
};

/*END OF sample_formatter.hxx*/
