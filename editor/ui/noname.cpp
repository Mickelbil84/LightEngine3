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
	this->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_INFOBK ) );
	this->SetBackgroundColour( wxColour( 225, 225, 225 ) );

	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );

	m_topToolbar = new wxAuiToolBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_TB_HORZ_LAYOUT|wxAUI_TB_PLAIN_BACKGROUND );
	m_newTool = m_topToolbar->AddTool( wxID_ANY, wxT("tool"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_loadTool = m_topToolbar->AddTool( wxID_ANY, wxT("tool"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_saveTool = m_topToolbar->AddTool( wxID_ANY, wxT("tool"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_saveAsTool = m_topToolbar->AddTool( wxID_ANY, wxT("tool"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_topToolbar->AddSeparator();

	m_undoTool = m_topToolbar->AddTool( wxID_ANY, wxT("tool"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_redoTool = m_topToolbar->AddTool( wxID_ANY, wxT("tool"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_topToolbar->AddSeparator();

	m_gizmoSelectTool = m_topToolbar->AddTool( wxID_ANY, wxT("tool"), wxNullBitmap, wxNullBitmap, wxITEM_CHECK, wxEmptyString, wxEmptyString, NULL );

	m_gizmoMoveTool = m_topToolbar->AddTool( wxID_ANY, wxT("tool"), wxNullBitmap, wxNullBitmap, wxITEM_CHECK, wxEmptyString, wxEmptyString, NULL );

	m_gizmoRotateTool = m_topToolbar->AddTool( wxID_ANY, wxT("tool"), wxNullBitmap, wxNullBitmap, wxITEM_CHECK, wxEmptyString, wxEmptyString, NULL );

	m_gizmoScaleTool = m_topToolbar->AddTool( wxID_ANY, wxT("tool"), wxNullBitmap, wxNullBitmap, wxITEM_CHECK, wxEmptyString, wxEmptyString, NULL );

	m_topToolbar->AddSeparator();

	m_collisionTool = m_topToolbar->AddTool( wxID_ANY, wxT("tool"), wxNullBitmap, wxNullBitmap, wxITEM_CHECK, wxEmptyString, wxEmptyString, NULL );

	m_bulletCollisionTool = m_topToolbar->AddTool( wxID_ANY, wxT("tool"), wxNullBitmap, wxNullBitmap, wxITEM_CHECK, wxEmptyString, wxEmptyString, NULL );

	m_topToolbar->AddSeparator();

	m_reparentTool = m_topToolbar->AddTool( wxID_ANY, wxT("tool"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_topToolbar->Realize();

	bSizer9->Add( m_topToolbar, 0, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxHORIZONTAL );

	m_sideToolbar = new wxAuiToolBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_TB_HORZ_LAYOUT|wxAUI_TB_PLAIN_BACKGROUND|wxAUI_TB_VERTICAL );
	m_addCubeTool = m_sideToolbar->AddTool( wxID_ANY, wxT("tool"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_addSphereTool = m_sideToolbar->AddTool( wxID_ANY, wxT("tool"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_addCylinderTool = m_sideToolbar->AddTool( wxID_ANY, wxT("tool"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_addConeTool = m_sideToolbar->AddTool( wxID_ANY, wxT("tool"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_addStaticMeshTool = m_sideToolbar->AddTool( wxID_ANY, wxT("tool"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_sideToolbar->AddSeparator();

	m_addEmptyTool = m_sideToolbar->AddTool( wxID_ANY, wxT("tool"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_tool28 = m_sideToolbar->AddTool( wxID_ANY, wxT("tool"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_tool29 = m_sideToolbar->AddTool( wxID_ANY, wxT("tool"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_sideToolbar->AddSeparator();

	m_sideToolbar->Realize();

	bSizer11->Add( m_sideToolbar, 0, wxALL, 5 );

	m_OpenGLContainer = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	bSizer11->Add( m_OpenGLContainer, 10, wxEXPAND | wxALL, 5 );

	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxVERTICAL );

	m_notebook1 = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panel2 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer91;
	bSizer91 = new wxBoxSizer( wxVERTICAL );

	m_sceneGraphTree = new wxTreeListCtrl( m_panel2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTL_DEFAULT_STYLE );

	bSizer91->Add( m_sceneGraphTree, 1, wxEXPAND | wxALL, 5 );


	m_panel2->SetSizer( bSizer91 );
	m_panel2->Layout();
	bSizer91->Fit( m_panel2 );
	m_notebook1->AddPage( m_panel2, wxT("Scene"), true );
	m_panel3 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );

	m_assetsNotebook = new wxNotebook( m_panel3, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_shadersPanel = new wxPanel( m_assetsNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerShadersPanel;
	bSizerShadersPanel = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizerShadersToolbar;
	bSizerShadersToolbar = new wxBoxSizer( wxHORIZONTAL );

	m_loadShaderButton = new wxButton( m_shadersPanel, wxID_ANY, wxT("New"), wxDefaultPosition, wxDefaultSize, 0 );
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

	m_loadTextureButton = new wxButton( m_texturesPanel, wxID_ANY, wxT("New"), wxDefaultPosition, wxDefaultSize, 0 );
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

	m_loadMeshButton = new wxButton( m_panel7, wxID_ANY, wxT("New"), wxDefaultPosition, wxDefaultSize, 0 );
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
	m_notebook1->AddPage( m_panel3, wxT("Assets"), false );

	bSizer12->Add( m_notebook1, 1, wxEXPAND | wxALL, 5 );

	m_propertyGrid = new wxPropertyGrid(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxPG_DEFAULT_STYLE);
	bSizer12->Add( m_propertyGrid, 1, wxALL|wxEXPAND, 5 );


	bSizer11->Add( bSizer12, 3, wxEXPAND, 5 );


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
	this->Connect( m_newTool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( LE3EditorWindow::OnNewScene ) );
	this->Connect( m_loadTool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( LE3EditorWindow::OnLoadScene ) );
	this->Connect( m_saveTool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( LE3EditorWindow::OnSaveScene ) );
	this->Connect( m_saveAsTool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( LE3EditorWindow::OnSaveSceneAs ) );
	this->Connect( m_collisionTool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( LE3EditorWindow::OnCollisionToolToggle ) );
	this->Connect( m_bulletCollisionTool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( LE3EditorWindow::OnBulletCollisionToolToggle ) );
	this->Connect( m_reparentTool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( LE3EditorWindow::OnReparent ) );
	this->Connect( m_addCubeTool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( LE3EditorWindow::OnAddCube ) );
	this->Connect( m_addSphereTool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( LE3EditorWindow::OnAddSphere ) );
	this->Connect( m_addCylinderTool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( LE3EditorWindow::OnAddCylinder ) );
	this->Connect( m_addConeTool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( LE3EditorWindow::OnAddCone ) );
	this->Connect( m_addStaticMeshTool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( LE3EditorWindow::OnAddStaticMesh ) );
	this->Connect( m_addEmptyTool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( LE3EditorWindow::OnAddEmpty ) );
	m_OpenGLContainer->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( LE3EditorWindow::OnMouseClick ), NULL, this );
	m_sceneGraphTree->Connect( wxEVT_TREELIST_SELECTION_CHANGED, wxTreeListEventHandler( LE3EditorWindow::OnSelectObjectInGraph ), NULL, this );
	m_loadShaderButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LE3EditorWindow::OnNewShader ), NULL, this );
	m_newShaderButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LE3EditorWindow::OnDeleteShader ), NULL, this );
	m_treeListShaders->Connect( wxEVT_TREELIST_SELECTION_CHANGED, wxTreeListEventHandler( LE3EditorWindow::OnSelectShader ), NULL, this );
	m_newMaterialButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LE3EditorWindow::OnNewMaterial ), NULL, this );
	m_deleteMaterialButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LE3EditorWindow::OnDeleteMaterial ), NULL, this );
	m_treeListMaterials->Connect( wxEVT_TREELIST_SELECTION_CHANGED, wxTreeListEventHandler( LE3EditorWindow::OnSelectMaterial ), NULL, this );
	m_loadTextureButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LE3EditorWindow::OnNewTexture ), NULL, this );
	m_deleteTextureButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LE3EditorWindow::OnDeleteTexture ), NULL, this );
	m_treeListTextures->Connect( wxEVT_TREELIST_SELECTION_CHANGED, wxTreeListEventHandler( LE3EditorWindow::OnSelectTexture ), NULL, this );
	m_loadMeshButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LE3EditorWindow::OnNewMesh ), NULL, this );
	m_deleteMeshButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LE3EditorWindow::OnDeleteMesh ), NULL, this );
	m_treeListMeshes->Connect( wxEVT_TREELIST_SELECTION_CHANGED, wxTreeListEventHandler( LE3EditorWindow::OnSelectMesh ), NULL, this );
	m_propertyGrid->Connect( wxEVT_PG_CHANGED, wxPropertyGridEventHandler( LE3EditorWindow::OnPropertyChange ), NULL, this );
}

LE3EditorWindow::~LE3EditorWindow()
{
	// Disconnect Events
	this->Disconnect( m_newTool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( LE3EditorWindow::OnNewScene ) );
	this->Disconnect( m_loadTool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( LE3EditorWindow::OnLoadScene ) );
	this->Disconnect( m_saveTool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( LE3EditorWindow::OnSaveScene ) );
	this->Disconnect( m_saveAsTool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( LE3EditorWindow::OnSaveSceneAs ) );
	this->Disconnect( m_collisionTool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( LE3EditorWindow::OnCollisionToolToggle ) );
	this->Disconnect( m_bulletCollisionTool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( LE3EditorWindow::OnBulletCollisionToolToggle ) );
	this->Disconnect( m_reparentTool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( LE3EditorWindow::OnReparent ) );
	this->Disconnect( m_addCubeTool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( LE3EditorWindow::OnAddCube ) );
	this->Disconnect( m_addSphereTool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( LE3EditorWindow::OnAddSphere ) );
	this->Disconnect( m_addCylinderTool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( LE3EditorWindow::OnAddCylinder ) );
	this->Disconnect( m_addConeTool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( LE3EditorWindow::OnAddCone ) );
	this->Disconnect( m_addStaticMeshTool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( LE3EditorWindow::OnAddStaticMesh ) );
	this->Disconnect( m_addEmptyTool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( LE3EditorWindow::OnAddEmpty ) );
	m_OpenGLContainer->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( LE3EditorWindow::OnMouseClick ), NULL, this );
	m_sceneGraphTree->Disconnect( wxEVT_TREELIST_SELECTION_CHANGED, wxTreeListEventHandler( LE3EditorWindow::OnSelectObjectInGraph ), NULL, this );
	m_loadShaderButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LE3EditorWindow::OnNewShader ), NULL, this );
	m_newShaderButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LE3EditorWindow::OnDeleteShader ), NULL, this );
	m_treeListShaders->Disconnect( wxEVT_TREELIST_SELECTION_CHANGED, wxTreeListEventHandler( LE3EditorWindow::OnSelectShader ), NULL, this );
	m_newMaterialButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LE3EditorWindow::OnNewMaterial ), NULL, this );
	m_deleteMaterialButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LE3EditorWindow::OnDeleteMaterial ), NULL, this );
	m_treeListMaterials->Disconnect( wxEVT_TREELIST_SELECTION_CHANGED, wxTreeListEventHandler( LE3EditorWindow::OnSelectMaterial ), NULL, this );
	m_loadTextureButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LE3EditorWindow::OnNewTexture ), NULL, this );
	m_deleteTextureButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LE3EditorWindow::OnDeleteTexture ), NULL, this );
	m_treeListTextures->Disconnect( wxEVT_TREELIST_SELECTION_CHANGED, wxTreeListEventHandler( LE3EditorWindow::OnSelectTexture ), NULL, this );
	m_loadMeshButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LE3EditorWindow::OnNewMesh ), NULL, this );
	m_deleteMeshButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LE3EditorWindow::OnDeleteMesh ), NULL, this );
	m_treeListMeshes->Disconnect( wxEVT_TREELIST_SELECTION_CHANGED, wxTreeListEventHandler( LE3EditorWindow::OnSelectMesh ), NULL, this );
	m_propertyGrid->Disconnect( wxEVT_PG_CHANGED, wxPropertyGridEventHandler( LE3EditorWindow::OnPropertyChange ), NULL, this );

}

LE3NewShaderDialog::LE3NewShaderDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer161;
	bSizer161 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	m_staticText1->SetMinSize( wxSize( 120,-1 ) );

	bSizer161->Add( m_staticText1, 0, wxALL, 5 );

	m_nameText = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer161->Add( m_nameText, 1, wxALL|wxEXPAND, 5 );


	bSizer14->Add( bSizer161, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer17;
	bSizer17 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("Vertex Shader:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	m_staticText3->SetMinSize( wxSize( 120,-1 ) );

	bSizer17->Add( m_staticText3, 0, wxALL, 5 );

	m_vertexShaderText = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer17->Add( m_vertexShaderText, 1, wxALL|wxEXPAND, 5 );


	bSizer14->Add( bSizer17, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer18;
	bSizer18 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText4 = new wxStaticText( this, wxID_ANY, wxT("Fragment Shader:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	m_staticText4->SetMinSize( wxSize( 120,-1 ) );

	bSizer18->Add( m_staticText4, 0, wxALL, 5 );

	m_fragmentShaderText = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer18->Add( m_fragmentShaderText, 1, wxALL|wxEXPAND, 5 );


	bSizer14->Add( bSizer18, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer( wxHORIZONTAL );

	m_cancelBtn = new wxButton( this, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer16->Add( m_cancelBtn, 1, wxALL|wxEXPAND, 5 );

	m_createBtn = new wxButton( this, wxID_OK, wxT("Create"), wxDefaultPosition, wxDefaultSize, 0 );

	m_createBtn->SetDefault();
	bSizer16->Add( m_createBtn, 1, wxALL|wxEXPAND, 5 );


	bSizer14->Add( bSizer16, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer14 );
	this->Layout();

	this->Centre( wxBOTH );
}

LE3NewShaderDialog::~LE3NewShaderDialog()
{
}

LE3NewMaterialDialog::LE3NewMaterialDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer20;
	bSizer20 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText4 = new wxStaticText( this, wxID_ANY, wxT("Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	m_staticText4->SetMinSize( wxSize( 60,-1 ) );

	bSizer20->Add( m_staticText4, 0, wxALL, 5 );

	m_nameText = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer20->Add( m_nameText, 1, wxALL|wxEXPAND, 5 );


	bSizer19->Add( bSizer20, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText5 = new wxStaticText( this, wxID_ANY, wxT("Shader:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	m_staticText5->SetMinSize( wxSize( 60,-1 ) );

	bSizer21->Add( m_staticText5, 0, wxALL, 5 );

	m_shaderText = new wxComboBox( this, wxID_ANY, wxT("Select Shader..."), wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY|wxCB_SORT );
	bSizer21->Add( m_shaderText, 1, wxALL|wxEXPAND, 5 );


	bSizer19->Add( bSizer21, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer22;
	bSizer22 = new wxBoxSizer( wxHORIZONTAL );

	m_cancelBtn = new wxButton( this, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer22->Add( m_cancelBtn, 1, wxALL|wxEXPAND, 5 );

	m_createBtn = new wxButton( this, wxID_OK, wxT("Create"), wxDefaultPosition, wxDefaultSize, 0 );

	m_createBtn->SetDefault();
	bSizer22->Add( m_createBtn, 1, wxALL|wxEXPAND, 5 );


	bSizer19->Add( bSizer22, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer19 );
	this->Layout();

	this->Centre( wxBOTH );
}

LE3NewMaterialDialog::~LE3NewMaterialDialog()
{
}

LE3NewTextureDialog::LE3NewTextureDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer23;
	bSizer23 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer24;
	bSizer24 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText6 = new wxStaticText( this, wxID_ANY, wxT("Name:"), wxDefaultPosition, wxSize( 120,-1 ), 0 );
	m_staticText6->Wrap( -1 );
	bSizer24->Add( m_staticText6, 0, wxALL, 5 );

	m_nameText = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer24->Add( m_nameText, 1, wxALL|wxEXPAND, 5 );


	bSizer23->Add( bSizer24, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer25;
	bSizer25 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText7 = new wxStaticText( this, wxID_ANY, wxT("Texture Path:"), wxDefaultPosition, wxSize( 120,-1 ), 0 );
	m_staticText7->Wrap( -1 );
	bSizer25->Add( m_staticText7, 0, wxALL, 5 );

	m_pathText = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer25->Add( m_pathText, 1, wxALL|wxEXPAND, 5 );


	bSizer23->Add( bSizer25, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer26;
	bSizer26 = new wxBoxSizer( wxHORIZONTAL );

	m_cancelBtn = new wxButton( this, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer26->Add( m_cancelBtn, 1, wxALL|wxEXPAND, 5 );

	m_createBtn = new wxButton( this, wxID_OK, wxT("Create"), wxDefaultPosition, wxDefaultSize, 0 );

	m_createBtn->SetDefault();
	bSizer26->Add( m_createBtn, 1, wxALL|wxEXPAND, 5 );


	bSizer23->Add( bSizer26, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer23 );
	this->Layout();

	this->Centre( wxBOTH );
}

LE3NewTextureDialog::~LE3NewTextureDialog()
{
}

LE3NewMeshDialog::LE3NewMeshDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer27;
	bSizer27 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer28;
	bSizer28 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText8 = new wxStaticText( this, wxID_ANY, wxT("Name:"), wxDefaultPosition, wxSize( 120,-1 ), 0 );
	m_staticText8->Wrap( -1 );
	bSizer28->Add( m_staticText8, 0, wxALL, 5 );

	m_nameText = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer28->Add( m_nameText, 1, wxALL|wxEXPAND, 5 );


	bSizer27->Add( bSizer28, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer29;
	bSizer29 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText9 = new wxStaticText( this, wxID_ANY, wxT("Mesh Path:"), wxDefaultPosition, wxSize( 120,-1 ), 0 );
	m_staticText9->Wrap( -1 );
	bSizer29->Add( m_staticText9, 0, wxALL, 5 );

	m_pathText = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer29->Add( m_pathText, 1, wxALL|wxEXPAND, 5 );


	bSizer27->Add( bSizer29, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer30;
	bSizer30 = new wxBoxSizer( wxHORIZONTAL );

	m_cancelBtn = new wxButton( this, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer30->Add( m_cancelBtn, 1, wxALL|wxEXPAND, 5 );

	m_createBtn = new wxButton( this, wxID_OK, wxT("Create"), wxDefaultPosition, wxDefaultSize, 0 );

	m_createBtn->SetDefault();
	bSizer30->Add( m_createBtn, 1, wxALL|wxEXPAND, 5 );


	bSizer27->Add( bSizer30, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer27 );
	this->Layout();

	this->Centre( wxBOTH );
}

LE3NewMeshDialog::~LE3NewMeshDialog()
{
}

LE3AddCubeDialog::LE3AddCubeDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer31;
	bSizer31 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer32;
	bSizer32 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText10 = new wxStaticText( this, wxID_ANY, wxT("Name:"), wxDefaultPosition, wxSize( 55,-1 ), 0 );
	m_staticText10->Wrap( -1 );
	bSizer32->Add( m_staticText10, 0, wxALL, 5 );

	m_nameText = new wxTextCtrl( this, wxID_ANY, wxT("cube"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer32->Add( m_nameText, 1, wxALL|wxEXPAND, 5 );


	bSizer31->Add( bSizer32, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer37;
	bSizer37 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText14 = new wxStaticText( this, wxID_ANY, wxT("Material:"), wxDefaultPosition, wxSize( 55,-1 ), 0 );
	m_staticText14->Wrap( -1 );
	bSizer37->Add( m_staticText14, 0, wxALL, 5 );

	m_materialText = new wxComboBox( this, wxID_ANY, wxT("Select Material..."), wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY|wxCB_SORT );
	bSizer37->Add( m_materialText, 1, wxALL|wxEXPAND, 5 );


	bSizer31->Add( bSizer37, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer33;
	bSizer33 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText11 = new wxStaticText( this, wxID_ANY, wxT("Width:"), wxDefaultPosition, wxSize( 55,-1 ), 0 );
	m_staticText11->Wrap( -1 );
	bSizer33->Add( m_staticText11, 0, wxALL, 5 );

	m_widthText = new wxTextCtrl( this, wxID_ANY, wxT("1"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer33->Add( m_widthText, 1, wxALL|wxEXPAND, 5 );


	bSizer31->Add( bSizer33, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer34;
	bSizer34 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText12 = new wxStaticText( this, wxID_ANY, wxT("Height:"), wxDefaultPosition, wxSize( 55,-1 ), 0 );
	m_staticText12->Wrap( -1 );
	bSizer34->Add( m_staticText12, 0, wxALL, 5 );

	m_heightText = new wxTextCtrl( this, wxID_ANY, wxT("1"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer34->Add( m_heightText, 1, wxALL|wxEXPAND, 5 );


	bSizer31->Add( bSizer34, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer35;
	bSizer35 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText13 = new wxStaticText( this, wxID_ANY, wxT("Depth:"), wxDefaultPosition, wxSize( 55,-1 ), 0 );
	m_staticText13->Wrap( -1 );
	bSizer35->Add( m_staticText13, 0, wxALL, 5 );

	m_depthText = new wxTextCtrl( this, wxID_ANY, wxT("1"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer35->Add( m_depthText, 1, wxALL|wxEXPAND, 5 );


	bSizer31->Add( bSizer35, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer36;
	bSizer36 = new wxBoxSizer( wxHORIZONTAL );

	m_cancelBtn = new wxButton( this, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer36->Add( m_cancelBtn, 1, wxALL|wxEXPAND, 5 );

	m_addBtn = new wxButton( this, wxID_OK, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0 );

	m_addBtn->SetDefault();
	bSizer36->Add( m_addBtn, 0, wxALL, 5 );


	bSizer31->Add( bSizer36, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer31 );
	this->Layout();

	this->Centre( wxBOTH );
}

LE3AddCubeDialog::~LE3AddCubeDialog()
{
}

LE3AddCylinderDialog::LE3AddCylinderDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer38;
	bSizer38 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer39;
	bSizer39 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText15 = new wxStaticText( this, wxID_ANY, wxT("Name:"), wxDefaultPosition, wxSize( 70,-1 ), 0 );
	m_staticText15->Wrap( -1 );
	bSizer39->Add( m_staticText15, 0, wxALL, 5 );

	m_nameText = new wxTextCtrl( this, wxID_ANY, wxT("cylinder"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer39->Add( m_nameText, 1, wxALL|wxEXPAND, 5 );


	bSizer38->Add( bSizer39, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer40;
	bSizer40 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText16 = new wxStaticText( this, wxID_ANY, wxT("Material:"), wxDefaultPosition, wxSize( 70,-1 ), 0 );
	m_staticText16->Wrap( -1 );
	bSizer40->Add( m_staticText16, 0, wxALL, 5 );

	m_materialText = new wxComboBox( this, wxID_ANY, wxT("Select Material..."), wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY|wxCB_SORT );
	bSizer40->Add( m_materialText, 1, wxALL|wxEXPAND, 5 );


	bSizer38->Add( bSizer40, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer42;
	bSizer42 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText17 = new wxStaticText( this, wxID_ANY, wxT("Radius:"), wxDefaultPosition, wxSize( 70,-1 ), 0 );
	m_staticText17->Wrap( -1 );
	bSizer42->Add( m_staticText17, 0, wxALL, 5 );

	m_radiusText = new wxTextCtrl( this, wxID_ANY, wxT("1"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer42->Add( m_radiusText, 1, wxALL|wxEXPAND, 5 );


	bSizer38->Add( bSizer42, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer43;
	bSizer43 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText18 = new wxStaticText( this, wxID_ANY, wxT("Height:"), wxDefaultPosition, wxSize( 70,-1 ), 0 );
	m_staticText18->Wrap( -1 );
	bSizer43->Add( m_staticText18, 0, wxALL, 5 );

	m_heightText = new wxTextCtrl( this, wxID_ANY, wxT("2"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer43->Add( m_heightText, 1, wxALL|wxEXPAND, 5 );


	bSizer38->Add( bSizer43, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer44;
	bSizer44 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText19 = new wxStaticText( this, wxID_ANY, wxT("Resolution:"), wxDefaultPosition, wxSize( 70,-1 ), 0 );
	m_staticText19->Wrap( -1 );
	bSizer44->Add( m_staticText19, 0, wxALL, 5 );

	m_resolutionText = new wxTextCtrl( this, wxID_ANY, wxT("16"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer44->Add( m_resolutionText, 1, wxALL|wxEXPAND, 5 );


	bSizer38->Add( bSizer44, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer46;
	bSizer46 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText20 = new wxStaticText( this, wxID_ANY, wxT("With Caps:"), wxDefaultPosition, wxSize( 70,-1 ), 0 );
	m_staticText20->Wrap( -1 );
	bSizer46->Add( m_staticText20, 0, wxALL, 5 );

	m_capsBool = new wxCheckBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_capsBool->SetValue(true);
	bSizer46->Add( m_capsBool, 0, wxALL, 5 );


	bSizer38->Add( bSizer46, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer45;
	bSizer45 = new wxBoxSizer( wxHORIZONTAL );

	m_cancelBtn = new wxButton( this, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer45->Add( m_cancelBtn, 1, wxALL|wxEXPAND, 5 );

	m_addBtn = new wxButton( this, wxID_OK, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0 );

	m_addBtn->SetDefault();
	bSizer45->Add( m_addBtn, 1, wxALL|wxEXPAND, 5 );


	bSizer38->Add( bSizer45, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer38 );
	this->Layout();

	this->Centre( wxBOTH );
}

LE3AddCylinderDialog::~LE3AddCylinderDialog()
{
}

LE3AddConeDialog::LE3AddConeDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer47;
	bSizer47 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer48;
	bSizer48 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText21 = new wxStaticText( this, wxID_ANY, wxT("Name:"), wxDefaultPosition, wxSize( 70,-1 ), 0 );
	m_staticText21->Wrap( -1 );
	bSizer48->Add( m_staticText21, 0, wxALL, 5 );

	m_nameText = new wxTextCtrl( this, wxID_ANY, wxT("cone"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer48->Add( m_nameText, 1, wxALL|wxEXPAND, 5 );


	bSizer47->Add( bSizer48, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer49;
	bSizer49 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText22 = new wxStaticText( this, wxID_ANY, wxT("Material:"), wxDefaultPosition, wxSize( 70,-1 ), 0 );
	m_staticText22->Wrap( -1 );
	bSizer49->Add( m_staticText22, 0, wxALL, 5 );

	m_materialText = new wxComboBox( this, wxID_ANY, wxT("Select Material..."), wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY|wxCB_SORT );
	bSizer49->Add( m_materialText, 1, wxALL|wxEXPAND, 5 );


	bSizer47->Add( bSizer49, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer50;
	bSizer50 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText23 = new wxStaticText( this, wxID_ANY, wxT("Radius:"), wxDefaultPosition, wxSize( 70,-1 ), 0 );
	m_staticText23->Wrap( -1 );
	bSizer50->Add( m_staticText23, 0, wxALL, 5 );

	m_radiusText = new wxTextCtrl( this, wxID_ANY, wxT("1"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer50->Add( m_radiusText, 1, wxALL|wxEXPAND, 5 );


	bSizer47->Add( bSizer50, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer51;
	bSizer51 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText24 = new wxStaticText( this, wxID_ANY, wxT("Height:"), wxDefaultPosition, wxSize( 70,-1 ), 0 );
	m_staticText24->Wrap( -1 );
	bSizer51->Add( m_staticText24, 0, wxALL, 5 );

	m_heightText = new wxTextCtrl( this, wxID_ANY, wxT("2"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer51->Add( m_heightText, 1, wxALL|wxEXPAND, 5 );


	bSizer47->Add( bSizer51, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer52;
	bSizer52 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText25 = new wxStaticText( this, wxID_ANY, wxT("Resolution:"), wxDefaultPosition, wxSize( 70,-1 ), 0 );
	m_staticText25->Wrap( -1 );
	bSizer52->Add( m_staticText25, 0, wxALL, 5 );

	m_resolutionText = new wxTextCtrl( this, wxID_ANY, wxT("16"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer52->Add( m_resolutionText, 1, wxALL|wxEXPAND, 5 );


	bSizer47->Add( bSizer52, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer53;
	bSizer53 = new wxBoxSizer( wxHORIZONTAL );

	m_cancelBtn = new wxButton( this, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer53->Add( m_cancelBtn, 1, wxALL|wxEXPAND, 5 );

	m_addBtn = new wxButton( this, wxID_OK, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0 );

	m_addBtn->SetDefault();
	bSizer53->Add( m_addBtn, 1, wxALL|wxEXPAND, 5 );


	bSizer47->Add( bSizer53, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer47 );
	this->Layout();

	this->Centre( wxBOTH );
}

LE3AddConeDialog::~LE3AddConeDialog()
{
}

LE3AddSphereDialog::LE3AddSphereDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer54;
	bSizer54 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer55;
	bSizer55 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText26 = new wxStaticText( this, wxID_ANY, wxT("Name:"), wxDefaultPosition, wxSize( 70,-1 ), 0 );
	m_staticText26->Wrap( -1 );
	bSizer55->Add( m_staticText26, 0, wxALL, 5 );

	m_nameText = new wxTextCtrl( this, wxID_ANY, wxT("sphere"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer55->Add( m_nameText, 1, wxALL|wxEXPAND, 5 );


	bSizer54->Add( bSizer55, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer56;
	bSizer56 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText27 = new wxStaticText( this, wxID_ANY, wxT("Material:"), wxDefaultPosition, wxSize( 70,-1 ), 0 );
	m_staticText27->Wrap( -1 );
	bSizer56->Add( m_staticText27, 0, wxALL, 5 );

	m_materialText = new wxComboBox( this, wxID_ANY, wxT("Select Material..."), wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY|wxCB_SORT );
	bSizer56->Add( m_materialText, 1, wxALL|wxEXPAND, 5 );


	bSizer54->Add( bSizer56, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer57;
	bSizer57 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText28 = new wxStaticText( this, wxID_ANY, wxT("Radius:"), wxDefaultPosition, wxSize( 70,-1 ), 0 );
	m_staticText28->Wrap( -1 );
	bSizer57->Add( m_staticText28, 0, wxALL, 5 );

	m_radiusText = new wxTextCtrl( this, wxID_ANY, wxT("1"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer57->Add( m_radiusText, 1, wxALL|wxEXPAND, 5 );


	bSizer54->Add( bSizer57, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer58;
	bSizer58 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText29 = new wxStaticText( this, wxID_ANY, wxT("Resolution:"), wxDefaultPosition, wxSize( 70,-1 ), 0 );
	m_staticText29->Wrap( -1 );
	bSizer58->Add( m_staticText29, 0, wxALL, 5 );

	m_resolutionText = new wxTextCtrl( this, wxID_ANY, wxT("16"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer58->Add( m_resolutionText, 1, wxALL|wxEXPAND, 5 );


	bSizer54->Add( bSizer58, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer59;
	bSizer59 = new wxBoxSizer( wxHORIZONTAL );

	m_cancelBtn = new wxButton( this, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer59->Add( m_cancelBtn, 1, wxALL|wxEXPAND, 5 );

	m_addBtn = new wxButton( this, wxID_OK, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0 );

	m_addBtn->SetDefault();
	bSizer59->Add( m_addBtn, 1, wxALL|wxEXPAND, 5 );


	bSizer54->Add( bSizer59, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer54 );
	this->Layout();

	this->Centre( wxBOTH );
}

LE3AddSphereDialog::~LE3AddSphereDialog()
{
}

LE3AddStaticMeshDialog::LE3AddStaticMeshDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer60;
	bSizer60 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer61;
	bSizer61 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText30 = new wxStaticText( this, wxID_ANY, wxT("Name:"), wxDefaultPosition, wxSize( 70,-1 ), 0 );
	m_staticText30->Wrap( -1 );
	bSizer61->Add( m_staticText30, 0, wxALL, 5 );

	m_nameText = new wxTextCtrl( this, wxID_ANY, wxT("staticMesh"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer61->Add( m_nameText, 1, wxALL|wxEXPAND, 5 );


	bSizer60->Add( bSizer61, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer62;
	bSizer62 = new wxBoxSizer( wxHORIZONTAL );

	wxStaticText* m_staticText31;
	m_staticText31 = new wxStaticText( this, wxID_ANY, wxT("Material:"), wxDefaultPosition, wxSize( 70,-1 ), 0 );
	m_staticText31->Wrap( -1 );
	bSizer62->Add( m_staticText31, 0, wxALL, 5 );

	m_materialText = new wxComboBox( this, wxID_ANY, wxT("Select Material..."), wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY|wxCB_SORT );
	bSizer62->Add( m_materialText, 0, wxALL, 5 );


	bSizer60->Add( bSizer62, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer63;
	bSizer63 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText32 = new wxStaticText( this, wxID_ANY, wxT("Mesh:"), wxDefaultPosition, wxSize( 70,-1 ), 0 );
	m_staticText32->Wrap( -1 );
	bSizer63->Add( m_staticText32, 0, wxALL, 5 );

	m_meshCombo = new wxComboBox( this, wxID_ANY, wxT("Select Mesh..."), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	bSizer63->Add( m_meshCombo, 1, wxALL|wxEXPAND, 5 );


	bSizer60->Add( bSizer63, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer64;
	bSizer64 = new wxBoxSizer( wxHORIZONTAL );

	m_cancelBtn = new wxButton( this, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer64->Add( m_cancelBtn, 1, wxALL|wxEXPAND, 5 );

	m_addBtn = new wxButton( this, wxID_OK, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0 );

	m_addBtn->SetDefault();
	bSizer64->Add( m_addBtn, 1, wxALL|wxEXPAND, 5 );


	bSizer60->Add( bSizer64, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer60 );
	this->Layout();

	this->Centre( wxBOTH );
}

LE3AddStaticMeshDialog::~LE3AddStaticMeshDialog()
{
}

LE3AddEmptyDialog::LE3AddEmptyDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer64;
	bSizer64 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer65;
	bSizer65 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText33 = new wxStaticText( this, wxID_ANY, wxT("Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText33->Wrap( -1 );
	bSizer65->Add( m_staticText33, 0, wxALL, 5 );

	m_nameText = new wxTextCtrl( this, wxID_ANY, wxT("empty"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer65->Add( m_nameText, 1, wxALL|wxEXPAND, 5 );


	bSizer64->Add( bSizer65, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer66;
	bSizer66 = new wxBoxSizer( wxHORIZONTAL );

	m_cancelBtn = new wxButton( this, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer66->Add( m_cancelBtn, 1, wxALL|wxEXPAND, 5 );

	m_addBtn = new wxButton( this, wxID_OK, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0 );

	m_addBtn->SetDefault();
	bSizer66->Add( m_addBtn, 1, wxALL|wxEXPAND, 5 );


	bSizer64->Add( bSizer66, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer64 );
	this->Layout();

	this->Centre( wxBOTH );
}

LE3AddEmptyDialog::~LE3AddEmptyDialog()
{
}

LE3ReparentDialog::LE3ReparentDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer67;
	bSizer67 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer68;
	bSizer68 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText34 = new wxStaticText( this, wxID_ANY, wxT("Object:"), wxDefaultPosition, wxSize( 50,-1 ), 0 );
	m_staticText34->Wrap( -1 );
	bSizer68->Add( m_staticText34, 0, wxALL, 5 );

	m_objectText = new wxComboBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY|wxCB_SORT );
	bSizer68->Add( m_objectText, 1, wxALL|wxEXPAND, 5 );


	bSizer67->Add( bSizer68, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer69;
	bSizer69 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText35 = new wxStaticText( this, wxID_ANY, wxT("Parent:"), wxDefaultPosition, wxSize( 50,-1 ), 0 );
	m_staticText35->Wrap( -1 );
	bSizer69->Add( m_staticText35, 0, wxALL, 5 );

	m_parentText = new wxComboBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY|wxCB_SORT );
	bSizer69->Add( m_parentText, 1, wxALL|wxEXPAND, 5 );


	bSizer67->Add( bSizer69, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer70;
	bSizer70 = new wxBoxSizer( wxHORIZONTAL );

	m_cancelBtn = new wxButton( this, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer70->Add( m_cancelBtn, 1, wxALL|wxEXPAND, 5 );

	m_reparentBtn = new wxButton( this, wxID_OK, wxT("Reparent"), wxDefaultPosition, wxDefaultSize, 0 );

	m_reparentBtn->SetDefault();
	bSizer70->Add( m_reparentBtn, 1, wxALL|wxEXPAND, 5 );


	bSizer67->Add( bSizer70, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer67 );
	this->Layout();

	this->Centre( wxBOTH );
}

LE3ReparentDialog::~LE3ReparentDialog()
{
}
