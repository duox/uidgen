/*Igenerator.hxx*/

class UIDGEN_API uidgen::Igenerator : public uidgen::object
{
public:

	virtual const uuid& get_uuid() const abstract;

	enum string_id_t {
		sid_name,
		sid_description,
		sid_help_text,
		sid_count
	};
	virtual bool		get_string( uidgen::string & buf, string_id_t id ) const abstract;

	virtual bool		generate( uuid & uid, uidgen::context & ctx ) const abstract;
};

/*END OF Igenerator.hxx*/
