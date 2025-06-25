#include "scripting/le3_script_bindings.h"
#include "core/le3_engine_systems.h"
using namespace le3;

FBIND(LE3EngineState, notify_wants_quit)
    LE3GetEngineState()->notifyWantsQuit();
FEND()

FBIND(LE3EngineState, notify_wants_relative_mouse)
    GET_BOOL(relativeMouse)
    LE3GetEngineState()->notifyWantsRelativeMouse(relativeMouse);
FEND()
FBIND(LE3EngineState, is_relative_mouse)
    PUSH_BOOL(LE3GetEngineState()->isRelativeMouse())
FEND()

LIB(LE3EngineState,
    notify_wants_quit,
    notify_wants_relative_mouse, is_relative_mouse
)