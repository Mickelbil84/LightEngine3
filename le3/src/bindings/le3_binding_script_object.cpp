#include "scripting/le3_script_bindings.h"
#include "core/le3_engine_systems.h"
using namespace le3;

FBIND_OBJECT_GETTER_STRING(LE3ScriptObject, get_classname, getClassname)
FBIND(LE3ScriptObject, update_internals)
    GET_UDATA_OBJECT(obj, LE3ScriptObject)
    GET_STRING(classname)
    GET_STRING(ref)
    obj->updateInternals(classname, ref);
FEND()

LIB(LE3ScriptObject, 
    get_classname, update_internals
)
