#include "le3_script_bindings.h"
#include "le3_engine_systems.h"
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

LIB(LE3VisualDebug, draw_debug_line, draw_debug_box)