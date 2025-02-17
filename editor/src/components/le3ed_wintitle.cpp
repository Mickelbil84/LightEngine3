#include "components/le3ed_wintitle.h"
#include "le3_engine_systems.h"
#include "le3ed_events.h"
using namespace le3;

void LE3EditorWindowTitle::init() {
    LE3GetEventManager().subscribe(LE3ED_EVENT_ON_SCENE_LOAD, nullptr, [this](void* data) { this->OnTitleUpdate(); });
    LE3GetEventManager().subscribe(LE3ED_EVENT_ON_SCENE_CHANGE, nullptr, [this](void* data) { this->OnTitleUpdate(); });
    LE3GetEventManager().subscribe(LE3ED_EVENT_ON_SCENE_SAVE, nullptr, [this](void* data) { this->OnTitleUpdate(); });
}

void LE3EditorWindowTitle::OnTitleUpdate() {

}