/*uidgen.h*/
#pragma once

#pragma warning(disable:4481)	// : nonstandard extension used : override specifier 'abstract'
#pragma warning(disable:4201)	// : nonstandard extension used : nameless struct / union

#ifdef FINAL
# define _CRT_SECURE_INVALID_PARAMETER(expr)
#endif // def FINAL

#include <windows.h>
#include <shlwapi.h>

#include "../rtl/include/uidgen-rtl.h"

#ifndef countof
# define countof(x)		( sizeof(x)/sizeof(*(x)) )
#endif // ndef countof

#if defined _MSC_VER && _MSC_VER < 1400
# define noexcept	throw()
# define abstract	=0
# define override
# define nullptr	NULL
#endif // _MSC_VER < 1300

#ifndef break_on_purecall
# define break_on_purecall()		__debugbreak()
#endif // ndef break_on_purecall

#ifndef unreferenced_parameter
# define unreferenced_parameter(p)	(p)
#endif // ndef unreferenced_parameter

#ifndef RESTRICT
# define RESTRICT
#endif // ndef RESTRICT

typedef LPCSTR	PCSZ;

#ifndef htons
# define htons(x)    ( (((x) >> 8) & 0x00FF) | (((x) << 8) & 0xFF00) )
#endif // ndef htons
#ifndef htonl
# define htonl(x)    ( (((x) >> 24) & 0x000000FF) | (((x) >> 8) & 0x0000FF00) | (((x) << 8) & 0x00FF0000) | (((x) << 24) & 0xFF000000) )
#endif // ndef htonl

#if defined UIDGEN_STATIC
# define UIDGEN_API
# define UIDGEN_INLINE_API
#elif defined UIDGEN_EXPORTS
# define UIDGEN_API			__declspec(dllexport)
# define UIDGEN_INLINE_API	__declspec(dllexport)
#else
# define UIDGEN_API			__declspec(dllimport)
# define UIDGEN_INLINE_API
#endif

#pragma warning(disable:4251)	//: '*' needs to have dll-interface to be used by clients of '*'

namespace uidgen {
class UIDGEN_API object;
class UIDGEN_API uuid;

class UIDGEN_INLINE_API PosixHeapAllocator;
class UIDGEN_INLINE_API WindowsHeapAllocator;
#ifdef _WINDOWS_
typedef WindowsHeapAllocator	DefaultHeapAllocator;
#else
typedef PosixHeapAllocator		DefaultHeapAllocator;
#endif

class UIDGEN_INLINE_API memory;

template<typename T, typename A> struct UIDGEN_INLINE_API Tarray_traits;
template<typename T, typename A> class UIDGEN_INLINE_API Theap_array_traits;
template<typename T, typename A = DefaultHeapAllocator, typename TR = Theap_array_traits<T, A> > class UIDGEN_INLINE_API Tarray;

template<typename C, typename A> struct UIDGEN_INLINE_API Tstring_traits;
template<typename C, typename A> class UIDGEN_INLINE_API Theap_string_traits;
template<typename C, typename A = DefaultHeapAllocator, typename TR = Theap_string_traits<C, A> > class UIDGEN_INLINE_API Tstring;
typedef Tstring<char>	string;

class UIDGEN_API Iformatter;
class UIDGEN_API Igenerator;

class UIDGEN_API Iprovider;
class	UIDGEN_API null_provider;
class UIDGEN_API context;

typedef Tarray<uidgen::Iformatter *>	formatter_list_t;
typedef Tarray<uidgen::Igenerator *>	generator_list_t;
}

#include "uidgen/object.hxx"
#include "uidgen/uuid.hxx"

#include "uidgen/allocator.hxx"
#include "uidgen/array.hxx"
#include "uidgen/memory.hxx"
#include "uidgen/string.hxx"
#if 1//defined UIDGEN_STATIC || defined UIDGEN_EXPORTS
# include "uidgen/array.inl"
# include "uidgen/memory.inl"
# include "uidgen/string.inl"
#endif // defined UIDGEN_STATIC || defined UIDGEN_EXPORTS

#include "uidgen/Iformatter.hxx"
#include "uidgen/Igenerator.hxx"

#include "uidgen/Iprovider.hxx"
#include "uidgen/context.hxx"

/*END OF uidgen.h*/
