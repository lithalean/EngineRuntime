
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

// Script Instance Base Implementation
static GDExtensionBool gdextension_script_instance_set(GDExtensionScriptInstanceDataPtr p_instance, GDExtensionConstStringNamePtr p_name, GDExtensionConstVariantPtr p_value)
{
	ScriptInstanceExtension* instance = reinterpret_cast<ScriptInstanceExtension*>(p_instance);
	const StringName* name = reinterpret_cast<const StringName*>(p_name);
	const Variant* value = reinterpret_cast<const Variant*>(p_value);
	return instance->set(*name, *value);
}
static GDExtensionBool gdextension_script_instance_get(GDExtensionScriptInstanceDataPtr p_instance, GDExtensionConstStringNamePtr p_name, GDExtensionVariantPtr r_ret)
{
	ScriptInstanceExtension* instance = reinterpret_cast<ScriptInstanceExtension*>(p_instance);
	const StringName* name = reinterpret_cast<const StringName*>(p_name);
	Variant* ret = reinterpret_cast<Variant*>(r_ret);
	return instance->get(*name, *ret);
}
static const GDExtensionPropertyInfo* gdextension_script_instance_get_property_list(GDExtensionScriptInstanceDataPtr p_instance, uint32_t* r_count)
{
	ScriptInstanceExtension* instance = reinterpret_cast<ScriptInstanceExtension*>(p_instance);
	return instance->get_property_list(r_count);
}
static void gdextension_script_instance_free_property_list(GDExtensionScriptInstanceDataPtr p_instance, const GDExtensionPropertyInfo* p_list, uint32_t p_count)
{
	ScriptInstanceExtension* instance = reinterpret_cast<ScriptInstanceExtension*>(p_instance);
	instance->free_property_list(p_list, p_count);
}
static GDExtensionBool gdextension_script_instance_get_class_category(GDExtensionScriptInstanceDataPtr p_instance, GDExtensionPropertyInfo* r_class_category)
{
	ScriptInstanceExtension* instance = reinterpret_cast<ScriptInstanceExtension*>(p_instance);
	return instance->get_class_category(*r_class_category);
}
static GDExtensionVariantType gdextension_script_instance_get_property_type(GDExtensionScriptInstanceDataPtr p_instance, GDExtensionConstStringNamePtr p_name, GDExtensionBool* r_is_valid)
{
	ScriptInstanceExtension* instance = reinterpret_cast<ScriptInstanceExtension*>(p_instance);
	const StringName* name = reinterpret_cast<const StringName*>(p_name);
	bool is_valid;
	GDExtensionVariantType ret = (GDExtensionVariantType)instance->get_property_type(*name, &is_valid);
	*r_is_valid = is_valid;
	return ret;
}
static GDExtensionBool gdextension_script_instance_validate_property(GDExtensionScriptInstanceDataPtr p_instance, GDExtensionPropertyInfo* p_property)
{
	ScriptInstanceExtension* instance = reinterpret_cast<ScriptInstanceExtension*>(p_instance);
	return instance->validate_property(*p_property);
}
static GDExtensionBool gdextension_script_instance_property_can_revert(GDExtensionScriptInstanceDataPtr p_instance, GDExtensionConstStringNamePtr p_name)
{
	ScriptInstanceExtension* instance = reinterpret_cast<ScriptInstanceExtension*>(p_instance);
	const StringName* name = reinterpret_cast<const StringName*>(p_name);
	return instance->property_can_revert(*name);
}
static GDExtensionBool gdextension_script_instance_property_get_revert(GDExtensionScriptInstanceDataPtr p_instance, GDExtensionConstStringNamePtr p_name, GDExtensionVariantPtr r_ret)
{
	ScriptInstanceExtension* instance = reinterpret_cast<ScriptInstanceExtension*>(p_instance);
	const StringName* name = reinterpret_cast<const StringName*>(p_name);
	Variant* ret = reinterpret_cast<Variant*>(r_ret);
	return instance->property_get_revert(*name, *ret);
}
static GDExtensionObjectPtr gdextension_script_instance_get_owner(GDExtensionScriptInstanceDataPtr p_instance)
{
	ScriptInstanceExtension* instance = reinterpret_cast<ScriptInstanceExtension*>(p_instance);
	Object* ret = instance->get_owner();
	return ret->_owner;
}
static void gdextension_script_instance_get_property_state(GDExtensionScriptInstanceDataPtr p_instance, GDExtensionScriptInstancePropertyStateAdd p_add_func, void* p_userdata)
{
	ScriptInstanceExtension* instance = reinterpret_cast<ScriptInstanceExtension*>(p_instance);
	instance->get_property_state(p_add_func, p_userdata);
}
static const GDExtensionMethodInfo* gdextension_script_instance_get_method_list(GDExtensionScriptInstanceDataPtr p_instance, uint32_t* r_count)
{
	ScriptInstanceExtension* instance = reinterpret_cast<ScriptInstanceExtension*>(p_instance);
	return instance->get_method_list(r_count);
}
static void gdextension_script_instance_free_method_list(GDExtensionScriptInstanceDataPtr p_instance, const GDExtensionMethodInfo* p_list, uint32_t p_count)
{
	ScriptInstanceExtension* instance = reinterpret_cast<ScriptInstanceExtension*>(p_instance);
	return instance->free_method_list(p_list, p_count);
}
static GDExtensionBool gdextension_script_instance_has_method(GDExtensionScriptInstanceDataPtr p_instance, GDExtensionConstStringNamePtr p_name)
{
	ScriptInstanceExtension* instance = reinterpret_cast<ScriptInstanceExtension*>(p_instance);
	const StringName* name = reinterpret_cast<const StringName*>(p_name);
	return instance->has_method(*name);
}
static void gdextension_script_instance_call(GDExtensionScriptInstanceDataPtr p_instance, GDExtensionConstStringNamePtr p_method, const GDExtensionConstVariantPtr* p_args, GDExtensionInt p_argument_count, GDExtensionVariantPtr r_return, GDExtensionCallError* r_error)
{
	ScriptInstanceExtension* instance = reinterpret_cast<ScriptInstanceExtension*>(p_instance);
	const StringName* method = reinterpret_cast<const StringName*>(p_method);
	const Variant** args = reinterpret_cast<const Variant**>(const_cast<const void**>(p_args));
	Variant* ret = reinterpret_cast<Variant*>(r_return);

	// Managed Safe Execution [Windows Only]
	#if defined(TARGET_PLATFORM_WINDOWS) && defined(_MSC_VER)

		// Create Invoker
		auto invoke_callp = [&]() { *ret = instance->callp(*method, args, p_argument_count, *r_error); };

		// Skip Managed Safe Execution If Disabled
		if (!jenova::GlobalStorage::UseManagedSafeExecution)
		{
			invoke_callp();
			return;
		}

		// Safe Call By Invocation
		__try { invoke_callp(); }
		__except (jenova::JenovaExecutionCrashHandler(GetExceptionInformation()))
		{
			// Suppres Godot Call Error
			if (r_error) r_error->error = GDEXTENSION_CALL_OK;
		}

	#else
		*ret = instance->callp(*method, args, p_argument_count, *r_error);
	#endif
}
static void gdextension_script_instance_notification(GDExtensionScriptInstanceDataPtr p_instance, int32_t p_what, GDExtensionBool p_reversed)
{
	ScriptInstanceExtension* instance = reinterpret_cast<ScriptInstanceExtension*>(p_instance);
	instance->notification(p_what, p_reversed);
}
static void gdextension_script_instance_to_string(GDExtensionScriptInstanceDataPtr p_instance, GDExtensionBool* r_is_valid, GDExtensionStringPtr r_out)
{
	ScriptInstanceExtension* instance = reinterpret_cast<ScriptInstanceExtension*>(p_instance);
	String* out = reinterpret_cast<String*>(r_out);
	bool is_valid = false;
	*out = instance->to_string(&is_valid);
	*r_is_valid = is_valid;
}
static void gdextension_script_instance_refcount_incremented(GDExtensionScriptInstanceDataPtr p_instance)
{
	ScriptInstanceExtension* instance = reinterpret_cast<ScriptInstanceExtension*>(p_instance);
	instance->refcount_incremented();
}
static GDExtensionBool gdextension_script_instance_refcount_decremented(GDExtensionScriptInstanceDataPtr p_instance)
{
	ScriptInstanceExtension* instance = reinterpret_cast<ScriptInstanceExtension*>(p_instance);
	return instance->refcount_decremented();
}
static GDExtensionObjectPtr gdextension_script_instance_get_script(GDExtensionScriptInstanceDataPtr p_instance)
{
	ScriptInstanceExtension* instance = reinterpret_cast<ScriptInstanceExtension*>(p_instance);
	return instance->get_script().ptr()->_owner;
}
static GDExtensionBool gdextension_script_instance_is_placeholder(GDExtensionScriptInstanceDataPtr p_instance)
{
	ScriptInstanceExtension* instance = reinterpret_cast<ScriptInstanceExtension*>(p_instance);
	return instance->is_placeholder();
}
static GDExtensionBool gdextension_script_instance_set_fallback(GDExtensionScriptInstanceDataPtr p_instance, GDExtensionConstStringNamePtr p_name, GDExtensionConstVariantPtr p_value) {
	ScriptInstanceExtension* instance = reinterpret_cast<ScriptInstanceExtension*>(p_instance);
	const StringName* name = reinterpret_cast<const StringName*>(p_name);
	const Variant* value = reinterpret_cast<const Variant*>(p_value);
	bool is_valid = false;
	instance->property_set_fallback(*name, *value, &is_valid);
	return is_valid;
}
static GDExtensionBool gdextension_script_instance_get_fallback(GDExtensionScriptInstanceDataPtr p_instance, GDExtensionConstStringNamePtr p_name, GDExtensionVariantPtr r_ret)
{
	ScriptInstanceExtension* instance = reinterpret_cast<ScriptInstanceExtension*>(p_instance);
	const StringName* name = reinterpret_cast<const StringName*>(p_name);
	Variant* ret = reinterpret_cast<Variant*>(r_ret);
	bool is_valid = false;
	instance->property_get_fallback(*name, &is_valid);
	return is_valid;
}
static GDExtensionScriptLanguagePtr gdextension_script_instance_get_language(GDExtensionScriptInstanceDataPtr p_instance)
{
	ScriptInstanceExtension* instance = reinterpret_cast<ScriptInstanceExtension*>(p_instance);
	return instance->_get_language()->_owner;
}
static void gdextension_script_instance_free(GDExtensionScriptInstanceDataPtr p_instance)
{
	if (p_instance) {
		ScriptInstanceExtension* instance = reinterpret_cast<ScriptInstanceExtension*>(p_instance);
		memdelete(instance);
	}
}
static GDExtensionInt gdextension_script_instance_get_method_argument_count(GDExtensionScriptInstanceDataPtr p_instance, GDExtensionConstStringNamePtr p_name, GDExtensionBool* r_is_valid)
{
	if (p_instance)
	{
		ScriptInstanceExtension* instance = reinterpret_cast<ScriptInstanceExtension*>(p_instance);
		const StringName* name = reinterpret_cast<const StringName*>(p_name);
		return instance->get_method_argument_count(*name, (bool*)r_is_valid);
	}
	else
	{
		return 0;
	}
}

// Script Instance Info
GDExtensionScriptInstanceInfo3 ScriptInstanceExtension::script_instance_info =
{
	&gdextension_script_instance_set,
	&gdextension_script_instance_get,
	&gdextension_script_instance_get_property_list,
	&gdextension_script_instance_free_property_list,
	&gdextension_script_instance_get_class_category,
	&gdextension_script_instance_property_can_revert,
	&gdextension_script_instance_property_get_revert,
	&gdextension_script_instance_get_owner,
	&gdextension_script_instance_get_property_state,
	&gdextension_script_instance_get_method_list,
	&gdextension_script_instance_free_method_list,
	&gdextension_script_instance_get_property_type,
	&gdextension_script_instance_validate_property,
	&gdextension_script_instance_has_method,
	&gdextension_script_instance_get_method_argument_count,
	&gdextension_script_instance_call,
	&gdextension_script_instance_notification,
	&gdextension_script_instance_to_string,
	&gdextension_script_instance_refcount_incremented,
	&gdextension_script_instance_refcount_decremented,
	&gdextension_script_instance_get_script,
	&gdextension_script_instance_is_placeholder,
	&gdextension_script_instance_set_fallback,
	&gdextension_script_instance_get_fallback,
	&gdextension_script_instance_get_language,
	&gdextension_script_instance_free,
};

// Script Instance Class Category
bool ScriptInstanceExtension::get_class_category(GDExtensionPropertyInfo& r_class_category) const
{
	Ref<CPPScript> script = get_script();
	if (script.is_valid())
	{
		// Update Script Class Information
		script->scriptClassName = CPPScriptLanguage::get_singleton()->_get_global_class_name(script->get_path())["name"];
		script->scriptClassType = script->get_class();
		script->scriptClassPath = script->get_path();

		// Create Class Category
		r_class_category.type = GDEXTENSION_VARIANT_TYPE_NIL;
		r_class_category.name = &script->scriptClassName;
		r_class_category.class_name = &script->scriptClassType;
		r_class_category.hint = PROPERTY_HINT_NONE;
		r_class_category.hint_string = &script->scriptClassPath;
		r_class_category.usage = PROPERTY_USAGE_CATEGORY;
		return true;
	}
	return false;
}
