///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "noname.h"

///////////////////////////////////////////////////////////////////////////

LE3EditorWindow::LE3EditorWindow( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );

	m_auiToolBar4 = new wxAuiToolBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_TB_HORZ_LAYOUT|wxAUI_TB_PLAIN_BACKGROUND );
	m_tool5 = m_auiToolBar4->AddTool( wxID_ANY, wxT("tool"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_tool6 = m_auiToolBar4->AddTool( wxID_ANY, wxT("tool"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_tool7 = m_auiToolBar4->AddTool( wxID_ANY, wxT("tool"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_auiToolBar4->Realize();

	bSizer9->Add( m_auiToolBar4, 0, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxHORIZONTAL );

	m_OpenGLContainer = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	bSizer11->Add( m_OpenGLContainer, 5, wxEXPAND | wxALL, 5 );

	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxVERTICAL );

	m_notebook1 = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panel2 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer91;
	bSizer91 = new wxBoxSizer( wxVERTICAL );

	m_treeListCtrl2 = new wxTreeListCtrl( m_panel2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTL_DEFAULT_STYLE );

	bSizer91->Add( m_treeListCtrl2, 1, wxEXPAND | wxALL, 5 );


	m_panel2->SetSizer( bSizer91 );
	m_panel2->Layout();
	bSizer91->Fit( m_panel2 );
	m_notebook1->AddPage( m_panel2, wxT("Scene"), false );
	m_panel3 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );

	m_assetsNotebook = new wxNotebook( m_panel3, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_shadersPanel = new wxPanel( m_assetsNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerShadersPanel;
	bSizerShadersPanel = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizerShadersToolbar;
	bSizerShadersToolbar = new wxBoxSizer( wxHORIZONTAL );

	m_loadShaderButton = new wxButton( m_shadersPanel, wxID_ANY, wxT("Load"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerShadersToolbar->Add( m_loadShaderButton, 1, wxALL|wxEXPAND, 5 );

	m_newShaderButton = new wxButton( m_shadersPanel, wxID_ANY, wxT("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerShadersToolbar->Add( m_newShaderButton, 1, wxALL|wxEXPAND, 5 );


	bSizerShadersPanel->Add( bSizerShadersToolbar, 1, wxEXPAND, 5 );

	m_treeListShaders = new wxTreeListCtrl( m_shadersPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTL_DEFAULT_STYLE );

	bSizerShadersPanel->Add( m_treeListShaders, 6, wxEXPAND | wxALL, 5 );


	m_shadersPanel->SetSizer( bSizerShadersPanel );
	m_shadersPanel->Layout();
	bSizerShadersPanel->Fit( m_shadersPanel );
	m_assetsNotebook->AddPage( m_shadersPanel, wxT("Shaders"), true );
	m_materialsPanel = new wxPanel( m_assetsNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerMaterialsPanel;
	bSizerMaterialsPanel = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizerMaterialsToolbar;
	bSizerMaterialsToolbar = new wxBoxSizer( wxHORIZONTAL );

	m_newMaterialButton = new wxButton( m_materialsPanel, wxID_ANY, wxT("New"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerMaterialsToolbar->Add( m_newMaterialButton, 1, wxALL|wxEXPAND, 5 );

	m_deleteMaterialButton = new wxButton( m_materialsPanel, wxID_ANY, wxT("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerMaterialsToolbar->Add( m_deleteMaterialButton, 1, wxALL|wxEXPAND, 5 );


	bSizerMaterialsPanel->Add( bSizerMaterialsToolbar, 1, wxEXPAND, 5 );

	m_treeListMaterials = new wxTreeListCtrl( m_materialsPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTL_DEFAULT_STYLE );

	bSizerMaterialsPanel->Add( m_treeListMaterials, 6, wxEXPAND | wxALL, 5 );


	m_materialsPanel->SetSizer( bSizerMaterialsPanel );
	m_materialsPanel->Layout();
	bSizerMaterialsPanel->Fit( m_materialsPanel );
	m_assetsNotebook->AddPage( m_materialsPanel, wxT("Materials"), false );
	m_texturesPanel = new wxPanel( m_assetsNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerTexturesPanel;
	bSizerTexturesPanel = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizerTexturesToolbar;
	bSizerTexturesToolbar = new wxBoxSizer( wxHORIZONTAL );

	m_loadTextureButton = new wxButton( m_texturesPanel, wxID_ANY, wxT("Load"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerTexturesToolbar->Add( m_loadTextureButton, 1, wxALL|wxEXPAND, 5 );

	m_deleteTextureButton = new wxButton( m_texturesPanel, wxID_ANY, wxT("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerTexturesToolbar->Add( m_deleteTextureButton, 1, wxALL|wxEXPAND, 5 );


	bSizerTexturesPanel->Add( bSizerTexturesToolbar, 1, wxEXPAND, 5 );

	m_treeListTextures = new wxTreeListCtrl( m_texturesPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTL_DEFAULT_STYLE );

	bSizerTexturesPanel->Add( m_treeListTextures, 6, wxEXPAND | wxALL, 5 );


	m_texturesPanel->SetSizer( bSizerTexturesPanel );
	m_texturesPanel->Layout();
	bSizerTexturesPanel->Fit( m_texturesPanel );
	m_assetsNotebook->AddPage( m_texturesPanel, wxT("Textures"), false );
	m_panel7 = new wxPanel( m_assetsNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerMeshesPanel;
	bSizerMeshesPanel = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizerMeshesToolbar;
	bSizerMeshesToolbar = new wxBoxSizer( wxHORIZONTAL );

	m_loadMeshButton = new wxButton( m_panel7, wxID_ANY, wxT("Load"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerMeshesToolbar->Add( m_loadMeshButton, 1, wxALL|wxEXPAND, 5 );

	m_deleteMeshButton = new wxButton( m_panel7, wxID_ANY, wxT("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerMeshesToolbar->Add( m_deleteMeshButton, 1, wxALL|wxEXPAND, 5 );


	bSizerMeshesPanel->Add( bSizerMeshesToolbar, 1, wxEXPAND, 5 );

	m_treeListMeshes = new wxTreeListCtrl( m_panel7, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTL_DEFAULT_STYLE );

	bSizerMeshesPanel->Add( m_treeListMeshes, 6, wxEXPAND | wxALL, 5 );


	m_panel7->SetSizer( bSizerMeshesPanel );
	m_panel7->Layout();
	bSizerMeshesPanel->Fit( m_panel7 );
	m_assetsNotebook->AddPage( m_panel7, wxT("Meshes"), false );

	bSizer10->Add( m_assetsNotebook, 1, wxEXPAND | wxALL, 5 );


	m_panel3->SetSizer( bSizer10 );
	m_panel3->Layout();
	bSizer10->Fit( m_panel3 );
	m_notebook1->AddPage( m_panel3, wxT("Assets"), true );

	bSizer12->Add( m_notebook1, 1, wxEXPAND | wxALL, 5 );

	m_propertyGrid = new wxPropertyGrid(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxPG_DEFAULT_STYLE);
	bSizer12->Add( m_propertyGrid, 1, wxALL|wxEXPAND, 5 );


	bSizer11->Add( bSizer12, 2, wxEXPAND, 5 );


	bSizer9->Add( bSizer11, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer9 );
	this->Layout();
	m_statusBar2 = this->CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );
	m_menubar2 = new wxMenuBar( 0 );
	m_menu2 = new wxMenu();
	wxMenuItem* m_menuItem1;
	m_menuItem1 = new wxMenuItem( m_menu2, wxID_ANY, wxString( wxT("Open...") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu2->Append( m_menuItem1 );

	m_menubar2->Append( m_menu2, wxT("File") );

	this->SetMenuBar( m_menubar2 );


	this->Centre( wxBOTH );

	// Connect Events
	m_treeListShaders->Connect( wxEVT_TREELIST_SELECTION_CHANGED, wxTreeListEventHandler( LE3EditorWindow::OnSelectShader ), NULL, this );
	m_propertyGrid->Connect( wxEVT_PG_CHANGED, wxPropertyGridEventHandler( LE3EditorWindow::OnPropertyChange ), NULL, this );
}

LE3EditorWindow::~LE3EditorWindow()
{
	// Disconnect Events
	m_treeListShaders->Disconnect( wxEVT_TREELIST_SELECTION_CHANGED, wxTreeListEventHandler( LE3EditorWindow::OnSelectShader ), NULL, this );
	m_propertyGrid->Disconnect( wxEVT_PG_CHANGED, wxPropertyGridEventHandler( LE3EditorWindow::OnPropertyChange ), NULL, this );

}
