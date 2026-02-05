#include "scripting/le3_script_bindings.h"
#include "core/le3_engine_systems.h"
using namespace le3;

FBIND(LE3VisualDebug, draw_debug_line)
    GET_VEC3_(start)
    GET_VEC3_(end)
    GET_VEC3_(color)
    LE3GetVisualDebug().drawDebugLine(start, end, color);
FEND()

FBIND(LE3VisualDebug, draw_debug_box)
    GET_VEC3_(position)
    GET_QUAT(rotation)
    GET_VEC3_(scale)
    GET_VEC3_(color)
    LE3GetVisualDebug().drawDebugBox(position, rotation, scale, color);
FEND()

FBIND(LE3VisualDebug, set_show_colliders)
    GET_BOOL(show)
    LE3GetEngineDebug().g_bShowColliders = show;
FEND()

FBIND(LE3VisualDebug, get_show_colliders)
    PUSH_BOOL(LE3GetEngineDebug().g_bShowColliders)
FEND()

LIB(LE3VisualDebug, draw_debug_line, draw_debug_box, set_show_colliders, get_show_colliders)