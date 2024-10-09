#pragma once

#include "le3ed_component.h"
#include "le3ed_constants.h"
#include "widgets/le3ed_toolbar.h"
#include "widgets/le3ed_toolbox.h"
#include "widgets/le3ed_sidepanel_top.h"
#include "widgets/le3ed_settings_panel.h"
#include "widgets/le3ed_properties_panel.h"

namespace le3 {
    class LE3EditorGUI : public LE3EditorComponent{
    public:
        LE3ED_COMPONENT_DEAFULT_CTOR(LE3EditorGUI)
        void init();
        void update(float deltaTime);

    private:
        void setupLayout();

        LE3EditorToolbar m_toolbar;
        LE3EditorToolbox m_toolbox;        
        LE3EditorSidepanelTop m_sidepanelTop;
        LE3EditorSettingsPanel m_settingsPanel;
        LE3EditorPropertiesPanel m_propertiesPanel;
    };
}