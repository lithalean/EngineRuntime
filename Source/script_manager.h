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

// Jenova Script Manager Definition
class JenovaScriptManager : public RefCounted
{
    GDCLASS(JenovaScriptManager, RefCounted);

protected:
    static void _bind_methods();
    std::vector<CPPScript*> scriptObjects;
    std::vector<CPPScriptInstance*> scriptInstances;
    std::vector<jenova::VoidFunc_t> runtimeStartEvents;

public:
    JenovaScriptManager();
    ~JenovaScriptManager();

public:
    bool add_script_object(CPPScript* scriptObject);
    bool remove_script_object(CPPScript* scriptObject);
    size_t get_script_object_count();
    Ref<CPPScript> get_script_object(size_t index);
    bool add_script_instance(CPPScriptInstance* scriptInstance);
    bool remove_script_instance(CPPScriptInstance* scriptInstance);
    size_t get_script_instance_count();
    CPPScriptInstance* get_script_instance(size_t index);
    bool register_runtime_start_event(jenova::VoidFunc_t callbackPtr);

public:
    static void init();
    static void deinit();
    static JenovaScriptManager* get_singleton();

protected:
    static inline bool IsRuntimeStarted = false;
};

// Define ALternative Name
typedef JenovaScriptManager ScriptManager;