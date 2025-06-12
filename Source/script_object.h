#pragma once

/*-------------------------------------------------------------+
|                                                              |
|                   _________   ______ _    _____              |
|                  / / ____/ | / / __ \ |  / /   |             |
|             __  / / __/ /  |/ / / / / | / / /| |             |
|            / /_/ / /___/ /|  / /_/ /| |/ / ___ |             |
|            \____/_____/_/ |_/\____/ |___/_/  |_|             |
|                                                              |
|                        Jenova Runtime                        |
|                   Developed by Hamid.Memar                   |
|                                                              |
+-------------------------------------------------------------*/

// Jenova SDK
#include "Jenova.hpp"

// Import jenova Types
namespace jenova
{
	typedef String ScriptIdentifier;
}

// Jenova Script Object Definition
class CPPScript : public ScriptExtension
{
	GDCLASS(CPPScript, ScriptExtension);

protected:
	static void _bind_methods();

private:
	// Internal Values
	String source_code;
	StringName globalName = jenova::GlobalSettings::JenovaScriptType;
	Ref<Mutex> scriptMutex;
	bool IsTool = false;

public:
	// Script Class Information
	StringName scriptClassName;
	StringName scriptClassType;
	String scriptClassPath;

public:
	// Base Methods
	virtual bool _editor_can_reload_from_file() override;
	virtual void _placeholder_erased(void* p_placeholder) override;
	virtual bool _can_instantiate() const override;
	virtual Ref<Script> _get_base_script() const override;
	virtual StringName _get_global_name();
	virtual bool _inherits_script(const Ref<Script>& p_script) const override;
	virtual StringName _get_instance_base_type() const override;
	virtual void* _instance_create(Object* p_for_object) const override;
	virtual void* _placeholder_instance_create(Object* p_for_object) const override;
	virtual bool _instance_has(Object* p_object) const override;
	virtual bool _has_source_code() const override;
	virtual String _get_source_code() const override;
	virtual void _set_source_code(const String& p_code) override;
	virtual Error _reload(bool p_keep_state) override;
	virtual TypedArray<Dictionary> _get_documentation() const override;
	virtual String _get_class_icon_path() const override;
	virtual bool _has_method(const StringName& p_method) const override;
	virtual bool _has_static_method(const StringName& p_method) const override;
	virtual Dictionary _get_method_info(const StringName& p_method) const override;
	virtual bool _is_tool() const override;
	virtual bool _is_valid() const override;
	virtual bool _is_abstract() const override;
	virtual ScriptLanguage* _get_language() const override;
	virtual bool _has_script_signal(const StringName& p_signal) const override;
	virtual TypedArray<Dictionary> _get_script_signal_list() const override;
	virtual bool _has_property_default_value(const StringName& p_property) const override;
	virtual Variant _get_property_default_value(const StringName& p_property) const override;
	virtual void _update_exports() override;
	virtual TypedArray<Dictionary> _get_script_method_list() const override;
	virtual TypedArray<Dictionary> _get_script_property_list() const override;
	virtual int32_t _get_member_line(const StringName& p_member) const override;
	virtual Dictionary _get_constants() const override;
	virtual TypedArray<StringName> _get_members() const override;
	virtual bool _is_placeholder_fallback_enabled() const override;
	virtual Variant _get_rpc_config() const override;

public:
	// Methods
	void SetDefaultSourceCode();
	jenova::ScriptIdentifier GetScriptIdentity() const;
	void ReloadScriptSourceCode();

	// Extra
	bool is_built_in() const
	{
		return get_path().is_empty() || get_path().contains("::") || get_path().begins_with("local://");
	};

	// Initializer/Destructor
	CPPScript();
	~CPPScript();
};

// Jenova Script Object Definition
class CPPHeader : public ScriptExtension
{
	GDCLASS(CPPHeader, ScriptExtension);

protected:
	static void _bind_methods();
	String source_code;

public:
	// Base Methods
	virtual bool _editor_can_reload_from_file() override;
	virtual void _placeholder_erased(void* p_placeholder) override;
	virtual bool _can_instantiate() const override;
	virtual Ref<Script> _get_base_script() const override;
	virtual StringName _get_global_name();
	virtual bool _inherits_script(const Ref<Script>& p_script) const override;
	virtual StringName _get_instance_base_type() const override;
	virtual void* _instance_create(Object* p_for_object) const override;
	virtual void* _placeholder_instance_create(Object* p_for_object) const override;
	virtual bool _instance_has(Object* p_object) const override;
	virtual bool _has_source_code() const override;
	virtual String _get_source_code() const override;
	virtual void _set_source_code(const String& p_code) override;
	virtual Error _reload(bool p_keep_state) override;
	virtual TypedArray<Dictionary> _get_documentation() const override;
	virtual String _get_class_icon_path() const override;
	virtual bool _has_method(const StringName& p_method) const override;
	virtual bool _has_static_method(const StringName& p_method) const override;
	virtual Dictionary _get_method_info(const StringName& p_method) const override;
	virtual bool _is_tool() const override;
	virtual bool _is_valid() const override;
	virtual bool _is_abstract() const override;
	virtual ScriptLanguage* _get_language() const override;
	virtual bool _has_script_signal(const StringName& p_signal) const override;
	virtual TypedArray<Dictionary> _get_script_signal_list() const override;
	virtual bool _has_property_default_value(const StringName& p_property) const override;
	virtual Variant _get_property_default_value(const StringName& p_property) const override;
	virtual void _update_exports() override;
	virtual TypedArray<Dictionary> _get_script_method_list() const override;
	virtual TypedArray<Dictionary> _get_script_property_list() const override;
	virtual int32_t _get_member_line(const StringName& p_member) const override;
	virtual Dictionary _get_constants() const override;
	virtual TypedArray<StringName> _get_members() const override;
	virtual bool _is_placeholder_fallback_enabled() const override;
	virtual Variant _get_rpc_config() const override;
public:
	// Methods
	void ReloadHeaderSourceCode();

	// Intializer
	CPPHeader();
};