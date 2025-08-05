/*Iuser_formatter.hxx*/

class UIDGEN_API uidgen::Iuser_formatter : public uidgen::Iformatter
{
public:

	virtual const char * get_format_string( uidgen::context & ctx ) const abstract;
	virtual bool		format( uidgen::string & buf, uidgen::context & ctx, const uidgen::uuid & uid ) const override;

	static int parse_hex( const char * src, size_t src_size, size_t min_digits, size_t max_digits, const char ** src_ptr );
	static int format_hex( char * dst, size_t dst_size, unsigned long data, int type, bool leading_zero, bool upper_case );
};

/*END OF Iuser_formatter.hxx*/
