/*uuid.hxx*/

class UIDGEN_API uidgen::uuid
{
public:
    union
    {
        struct {
            unsigned long  Data1;
            unsigned short Data2;
            unsigned short Data3;
            unsigned char  Data4[8];
        };
        struct {
            unsigned long long  qwData0;
            unsigned long long  qwData1;
        };
    };
	static uuid	null;

    bool operator==( const uuid& uuid ) const;
    bool operator!=( const uuid& uuid ) const;
};

/*END OF uuid.hxx*/
