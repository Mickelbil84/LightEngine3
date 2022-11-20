///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/gdicmn.h>
#include <wx/aui/aui.h>
#include <wx/aui/auibar.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/panel.h>
#include <wx/treelist.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/notebook.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>
#include <wx/statusbr.h>
#include <wx/menu.h>
#include <wx/frame.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class LE3EditorWindow
///////////////////////////////////////////////////////////////////////////////
class LE3EditorWindow : public wxFrame
{
	private:

	protected:
		wxAuiToolBar* m_topToolbar;
		wxAuiToolBarItem* m_newTool;
		wxAuiToolBarItem* m_loadTool;
		wxAuiToolBarItem* m_saveTool;
		wxAuiToolBarItem* m_saveAsTool;
		wxAuiToolBarItem* m_undoTool;
		wxAuiToolBarItem* m_redoTool;
		wxAuiToolBarItem* m_gizmoSelectTool;
		wxAuiToolBarItem* m_gizmoMoveTool;
		wxAuiToolBarItem* m_gizmoRotateTool;
		wxAuiToolBarItem* m_gizmoScaleTool;
		wxAuiToolBarItem* m_collisionTool;
		wxAuiToolBarItem* m_bulletCollisionTool;
		wxAuiToolBar* m_sideToolbar;
		wxAuiToolBarItem* m_addCubeTool;
		wxAuiToolBarItem* m_addSphereTool;
		wxAuiToolBarItem* m_addCylinderTool;
		wxAuiToolBarItem* m_addConeTool;
		wxAuiToolBarItem* m_addStaticMeshTool;
		wxAuiToolBarItem* m_tool27;
		wxAuiToolBarItem* m_tool28;
		wxAuiToolBarItem* m_tool29;
		wxNotebook* m_notebook1;
		wxPanel* m_panel2;
		wxTreeListCtrl* m_sceneGraphTree;
		wxPanel* m_panel3;
		wxNotebook* m_assetsNotebook;
		wxPanel* m_shadersPanel;
		wxButton* m_loadShaderButton;
		wxButton* m_newShaderButton;
		wxTreeListCtrl* m_treeListShaders;
		wxPanel* m_materialsPanel;
		wxButton* m_newMaterialButton;
		wxButton* m_deleteMaterialButton;
		wxTreeListCtrl* m_treeListMaterials;
		wxPanel* m_texturesPanel;
		wxButton* m_loadTextureButton;
		wxButton* m_deleteTextureButton;
		wxTreeListCtrl* m_treeListTextures;
		wxPanel* m_panel7;
		wxButton* m_loadMeshButton;
		wxButton* m_deleteMeshButton;
		wxTreeListCtrl* m_treeListMeshes;
		wxPropertyGrid* m_propertyGrid;
		wxStatusBar* m_statusBar2;
		wxMenuBar* m_menubar2;
		wxMenu* m_menu2;

		// Virtual event handlers, override them in your derived class
		virtual void OnNewScene( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnLoadScene( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSaveScene( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSaveSceneAs( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCollisionToolToggle( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBulletCollisionToolToggle( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAddCube( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAddSphere( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAddCylinder( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAddCone( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAddStaticMesh( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMouseClick( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnSelectObjectInGraph( wxTreeListEvent& event ) { event.Skip(); }
		virtual void OnNewShader( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDeleteShader( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSelectShader( wxTreeListEvent& event ) { event.Skip(); }
		virtual void OnNewMaterial( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDeleteMaterial( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSelectMaterial( wxTreeListEvent& event ) { event.Skip(); }
		virtual void OnNewTexture( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDeleteTexture( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSelectTexture( wxTreeListEvent& event ) { event.Skip(); }
		virtual void OnNewMesh( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDeleteMesh( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSelectMesh( wxTreeListEvent& event ) { event.Skip(); }
		virtual void OnPropertyChange( wxPropertyGridEvent& event ) { event.Skip(); }


	public:
		wxPanel* m_OpenGLContainer;

		LE3EditorWindow( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("LightEngine3 Editor"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1360,768 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~LE3EditorWindow();

};

///////////////////////////////////////////////////////////////////////////////
/// Class LE3NewShaderDialog
///////////////////////////////////////////////////////////////////////////////
class LE3NewShaderDialog : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText1;
		wxStaticText* m_staticText3;
		wxStaticText* m_staticText4;
		wxButton* m_cancelBtn;
		wxButton* m_createBtn;

	public:
		wxTextCtrl* m_nameText;
		wxTextCtrl* m_vertexShaderText;
		wxTextCtrl* m_fragmentShaderText;

		LE3NewShaderDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("New Shader"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 600,170 ), long style = wxDEFAULT_DIALOG_STYLE );

		~LE3NewShaderDialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class LE3NewMaterialDialog
///////////////////////////////////////////////////////////////////////////////
class LE3NewMaterialDialog : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText4;
		wxStaticText* m_staticText5;
		wxButton* m_cancelBtn;
		wxButton* m_createBtn;

	public:
		wxTextCtrl* m_nameText;
		wxTextCtrl* m_shaderNametext;

		LE3NewMaterialDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("New Material"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 600,140 ), long style = wxDEFAULT_DIALOG_STYLE );

		~LE3NewMaterialDialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class LE3NewTextureDialog
///////////////////////////////////////////////////////////////////////////////
class LE3NewTextureDialog : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText6;
		wxStaticText* m_staticText7;
		wxButton* m_cancelBtn;
		wxButton* m_createBtn;

	public:
		wxTextCtrl* m_nameText;
		wxTextCtrl* m_pathText;

		LE3NewTextureDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("New Texture"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 600,140 ), long style = wxDEFAULT_DIALOG_STYLE );

		~LE3NewTextureDialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class LE3NewMeshDialog
///////////////////////////////////////////////////////////////////////////////
class LE3NewMeshDialog : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText8;
		wxStaticText* m_staticText9;
		wxButton* m_cancelBtn;
		wxButton* m_createBtn;

	public:
		wxTextCtrl* m_nameText;
		wxTextCtrl* m_pathText;

		LE3NewMeshDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("New Mesh"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 600,140 ), long style = wxDEFAULT_DIALOG_STYLE );

		~LE3NewMeshDialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class LE3AddCubeDialog
///////////////////////////////////////////////////////////////////////////////
class LE3AddCubeDialog : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText10;
		wxStaticText* m_staticText14;
		wxStaticText* m_staticText11;
		wxStaticText* m_staticText12;
		wxStaticText* m_staticText13;
		wxButton* m_cancelBtn;
		wxButton* m_addBtn;

	public:
		wxTextCtrl* m_nameText;
		wxTextCtrl* m_materialText;
		wxTextCtrl* m_widthText;
		wxTextCtrl* m_heightText;
		wxTextCtrl* m_depthText;

		LE3AddCubeDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Add Cube"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 200,230 ), long style = wxDEFAULT_DIALOG_STYLE );

		~LE3AddCubeDialog();

};

