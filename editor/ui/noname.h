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

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class LE3EditorWindow
///////////////////////////////////////////////////////////////////////////////
class LE3EditorWindow : public wxFrame
{
	private:

	protected:
		wxAuiToolBar* m_auiToolBar4;
		wxAuiToolBarItem* m_tool5;
		wxAuiToolBarItem* m_tool7;
		wxAuiToolBarItem* m_tool6;
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
		virtual void OnMouseClick( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnSelectObjectInGraph( wxTreeListEvent& event ) { event.Skip(); }
		virtual void OnSelectShader( wxTreeListEvent& event ) { event.Skip(); }
		virtual void OnPropertyChange( wxPropertyGridEvent& event ) { event.Skip(); }


	public:
		wxPanel* m_OpenGLContainer;

		LE3EditorWindow( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("LightEngine3 Editor"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1360,768 ), long style = wxDEFAULT_FRAME_STYLE|wxSTAY_ON_TOP|wxTAB_TRAVERSAL );

		~LE3EditorWindow();

};

