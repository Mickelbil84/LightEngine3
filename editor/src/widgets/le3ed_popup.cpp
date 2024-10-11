#include "widgets/le3ed_popup.h"
#include "le3_engine_systems.h"
using namespace le3;

void LE3EditorPopup::lockEngine() {
    LE3GetEditorManager().setPauseSceneUpdates(true);
}
void LE3EditorPopup::unlockEngine() {
    LE3GetEditorManager().setPauseSceneUpdates(false);
}