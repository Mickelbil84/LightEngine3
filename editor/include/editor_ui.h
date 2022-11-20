#pragma once
#include "editor.h"
#include "noname.h"

#include "editor_asset_properties.h"
#include "editor_object_properties.h"

#include <wx/msgdlg.h>
#include <wx/filedlg.h>

#include <le3_visual_debug.h>

#define LE3EDITOR_WINDOW_TITLE "LightEngine3 Editor"

enum LE3SelectedObjectType
{
    LE3_SELECTED_NONE,
    LE3_SELECTED_OBJECT,
    LE3_SELECTED_SHADER,
    LE3_SELECTED_MATERIAL,
    LE3_SELECTED_TEXTURE,
    LE3_SELECTED_MESH
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

    bool bPauseEngine;

    std::map<wxTreeListItem, LE3Object*> m_sceneGraphMap;
    std::map<LE3Object*, wxTreeListItem> m_sceneGraphMapInverse;

    virtual void OnNewScene( wxCommandEvent& event );
    virtual void OnLoadScene( wxCommandEvent& event );
    virtual void OnSaveScene( wxCommandEvent& event );
    virtual void OnSaveSceneAs( wxCommandEvent& event );

    void RefreshPropertyGrid();
    void RefreshPropertyGrid(wxTimerEvent& evt);

    virtual void OnSelectShader( wxTreeListEvent& event );
    virtual void OnSelectMaterial( wxTreeListEvent& event );
    virtual void OnSelectTexture( wxTreeListEvent& event );
	virtual void OnSelectMesh( wxTreeListEvent& event );

    virtual void OnNewShader( wxCommandEvent& event );
	virtual void OnDeleteShader( wxCommandEvent& event );

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