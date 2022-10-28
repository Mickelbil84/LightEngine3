#pragma once
#include "editor.h"
#include "noname.h"

#include "editor_object_properties.h"

#include <le3_visual_debug.h>

enum LE3SelectedObjectType
{
    LE3_SELECTED_NONE,
    LE3_SELECTED_OBJECT,
    LE3_SELECTED_SHADER,
};

class LE3EditorUI : public LE3EditorWindow
{
public:
    LE3EditorUI(wxWindow* parent);

    void RefreshAssets();
    void RefreshSceneGraph();
    void RefreshSceneGraph(LE3Object* node, wxTreeListItem treeItem);

    LE3Editor* m_editor;

protected:
    LE3SelectedObjectType m_selectedType;
    std::string m_selectedName;
    wxTimer m_propertyGridRefresh;

    std::map<wxTreeListItem, LE3Object*> m_sceneGraphMap;
    std::map<LE3Object*, wxTreeListItem> m_sceneGraphMapInverse;

    void RefreshPropertyGrid();
    void RefreshPropertyGrid(wxTimerEvent& evt);

    virtual void OnSelectShader( wxTreeListEvent& event );
    void OnPropertyChangeShader(wxPropertyGridEvent& event);

    // virtual void OnSelectShader( wxTreeListEvent& event );
    // void OnPropertyChangeShader(wxPropertyGridEvent& event);

    virtual void OnPropertyChange( wxPropertyGridEvent& event );

    virtual void OnSelectObjectInGraph( wxTreeListEvent& event );

    virtual void OnMouseClick( wxMouseEvent& event );

    virtual void OnCollisionToolToggle( wxCommandEvent& event );
    virtual void OnBulletCollisionToolToggle( wxCommandEvent& event );

public:
    ///////////////
    // Callbacks //
    ///////////////
    class LE3EditorUI_SelectCallback : public LE3SelectCallback
    {
    public:
        LE3EditorUI_SelectCallback(LE3EditorUI* parent);
        virtual void callback();

        LE3EditorUI* parent;
    };

    class LE3EditorUI_RefreshPropertiesCallback : public LE3RefreshPropertiesCallback
    {
    public:
        LE3EditorUI_RefreshPropertiesCallback(LE3EditorUI* parent);
        virtual void callback();

        LE3EditorUI* parent;
    };

    LE3EditorUI_SelectCallback selectCallback;
    LE3EditorUI_RefreshPropertiesCallback refreshPropertiesCallback;
};