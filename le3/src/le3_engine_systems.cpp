#include "le3_engine_systems.h"
using namespace le3;

LE3EngineSystems& LE3EngineSystems::instance() {
    static LE3EngineSystems* instance_ = new LE3EngineSystems();
    return *instance_;
}