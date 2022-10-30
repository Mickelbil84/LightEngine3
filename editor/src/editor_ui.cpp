#include "editor_ui.h"

#include "icons/icon_none.xpm"
#include "icons/icon_new.xpm"
#include "icons/icon_open.xpm"
#include "icons/icon_save.xpm"
#include "icons/icon_saveas.xpm"
#include "icons/icon_undo.xpm"
#include "icons/icon_redo.xpm"
#include "icons/icon_gizmo_select.xpm"
#include "icons/icon_gizmo_move.xpm"
#include "icons/icon_gizmo_rotate.xpm"
#include "icons/icon_gizmo_scale.xpm"
#include "icons/icon_collision.xpm"
#include "icons/icon_bulletcollision.xpm"

LE3EditorUI::LE3EditorUI(wxWindow* parent) : LE3EditorWindow(parent), m_selectedType(LE3_SELECTED_NONE), selectCallback(this), refreshPropertiesCallback(this)
{
    m_auiToolBar4->SetToolBitmapSize(wxSize(24, 24));    
    m_newTool->SetBitmap({icon_new});
    m_loadTool->SetBitmap({icon_open});
    m_saveTool->SetBitmap({icon_save});
    m_saveAsTool->SetBitmap({icon_saveas});
    m_undoTool->SetBitmap({icon_undo});
    m_redoTool->SetBitmap({icon_redo});
    m_gizmoSelectTool->SetBitmap({icon_gizmo_select});
    m_gizmoMoveTool->SetBitmap({icon_gizmo_move});
    m_gizmoRotateTool->SetBitmap({icon_gizmo_rotate});
    m_gizmoScaleTool->SetBitmap({icon_gizmo_scale});
    m_collisionTool->SetBitmap({icon_collision});
    m_bulletCollisionTool->SetBitmap({icon_bulletcollision});

    m_auiToolBar4->Realize();


}

void LE3EditorUI::RefreshSceneGraph()
{
    this->m_sceneGraphMap.clear();
    this->m_sceneGraphTree->DeleteAllItems();
    this->m_sceneGraphTree->AppendColumn(wxT("Name"));
    this->RefreshSceneGraph(m_editor->scene.GetRoot().get(), m_sceneGraphTree->GetRootItem());
}

void LE3EditorUI::RefreshSceneGraph(LE3Object* node, wxTreeListItem treeItem)
{
    if (node->GetHiddenInSceneGraph())
        return;
    wxTreeListItem newItem = this->m_sceneGraphTree->AppendItem(treeItem, node->GetName().c_str());
    this->m_sceneGraphMap[newItem] = node;
    this->m_sceneGraphMapInverse[node] = newItem;
    this->m_sceneGraphTree->Expand(newItem);
    this->m_sceneGraphTree->SetColumnWidth(0, 300);
    for (auto child : node->GetChildren())
        this->RefreshSceneGraph(child, newItem);
}

void LE3EditorUI::RefreshAssets()
{
    this->m_treeListShaders->DeleteAllItems();
    this->m_treeListShaders->AppendColumn(wxT("Name"));
    for (const auto& [key, value] : m_editor->scene.assets.m_shaders)
        this->m_treeListShaders->AppendItem(m_treeListShaders->GetRootItem(), key.c_str());

    this->m_treeListMaterials->DeleteAllItems();
    this->m_treeListMaterials->AppendColumn(wxT("Name"));
    for (const auto& [key, value] : m_editor->scene.assets.m_materials)
        this->m_treeListMaterials->AppendItem(m_treeListMaterials->GetRootItem(), key.c_str());
    
    this->m_treeListTextures->DeleteAllItems();
    this->m_treeListTextures->AppendColumn(wxT("Name"));
    for (const auto& [key, value] : m_editor->scene.assets.m_textures)
        this->m_treeListTextures->AppendItem(m_treeListTextures->GetRootItem(), key.c_str());
    
    this->m_treeListMeshes->DeleteAllItems();
    this->m_treeListMeshes->AppendColumn(wxT("Name"));
    for (const auto& [key, value] : m_editor->scene.assets.m_meshes)
        this->m_treeListMeshes->AppendItem(m_treeListMeshes->GetRootItem(), key.c_str());
}

void LE3EditorUI::OnSelectShader( wxTreeListEvent& event )
{
    bool res = UpdateShaderPropertyGrid(m_propertyGrid, m_treeListShaders, event, m_editor->scene.assets);
    if (res)
    {
        m_selectedType = LE3_SELECTED_SHADER;
        m_selectedName = this->m_treeListShaders->GetItemText(event.GetItem());
    }
    else
    {
        m_selectedType = LE3_SELECTED_NONE;
        m_selectedName = std::string("");
    }
}
void LE3EditorUI::OnPropertyChangeShader(wxPropertyGridEvent& event)
{
    ShaderPropertyGridChanged(m_propertyGrid, m_treeListShaders, event, m_editor->scene.assets, m_selectedName);
    RefreshAssets();
}

void LE3EditorUI::OnSelectObjectInGraph( wxTreeListEvent& event )
{
    // Check if this is a deselect event
    wxString name = this->m_treeListShaders->GetItemText(event.GetItem());
    if (name.IsEmpty())
        return;

    LE3Object* obj = this->m_sceneGraphMap[event.GetItem()];
    m_editor->SetSelectedObject(obj);
    refreshPropertiesCallback.callback();
}

void LE3EditorUI::OnPropertyChange( wxPropertyGridEvent& event )
{
    switch(m_selectedType)
    {
    case LE3_SELECTED_SHADER:
        OnPropertyChangeShader(event);
        break;

    case LE3_SELECTED_OBJECT:
        ObjectPropertyGridChanged(m_editor->GetSelectedObject(), m_propertyGrid, event);
        m_editor->SetSelectedObject(m_editor->GetSelectedObject());
        RefreshSceneGraph();
        m_editor->scene.UpdateAssets();
        break;

    case LE3_SELECTED_NONE:
    default:
         event.Skip(); 
         break;
    }
}

void LE3EditorUI::OnMouseClick( wxMouseEvent& event )
{
}

void LE3EditorUI::RefreshPropertyGrid()
{
    if (m_editor->GetSelectedObject())
    {
        UpdateObjectPropertyGrid(m_editor->GetSelectedObject(), m_propertyGrid);
        m_selectedType = LE3_SELECTED_OBJECT;
    }
    else
    {
        m_propertyGrid->Clear();
        m_selectedType = LE3_SELECTED_NONE;
    }
}

void LE3EditorUI::RefreshPropertyGrid(wxTimerEvent& evt)
{
    this->RefreshPropertyGrid();
}

LE3EditorUI::LE3EditorUI_SelectCallback::LE3EditorUI_SelectCallback(LE3EditorUI* parent)
{
    this->parent = parent;
}

void LE3EditorUI::LE3EditorUI_SelectCallback::callback()
{
    if (parent->m_editor->GetHoveredObject())
    {
        parent->m_sceneGraphTree->Select(parent->m_sceneGraphMapInverse[parent->m_editor->GetHoveredObject()]);
    }
    else
    {
        parent->m_sceneGraphTree->UnselectAll();
    }
}

LE3EditorUI::LE3EditorUI_RefreshPropertiesCallback::LE3EditorUI_RefreshPropertiesCallback(LE3EditorUI* parent)
{
    this->parent = parent;
}

void LE3EditorUI::LE3EditorUI_RefreshPropertiesCallback::callback()
{
    parent->RefreshPropertyGrid();
}

void LE3EditorUI::OnCollisionToolToggle( wxCommandEvent& event )
{
    LE3VisualDebug::g_bDrawCollision = event.IsChecked();
}
void LE3EditorUI::OnBulletCollisionToolToggle( wxCommandEvent& event )
{
    LE3VisualDebug::g_bDrawBulletCollision = event.IsChecked();
}

void LE3EditorUI::OnNewScene( wxCommandEvent& event )
{
    m_editor->scene.Clear();
    m_editor->Init();
    m_editor->scenePath = "";
    
    RefreshAssets();
    RefreshSceneGraph();

    wxTopLevelWindow::SetTitle(LE3EDITOR_WINDOW_TITLE);
}
void LE3EditorUI::OnLoadScene( wxCommandEvent& event )
{
    wxFileDialog openFileDialog(this, _("Open LE3S file"), "", "", "LE3S files (*.json)|*.json", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    m_editor->bPauseEngine = true;
    if (openFileDialog.ShowModal() == wxID_CANCEL)
    {
        m_editor->bPauseEngine = false;
        return;
    }
    this->OnNewScene(event);
    m_editor->scenePath = openFileDialog.GetPath().ToStdString();
    LoadScene(m_editor->scene, m_editor->scenePath);
    m_editor->bPauseEngine = false;

    RefreshAssets();
    RefreshSceneGraph();
    
    wxTopLevelWindow::SetTitle(std::string(LE3EDITOR_WINDOW_TITLE) + std::string(" - ") + m_editor->scenePath);
}
void LE3EditorUI::OnSaveScene( wxCommandEvent& event )
{
    if (m_editor->scenePath == "")
    {
        this->OnSaveSceneAs(event);
        return;
    }

    SaveScene(m_editor->scene, m_editor->scenePath);

    wxMessageBox(wxT("Save successful."), wxT("Save Scene"), wxICON_INFORMATION);
}
void LE3EditorUI::OnSaveSceneAs( wxCommandEvent& event )
{
    wxFileDialog saveFileDialog(this, _("Save LE3S file"), "", "", "LE3S files (*.json)|*.json", wxFD_SAVE);

    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return;
    
    m_editor->scenePath = saveFileDialog.GetPath().ToStdString();
    SaveScene(m_editor->scene, m_editor->scenePath);

    wxTopLevelWindow::SetTitle(std::string(LE3EDITOR_WINDOW_TITLE) + std::string(" - ") + m_editor->scenePath);
}