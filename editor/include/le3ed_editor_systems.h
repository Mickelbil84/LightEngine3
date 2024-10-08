#pragma once

#include "components/le3ed_gui.h"
#include "components/le3ed_scenes.h"
#include "components/le3ed_hotkeys.h"

namespace le3 {
    class LE3EditorSystems {
    public:
        static LE3EditorSystems& instance();

        inline LE3EditorGUI* getGUIComponent() { return g_guiComponent; }
        void setGUIComponent(LE3EditorGUI* guiComponent) { g_guiComponent = guiComponent; }

        inline LE3EditorScenes* getScenesComponent() { return g_scenesComponent; }
        void setScenesComponent(LE3EditorScenes* scenesComponent) { g_scenesComponent = scenesComponent; }
        
        inline LE3EditorHotkeys* getHotkeysComponent() { return g_hotkeysComponent; }
        void setHotkeysComponent(LE3EditorHotkeys* hotkeysComponent) { g_hotkeysComponent = hotkeysComponent; }


    private:
        LE3EditorGUI* g_guiComponent;
        LE3EditorScenes* g_scenesComponent;
        LE3EditorHotkeys* g_hotkeysComponent;
    };
}