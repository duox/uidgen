/*defs.h*/
#pragma once

#define break_on_purecall()			__debugbreak()
#define unreferenced_parameter(p)	(p)

#define RESTRICT

typedef LPCSTR	PCSZ;

#define htons(x)    ( (((x) >> 8) & 0x00FF) | (((x) << 8) & 0xFF00) )
#define htonl(x)    ( (((x) >> 24) & 0x000000FF) | (((x) >> 8) & 0x0000FF00) | (((x) << 8) & 0x00FF0000) | (((x) << 24) & 0xFF000000) )

/*END OF defs.h*/
