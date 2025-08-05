/*uidgen_context.hxx*/
#pragma once

class uidgen_context : public uidgen::context
{
public:

	uidgen_context();

protected:
	uidgen::Csharp_field_definition_formatter	m_Csharp_field_definition_formatter;
	uidgen::Csharp_Guid_object_formatter		m_Csharp_Guid_object_formatter;
	uidgen::DEFINE_GUID_formatter				m_DEFINE_GUID_formatter;
	uidgen::Guid_attribute_1_formatter			m_Guid_attribute_1_formatter;
	uidgen::Guid_attribute_2_formatter			m_Guid_attribute_2_formatter;
	uidgen::Guid_attribute_3_formatter			m_Guid_attribute_3_formatter;
	uidgen::IDL_interface_template_formatter	m_IDL_interface_template_formatter;
	uidgen::IMPLEMENT_OLECREATE_formatter		m_IMPLEMENT_OLECREATE_formatter;
	uidgen::raw_format_formatter				m_raw_format_formatter;
	uidgen::registry_format_formatter			m_registry_format_formatter;
	uidgen::static_const_GUID_formatter			m_static_const_GUID_formatter;
	uidgen::user_string_formatter				m_user_string_formatter;
	uidgen::VbNet_field_definition_formatter	m_VbNet_field_definition_formatter;

	uidgen::random_uuid_generator	m_random_uuid_generator;
	uidgen::manual_uuid_generator	m_manual_uuid_generator;
	uidgen::null_uuid_generator		m_null_uuid_generator;
	uidgen::invalid_uuid_generator	m_invalid_uuid_generator;
};

/*END OF uidgen_context.hxx*/
