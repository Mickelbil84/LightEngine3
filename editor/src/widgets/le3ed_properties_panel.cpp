#include "widgets/le3ed_properties_panel.h"
using namespace le3;

/*
* Since object serialization happens in Lua anyway, it's also easier to use Lua
* For the properties panel
*/

void LE3EditorPropertiesPanel::init() {
    LE3GetScriptSystem().doFile("/editor/scripts/widgets_properties.lua");
}
void LE3EditorPropertiesPanel::update() {
    LE3ObjectPtr obj = LE3GetEditorManager().getSelection().pObject.lock();
    if (!obj) return;

    LE3GetScriptSystem().getGlobal("update_properties_panel");
    LE3GetScriptSystem().pushUserType(&obj);
    LE3GetScriptSystem().callFunction(1, 0);
}