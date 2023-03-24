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

    // bool bPauseEngine;

    std::map<wxTreeListItem, LE3Object*> m_sceneGraphMap;
    std::map<LE3Object*, wxTreeListItem> m_sceneGraphMapInverse;

    ////////////////////////////////
    // Scene management (Load/Save)
    ////////////////////////////////
    virtual void OnNewScene( wxCommandEvent& event );
    virtual void OnLoadScene( wxCommandEvent& event );
    virtual void OnSaveScene( wxCommandEvent& event );
    virtual void OnSaveSceneAs( wxCommandEvent& event );

    ////////////////////////////////
    // Updating Properties
    ////////////////////////////////
    void RefreshPropertyGrid();
    void RefreshPropertyGrid(wxTimerEvent& evt);
    virtual void OnPropertyChange( wxPropertyGridEvent& event );

    ///////////////////////////////////
    // Asset & Object selection Events
    ///////////////////////////////////
    virtual void OnSelectShader( wxTreeListEvent& event );
    virtual void OnSelectMaterial( wxTreeListEvent& event );
    virtual void OnSelectTexture( wxTreeListEvent& event );
	virtual void OnSelectMesh( wxTreeListEvent& event );
    virtual void OnSelectObjectInGraph( wxTreeListEvent& event );

    //////////////////////////////////
    // Asset creation/deletion events
    //////////////////////////////////
    virtual void OnNewShader( wxCommandEvent& event );
	virtual void OnDeleteShader( wxCommandEvent& event );
    virtual void OnNewMaterial( wxCommandEvent& event );
	virtual void OnDeleteMaterial( wxCommandEvent& event );
    virtual void OnNewTexture( wxCommandEvent& event );
	virtual void OnDeleteTexture( wxCommandEvent& event );
    virtual void OnNewMesh( wxCommandEvent& event );
	virtual void OnDeleteMesh( wxCommandEvent& event );

    ////////////////////////////////
    // Debug toggles event
    ////////////////////////////////
    virtual void OnCollisionToolToggle( wxCommandEvent& event );
    virtual void OnBulletCollisionToolToggle( wxCommandEvent& event );

    ////////////////////////////////
    // Gizmo Modes
    ////////////////////////////////
    virtual void OnGizmoSelect( wxCommandEvent& event );
    virtual void OnGizmoMove( wxCommandEvent& event );
    virtual void OnGizmoRotate( wxCommandEvent& event );
    virtual void OnGizmoScale( wxCommandEvent& event );

    /////////////////////////////////
    // Object Hirerachy Manipulation
    /////////////////////////////////
    virtual void OnReparent( wxCommandEvent& event );
    virtual void OnDuplicate( wxCommandEvent& event );
    virtual void OnDelete( wxCommandEvent& event );

    ////////////////////////////////
    // Object Creation Dialogs
    ////////////////////////////////
    virtual void OnAddCube( wxCommandEvent& event );
    virtual void OnAddCylinder( wxCommandEvent& event );
    virtual void OnAddCone( wxCommandEvent& event );
    virtual void OnAddTorus( wxCommandEvent& event );
    virtual void OnAddSphere( wxCommandEvent& event );
    virtual void OnAddStaticMesh( wxCommandEvent& event );
    virtual void OnAddEmpty( wxCommandEvent& event );

    ////////////////////////////////
    // Light Creation Dialogs
    ////////////////////////////////
    virtual void OnAddAmbientLight( wxCommandEvent& event );
    virtual void OnAddDirectionalLight( wxCommandEvent& event );
    virtual void OnAddPointLight( wxCommandEvent& event );
    virtual void OnAddSpotLight( wxCommandEvent& event );

    ////////////////////////////////
    // Numbered names generation
    ////////////////////////////////
    std::string GetObjectNumberPrefix(std::string objectName);
    int GetObjectNumberSuffix(std::string objectName);
    // std::string GetValidObjectName(std::string objectName);
    std::string GetValidShaderName(std::string name);
    std::string GetValidMaterialName(std::string name);
    std::string GetValidTextureName(std::string name);
    std::string GetValidMeshName(std::string name);


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