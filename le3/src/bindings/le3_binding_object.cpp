#include "le3_script_bindings.h"
#include "le3_engine_systems.h"
using namespace le3;

FBIND(LE3Object, get_transform)
    GET_UDATA_OBJECT(obj, LE3Object)
    LE3Transform& transform = obj->getTransform();
    PUSH_UDATA(&transform, LE3Transform)
FEND()

LIB(LE3Object,
    get_transform
)