/*basic_formatters.h*/

#define SZ_UID_FORMAT_REGISTRY		"{%{!D0}-%{!W2}-%{!W3}-%{!B8}%{!B9}-%{!B10}%{!B11}%{!B12}%{!B13}%{!B14}%{!B15}}"
#define SZ_UID_FORMAT_REGISTRY_LC	"{%{!d0}-%{!w2}-%{!w3}-%{!b8}%{!b9}-%{!b10}%{!b11}%{!b12}%{!b13}%{!b14}%{!b15}}"

namespace uidgen
{
class Iuser_formatter;
class	Csharp_field_definition_formatter;
class	Csharp_Guid_object_formatter;
class	DEFINE_GUID_formatter;
class	Guid_attribute_1_formatter;
class	Guid_attribute_2_formatter;
class	Guid_attribute_3_formatter;
class	IDL_interface_template_formatter;
class	IMPLEMENT_OLECREATE_formatter;
class	raw_format_formatter;
class	registry_format_formatter;
class	static_const_GUID_formatter;
class	user_string_formatter;
class	VbNet_field_definition_formatter;
}

#include "Iuser_formatter.hxx"
#include	"Csharp_field_definition_formatter.hxx"
#include	"Csharp_Guid_object_formatter.hxx"
#include	"DEFINE_GUID_formatter.hxx"
#include	"Guid_attribute_1_formatter.hxx"
#include	"Guid_attribute_2_formatter.hxx"
#include	"Guid_attribute_3_formatter.hxx"
#include	"IDL_interface_template_formatter.hxx"
#include	"IMPLEMENT_OLECREATE_formatter.hxx"
#include	"raw_format_formatter.hxx"
#include	"registry_format_formatter.hxx"
#include	"static_const_GUID_formatter.hxx"
#include	"user_string_formatter.hxx"
#include	"VbNet_field_definition_formatter.hxx"

/*END OF basic_formatters.h*/
