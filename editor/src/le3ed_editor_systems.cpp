#include "le3ed_editor_systems.h"
using namespace le3;

LE3EditorSystems& LE3EditorSystems::instance() {
    static LE3EditorSystems* instance_ = new LE3EditorSystems();
    return *instance_;
}