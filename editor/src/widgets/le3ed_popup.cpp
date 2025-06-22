#include "widgets/le3ed_popup.h"
#include "core/le3_engine_systems.h"
#include "le3ed_editor_systems.h"
using namespace le3;

LE3EditorPopup::LE3EditorPopup() {
    LE3EditorSystems::instance().addPopup(this);
}

void LE3EditorPopup::lockEngine() {
    LE3GetEditorManager().setPauseSceneUpdates(true);
}
void LE3EditorPopup::unlockEngine() {
    LE3GetEditorManager().setPauseSceneUpdates(false);
}