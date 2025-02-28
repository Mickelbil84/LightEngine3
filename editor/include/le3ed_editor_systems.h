#pragma once

#include "components/le3ed_gui.h"
#include "components/le3ed_scenes.h"
#include "components/le3ed_hotkeys.h"
#include "components/le3ed_scripts.h"
#include "components/le3ed_wintitle.h"
#include "widgets/le3ed_popup.h"

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

        inline LE3EditorScripts* getScriptsComponent() { return g_scriptsComponent; }
        void setScriptsComponent(LE3EditorScripts* scriptsComponent) { g_scriptsComponent = scriptsComponent; }

        inline LE3EditorWindowTitle* getWindowTitleComponent() { return g_wintitleComponent; }
        void setWindowTitleComponent(LE3EditorWindowTitle* wintitleComponent) { g_wintitleComponent = wintitleComponent; }

        void addPopup(LE3EditorPopup* popup) { g_popups.push_back(popup); }
        void updatePopups() { for (auto popup : g_popups) popup->update(); }

    private:
        LE3EditorGUI* g_guiComponent;
        LE3EditorScenes* g_scenesComponent;
        LE3EditorHotkeys* g_hotkeysComponent;
        LE3EditorScripts* g_scriptsComponent;
        LE3EditorWindowTitle* g_wintitleComponent;

        std::vector<LE3EditorPopup*> g_popups;
    };
}