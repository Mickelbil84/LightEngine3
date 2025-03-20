#include "scripting/le3_script_bindings.h"
#include "core/le3_engine_systems.h"
using namespace le3;

FBIND(LE3Object, get_transform)
    GET_UDATA_OBJECT(obj, LE3Object)
    LE3Transform& transform = obj->getTransform();
    PUSH_UDATA(&transform, LE3Transform)
FEND()
FBIND(LE3Object, get_name)
    GET_UDATA_OBJECT(obj, LE3Object)
    PUSH_STRING(obj->getName())
FEND()
FBIND(LE3Object, get_object_type)
    GET_UDATA_OBJECT(obj, LE3Object)
    PUSH_STRING(obj->getObjectType())
FEND()
FBIND(LE3Object, get_parent_name)
    GET_UDATA_OBJECT(obj, LE3Object)
    if (obj->getParent() == nullptr) {
        PUSH_NIL()
    } else {
        PUSH_STRING(obj->getParent()->getName())
    }
FEND()
FBIND(LE3Object, get_children_names)
    GET_UDATA_OBJECT(obj, LE3Object)
    if (obj->getChildren().size() == 0) {
        PUSH_NIL()
    } else {
        for (auto child : obj->getChildren()) {
            PUSH_STRING(child->getName());
        }
    }
FEND()

LIB(LE3Object,
    get_transform, get_name, get_object_type, get_parent_name, get_children_names
)