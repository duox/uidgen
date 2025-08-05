/*Iformatter.hxx*/

class UIDGEN_API uidgen::Iformatter : public uidgen::object
{
public:

	virtual const uuid&	get_uuid() const abstract;

	enum string_id_t {
		sid_name,
		sid_description,
		sid_help_text,
		sid_count
	};
	virtual bool		get_string( uidgen::string& buf, string_id_t id ) const abstract;

	virtual bool		format( uidgen::string & buf, uidgen::context & ctx, const uidgen::uuid & uid ) const abstract;
};

/*END OF Iformatter.hxx*/
