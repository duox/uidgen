/*uidgen_context.cxx*/
/** @file
 *
 * @brief Overrides of the uidgen::context class.
 * SPDX-License-Identifier: MIT
 */
#include "../pch.h"
#include "../main.h"
#include "uidgen_context.hxx"

/**
 * @brief The uidgen context constructor.
 *
 *	The constructor adds all known formatters and generators.
 */
uidgen_context::uidgen_context()
{
	append_formatter( m_Csharp_field_definition_formatter );
	append_formatter( m_Csharp_Guid_object_formatter );
	append_formatter( m_DEFINE_GUID_formatter );
	append_formatter( m_Guid_attribute_1_formatter );
	append_formatter( m_Guid_attribute_2_formatter );
	append_formatter( m_Guid_attribute_3_formatter );
	append_formatter( m_IDL_interface_template_formatter );
	append_formatter( m_IMPLEMENT_OLECREATE_formatter );
	append_formatter( m_raw_format_formatter );
	append_formatter( m_registry_format_formatter );
	append_formatter( m_static_const_GUID_formatter );
	append_formatter( m_user_string_formatter );
	append_formatter( m_VbNet_field_definition_formatter );

	append_generator( m_random_uuid_generator );
	append_generator( m_manual_uuid_generator );
	append_generator( m_null_uuid_generator );
	append_generator( m_invalid_uuid_generator );
}

/*END OF uidgen_context.cxx*/
