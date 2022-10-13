#pragma once
#include "editor.h"
#include "noname.h"

enum LE3SelectedObjectType
{
    LE3_SELECTED_NONE,
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

    std::map<wxTreeListItem, LE3Object*> m_sceneGraphMap;
    std::map<LE3Object*, wxTreeListItem> m_sceneGraphMapInverse;

    virtual void OnSelectShader( wxTreeListEvent& event );
    void OnPropertyChangeShader(wxPropertyGridEvent& event);

    // virtual void OnSelectShader( wxTreeListEvent& event );
    // void OnPropertyChangeShader(wxPropertyGridEvent& event);

    virtual void OnPropertyChange( wxPropertyGridEvent& event );

    virtual void OnSelectObjectInGraph( wxTreeListEvent& event );

    virtual void OnMouseClick( wxMouseEvent& event );

public:
    class LE3EditorUI_SelectCallback : public LE3SelectCallback
    {
    public:
        LE3EditorUI_SelectCallback(LE3EditorUI* parent);
        virtual void callback();

        LE3EditorUI* parent;
    };

    LE3EditorUI_SelectCallback selectCallback;
};