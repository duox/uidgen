/*Iprovider.hxx*/

class UIDGEN_API uidgen::Iprovider : public uidgen::object
{
public:

	virtual void printf( const char* format, ... ) abstract;
};

class UIDGEN_API uidgen::null_provider : public uidgen::Iprovider
{
	virtual void printf( const char *, ... ) override;
};

/*END OF Iprovider.hxx*/
