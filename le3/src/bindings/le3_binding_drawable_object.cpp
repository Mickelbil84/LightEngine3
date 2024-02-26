#include "le3_script_bindings.h"
#include "le3_engine_systems.h"
using namespace le3;


FBIND_OBJECT_GETTER_NUMBER(LE3DrawableObject, get_draw_priority, getDrawPriority)
FBIND_OBJECT_SETTER_ENUM(LE3DrawableObject, set_draw_priority, setDrawPriority, LE3DrawPriority)

FBIND(LE3DrawableObject, get_material)
    GET_UDATA_OBJECT(self, LE3DrawableObject)
    LE3MaterialPtr& material = self->getMaterial();
    PUSH_UDATA(&material, LE3MaterialPtr)
FEND()

FBIND_OBJECT_GETTER_BOOL(LE3DrawableObject, get_hidden, isHidden)
FBIND_OBJECT_SETTER_BOOL(LE3DrawableObject, set_hidden, setHidden)

FBIND_OBJECT_GETTER_BOOL(LE3DrawableObject, get_cast_shadow, getCastShadow)
FBIND_OBJECT_SETTER_BOOL(LE3DrawableObject, set_cast_shadow, setCastShadow)

LIB(LE3DrawableObject,
    get_draw_priority, set_draw_priority,
    get_material,
    get_hidden, set_hidden,
    get_cast_shadow, set_cast_shadow
)