/*string.h*/
#pragma once

#define RtlCharIsDigit(c)		('0' <= (c) && (c) <= '9')
#define RtlCharIsHexDigit(c)	( RtlCharIsDigit(c) || ('A' <= (c) && (c) <= 'F') || ('a' <= (c) && (c) <= 'f') )
#define RtlCharIsSpace(c)		( '\x20' == (c) || '\f' == (c) || '\n' == (c) || '\t' == (c) || '\r' == (c) || '\v' == (c) )

#define RtlCharToHexDigit(c)	(\
	RtlCharIsDigit(c) ?			(c) - '0':\
	'A' <= (c) && (c) <= 'F' ?	(c) - 'A' + 10:\
	'a' <= (c) && (c) <= 'f' ?	(c) - 'a' + 10:\
								-1 )
#define RtlCharFromHexDigitLC(n)	((char)(\
	0	<= (n) && (n) <  10 ?	(n) + '0':\
	10	<= (n) && (n) <= 15 ?	(n) - 10 + 'a':\
								'\0' ))
#define RtlCharFromHexDigitUC(n)	((char)(\
	0	<= (n) && (n) <  10 ?	(n) + '0':\
	10	<= (n) && (n) <= 15 ?	(n) - 10 + 'A':\
								'\0' ))

PCSZ UIDGEN_RTL_API RtlStrParseInt32( LONG * Result, PCSZ String, PCSZ * EndPtr, UINT Radix );

/*END OF string.h*/
