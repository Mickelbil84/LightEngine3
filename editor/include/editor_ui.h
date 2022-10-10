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

    virtual void OnSelectShader( wxTreeListEvent& event );
    void OnPropertyChangeShader(wxPropertyGridEvent& event);

    // virtual void OnSelectShader( wxTreeListEvent& event );
    // void OnPropertyChangeShader(wxPropertyGridEvent& event);

    virtual void OnPropertyChange( wxPropertyGridEvent& event );

    virtual void OnSelectObjectInGraph( wxTreeListEvent& event );

};