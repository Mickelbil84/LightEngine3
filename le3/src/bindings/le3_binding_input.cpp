#include "scripting/le3_script_bindings.h"
#include "core/le3_engine_systems.h"
using namespace le3;

FBIND(LE3Input, get_key)
    GET_STRING(key)
    PUSH_BOOL(LE3GetInput().keys[key])
FEND()

FBIND(LE3Input, get_xrel)
    PUSH_NUMBER(LE3GetInput().xrel)
FEND()

FBIND(LE3Input, get_yrel)
    PUSH_NUMBER(LE3GetInput().yrel)
FEND()

FBIND(LE3Input, is_key_down_event)
    GET_STRING(key)
    PUSH_BOOL(LE3GetInput().isKeyDownEvent(key))
FEND()

FBIND(LE3Input, is_key_up_event)
    GET_STRING(key)
    PUSH_BOOL(LE3GetInput().isKeyUpEvent(key))
FEND()

FBIND(LE3Input, get_mouse_x)
    PUSH_NUMBER(LE3GetInput().mouseX)
FEND()
FBIND(LE3Input, get_mouse_y)
    PUSH_NUMBER(LE3GetInput().mouseY)
FEND()

FBIND(LE3Input, is_left_mouse_down)
    PUSH_BOOL(LE3GetInput().bLeftMouseDown)
FEND()
FBIND(LE3Input, is_right_mouse_down)
    PUSH_BOOL(LE3GetInput().bRightMouseDown)
FEND()

LIB(LE3Input,
    get_key, is_key_down_event, is_key_up_event,
    get_xrel, get_yrel, get_mouse_x, get_mouse_y,
    is_left_mouse_down, is_right_mouse_down
)