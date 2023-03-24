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
#include "icons/icon_reparent.xpm"
#include "icons/icon_duplicate.xpm"

#include "icons/icon_newcube.xpm"
#include "icons/icon_newsphere.xpm"
#include "icons/icon_newcylinder.xpm"
#include "icons/icon_newcone.xpm"
#include "icons/icon_newtorus.xpm"
#include "icons/icon_newstaticmesh.xpm"
#include "icons/icon_newempty.xpm"

#include "icons/icon_addambientlight.xpm"
#include "icons/icon_adddirectionallight.xpm"
#include "icons/icon_addpointlight.xpm"
#include "icons/icon_addspotlight.xpm"

LE3EditorUI::LE3EditorUI(wxWindow* parent) : LE3EditorWindow(parent), m_selectedType(LE3_SELECTED_NONE), selectCallback(this), refreshPropertiesCallback(this)
{
    m_topToolbar->SetToolBitmapSize(wxSize(24, 24));    
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
    m_reparentTool->SetBitmap({icon_reparent});
    m_duplicateTool->SetBitmap({icon_duplicate});
    m_topToolbar->Realize();

    m_sideToolbar->SetToolBitmapSize(wxSize(24, 24));
    m_addCubeTool->SetBitmap({icon_newcube});
    m_addSphereTool->SetBitmap({icon_newsphere});
    m_addCylinderTool->SetBitmap({icon_newcylinder});
    m_addConeTool->SetBitmap({icon_newcone});
    m_addTorusTool->SetBitmap({icon_newtorus});
    m_addStaticMeshTool->SetBitmap({icon_newstaticmesh});
    m_addEmptyTool->SetBitmap({icon_newempty});

    m_addAmbientLightTool->SetBitmap({icon_addambientlight});
    m_addDirectionalLightTool->SetBitmap({icon_adddirectionallight});
    m_addPointLightTool->SetBitmap({icon_addpointlight});
    m_addSpotLightTool->SetBitmap({icon_addspotlight});

    m_sideToolbar->Realize();

}

void LE3EditorUI::RefreshSceneGraph()
{
    this->m_sceneGraphMap.clear();
    this->m_sceneGraphTree->ClearColumns();
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
    this->m_treeListShaders->ClearColumns();
    this->m_treeListShaders->DeleteAllItems();
    this->m_treeListShaders->AppendColumn(wxT("Name"));
    this->m_treeListShaders->SetColumnWidth(0, 300);
    for (const auto& [key, value] : m_editor->scene.assets.m_shadersPaths)
        this->m_treeListShaders->AppendItem(m_treeListShaders->GetRootItem(), key.c_str());

    this->m_treeListMaterials->ClearColumns();
    this->m_treeListMaterials->DeleteAllItems();
    this->m_treeListMaterials->AppendColumn(wxT("Name"));
    this->m_treeListMaterials->SetColumnWidth(0, 300);
    for (const auto& [key, value] : m_editor->scene.assets.m_materials)
        this->m_treeListMaterials->AppendItem(m_treeListMaterials->GetRootItem(), key.c_str());
    
    this->m_treeListTextures->ClearColumns();
    this->m_treeListTextures->DeleteAllItems();
    this->m_treeListTextures->AppendColumn(wxT("Name"));
    this->m_treeListTextures->SetColumnWidth(0, 300);
    for (const auto& [key, value] : m_editor->scene.assets.m_texturesPaths)
        this->m_treeListTextures->AppendItem(m_treeListTextures->GetRootItem(), key.c_str());

    this->m_treeListMeshes->ClearColumns();
    this->m_treeListMeshes->DeleteAllItems();
    this->m_treeListMeshes->AppendColumn(wxT("Name"));
    this->m_treeListMeshes->SetColumnWidth(0, 300);
    for (const auto& [key, value] : m_editor->scene.assets.m_meshesPaths)
    {
        if (value.path != std::string("") && value.path[0] == gPrimitivePathPrefix)
            continue;
        this->m_treeListMeshes->AppendItem(m_treeListMeshes->GetRootItem(), key.c_str());
    }
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

void LE3EditorUI::OnSelectMaterial( wxTreeListEvent& event )
{
    bool res = UpdateMaterialPropertyGrid(m_propertyGrid, m_treeListMaterials, event, m_editor->scene.assets);
    if (res)
    {
        m_selectedType = LE3_SELECTED_MATERIAL;
        m_selectedName = this->m_treeListMaterials->GetItemText(event.GetItem());
    }
    else
    {
        m_selectedType = LE3_SELECTED_NONE;
        m_selectedName = std::string("");
    }
}
void LE3EditorUI::OnSelectTexture( wxTreeListEvent& event )
{
    bool res = UpdateTexturePropertyGrid(m_propertyGrid, m_treeListTextures, event, m_editor->scene.assets);
    if (res)
    {
        m_selectedType = LE3_SELECTED_TEXTURE;
        m_selectedName = this->m_treeListTextures->GetItemText(event.GetItem());
    }
    else
    {
        m_selectedType = LE3_SELECTED_NONE;
        m_selectedName = std::string("");
    }
}
void LE3EditorUI::OnSelectMesh( wxTreeListEvent& event )
{
    bool res = UpdateMeshPropertyGrid(m_propertyGrid, m_treeListMeshes, event, m_editor->scene.assets);
    if (res)
    {
        m_selectedType = LE3_SELECTED_MESH;
        m_selectedName = this->m_treeListMeshes->GetItemText(event.GetItem());
    }
    else
    {
        m_selectedType = LE3_SELECTED_NONE;
        m_selectedName = std::string("");
    }
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
    // A bit of voodoo: to make sure everything is safe, break the rendering loop before breaking stuff
    m_editor->bPauseEngine = true;
    wxMilliSleep(10);
    
    switch(m_selectedType)
    {
    case LE3_SELECTED_SHADER:
        // OnPropertyChangeShader(event);
        ShaderPropertyGridChanged(m_propertyGrid, m_treeListShaders, event, m_editor->scene.assets, m_editor->scene, m_selectedName);
        if (event.GetPropertyName() == wxT("Name"))
            RefreshAssets();
        break;
    
    case LE3_SELECTED_MATERIAL:
        MaterialPropertyGridChanged(m_propertyGrid, m_treeListMaterials, event, m_editor->scene.assets, m_editor->scene, m_selectedName);
        if (event.GetPropertyName() == wxT("Name"))
            RefreshAssets();
        break;

    case LE3_SELECTED_TEXTURE:
        TexturePropertyGridChanged(m_propertyGrid, m_treeListTextures, event, m_editor->scene.assets, m_editor->scene, m_selectedName);
        if (event.GetPropertyName() == wxT("Name"))
            RefreshAssets();
        break;

    case LE3_SELECTED_MESH:
        MeshPropertyGridChanged(m_propertyGrid, m_treeListMeshes, event, m_editor->scene.assets, m_editor->scene, m_selectedName);
        if (event.GetPropertyName() == wxT("Name"))
            RefreshAssets();
        break;

    case LE3_SELECTED_OBJECT:
        ObjectPropertyGridChanged(m_editor->GetSelectedObject(), m_propertyGrid, event, m_editor->scene.assets, m_editor->scene.lightManager);
        m_editor->SetSelectedObject(m_editor->GetSelectedObject());
        RefreshSceneGraph();
        m_editor->scene.UpdateAssets();
        break;

    case LE3_SELECTED_NONE:
    default:
         event.Skip(); 
         break;
    }
    m_editor->bPauseEngine = false;
}

void LE3EditorUI::RefreshPropertyGrid()
{
    if (m_editor->GetSelectedObject())
    {
        UpdateObjectPropertyGrid(m_editor->GetSelectedObject(), m_propertyGrid, m_editor->scene.assets);
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

    m_editor->scene.lightManager.RegisterLightCollisions(m_editor->scene.GetPhysics());
    m_editor->scene.AddLightSprites();
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

void LE3EditorUI::OnNewShader( wxCommandEvent& event )
{
    LE3NewShaderDialog dialog(this);
    m_editor->bPauseUpdate = true;
    if (dialog.ShowModal() == wxID_OK)
    {
        std::string name = GetValidShaderName(dialog.m_nameText->GetValue().ToStdString());
        std::string vertexShaderPath = dialog.m_vertexShaderText->GetValue().ToStdString();
        std::string fragmentShaderPath = dialog.m_fragmentShaderText->GetValue().ToStdString();
        
        m_editor->scene.assets.AddShaderPath(name, vertexShaderPath, fragmentShaderPath);
        m_editor->scene.assets.GetShader(name);

        RefreshAssets();
    }
    m_editor->bPauseUpdate = false;
}
void LE3EditorUI::OnDeleteShader( wxCommandEvent& event )
{
    if (m_selectedType != LE3_SELECTED_SHADER)
        return;
    
    int answer = wxMessageBox(
        std::string("Are you sure you want to delete the shader [") + m_selectedName + std::string("]?"),
        "Delete Shader",
        wxYES_NO | wxCANCEL, this);
    if (answer == wxYES)
    {
        // A bit of voodoo: to make sure everything is safe, break the rendering loop before breaking stuff
        m_editor->bPauseEngine = true;
        wxMilliSleep(10);
        
        UpdateShaderBookkeeping(m_editor->scene.assets, m_selectedName);
        
        m_editor->scene.assets.m_shaders.extract(m_selectedName);
        m_editor->scene.assets.m_shadersPaths.extract(m_selectedName);

        RefreshAssets();
        m_editor->bPauseEngine = false;
    }
}
void LE3EditorUI::OnNewMaterial( wxCommandEvent& event )
{
    LE3NewMaterialDialog dialog(this);

    // Populate materials
    for (auto [key, value] : m_editor->scene.assets.m_shadersPaths)
        dialog.m_shaderText->Append(key);
    dialog.m_shaderText->SetValue(DEFAULT_SHADER_NAME);

    m_editor->bPauseUpdate = true;
    if (dialog.ShowModal() == wxID_OK)
    {
        std::string name = GetValidMaterialName(dialog.m_nameText->GetValue().ToStdString());
        std::string shaderName = dialog.m_shaderText->GetValue().ToStdString();
        
        m_editor->scene.assets.CreateMaterial(name, shaderName);

        RefreshAssets();
    }
    m_editor->bPauseUpdate = false;
}
void LE3EditorUI::OnDeleteMaterial( wxCommandEvent& event )
{
    if (m_selectedType != LE3_SELECTED_MATERIAL)
        return;
    
    int answer = wxMessageBox(
        std::string("Are you sure you want to delete the material [") + m_selectedName + std::string("]?"),
        "Delete Material",
        wxYES_NO | wxCANCEL, this);
    if (answer == wxYES)
    {
        // A bit of voodoo: to make sure everything is safe, break the rendering loop before breaking stuff
        m_editor->bPauseEngine = true;
        wxMilliSleep(10);
        
        UpdateMaterialBookkeeping(m_editor->scene, m_selectedName);
        
        m_editor->scene.assets.m_materials.erase(m_selectedName);

        RefreshAssets();
        m_editor->bPauseEngine = false;
    }
}
void LE3EditorUI::OnNewTexture( wxCommandEvent& event )
{
    LE3NewTextureDialog dialog(this);
    m_editor->bPauseUpdate = true;
    if (dialog.ShowModal() == wxID_OK)
    {
        std::string name = GetValidTextureName(dialog.m_nameText->GetValue().ToStdString());
        std::string path = dialog.m_pathText->GetValue().ToStdString();
        
        m_editor->scene.assets.AddTexturePath(name, path);
        m_editor->scene.assets.GetTexture(name);

        RefreshAssets();
    }
    m_editor->bPauseUpdate = false;
}
void LE3EditorUI::OnDeleteTexture( wxCommandEvent& event )
{
    if (m_selectedType != LE3_SELECTED_TEXTURE)
        return;
    
    int answer = wxMessageBox(
        std::string("Are you sure you want to delete the texture [") + m_selectedName + std::string("]?"),
        "Delete Texture",
        wxYES_NO | wxCANCEL, this);
    if (answer == wxYES)
    {
        // A bit of voodoo: to make sure everything is safe, break the rendering loop before breaking stuff
        m_editor->bPauseEngine = true;
        wxMilliSleep(10);
        
        UpdateTextureBookkeeping(m_editor->scene.assets, m_selectedName);
        
        m_editor->scene.assets.m_texturesPaths.erase(m_selectedName);
        m_editor->scene.assets.m_textures.erase(m_selectedName);

        RefreshAssets();
        m_editor->bPauseEngine = false;
    }
}
void LE3EditorUI::OnNewMesh( wxCommandEvent& event )
{
    LE3NewMeshDialog dialog(this);
    m_editor->bPauseUpdate = true;
    if (dialog.ShowModal() == wxID_OK)
    {
        std::string name = GetValidMeshName(dialog.m_nameText->GetValue().ToStdString());
        std::string path = dialog.m_pathText->GetValue().ToStdString();
        
        m_editor->scene.assets.AddMeshPath(name, path);
        m_editor->scene.assets.GetMesh(name);

        RefreshAssets();
    }
    m_editor->bPauseUpdate = false;
}
void LE3EditorUI::OnDeleteMesh( wxCommandEvent& event )
{
    if (m_selectedType != LE3_SELECTED_MESH)
        return;
    
    int answer = wxMessageBox(
        std::string("Are you sure you want to delete the mesh [") + m_selectedName + std::string("]?"),
        "Delete Mesh",
        wxYES_NO | wxCANCEL, this);
    if (answer == wxYES)
    {
        // A bit of voodoo: to make sure everything is safe, break the rendering loop before breaking stuff
        m_editor->bPauseEngine = true;
        wxMilliSleep(10);
        
        UpdateMeshBookkeeping(m_editor->scene, m_selectedName);
        
        m_editor->scene.assets.m_meshesPaths.erase(m_selectedName);
        m_editor->scene.assets.m_meshes.erase(m_selectedName);

        RefreshAssets();
        m_editor->bPauseEngine = false;
    }
}

std::string LE3EditorUI::GetObjectNumberPrefix(std::string objectName)
{
    size_t idx = objectName.find_last_not_of("1234567890");
    return objectName.substr(0, ++idx);
}
int LE3EditorUI::GetObjectNumberSuffix(std::string objectName)
{
    size_t idx = objectName.find_last_not_of("1234567890");
    std::string res = objectName.substr(++idx);
    if (res == std::string(""))
        return 0;
    return std::atoi(res.c_str());
}

std::string LE3EditorUI::GetValidShaderName(std::string name)
{
    if (m_editor->scene.assets.m_shaders.find(name) == m_editor->scene.assets.m_shaders.end())
        return name;
    
    std::string prefix = GetObjectNumberPrefix(name);
    int counter = GetObjectNumberSuffix(name);

    while (m_editor->scene.assets.m_shaders.find(prefix + std::to_string(++counter)) != m_editor->scene.assets.m_shaders.end());

    return prefix + std::to_string(counter);
}
std::string LE3EditorUI::GetValidMaterialName(std::string name)
{
    if (m_editor->scene.assets.m_materials.find(name) == m_editor->scene.assets.m_materials.end())
        return name;
    
    std::string prefix = GetObjectNumberPrefix(name);
    int counter = GetObjectNumberSuffix(name);

    while (m_editor->scene.assets.m_materials.find(prefix + std::to_string(++counter)) != m_editor->scene.assets.m_materials.end());

    return prefix + std::to_string(counter);
}
std::string LE3EditorUI::GetValidTextureName(std::string name)
{
    if (m_editor->scene.assets.m_textures.find(name) == m_editor->scene.assets.m_textures.end())
        return name;
    
    std::string prefix = GetObjectNumberPrefix(name);
    int counter = GetObjectNumberSuffix(name);

    while (m_editor->scene.assets.m_textures.find(prefix + std::to_string(++counter)) != m_editor->scene.assets.m_textures.end());

    return prefix + std::to_string(counter);
}
std::string LE3EditorUI::GetValidMeshName(std::string name)
{
    if (m_editor->scene.assets.m_meshes.find(name) == m_editor->scene.assets.m_meshes.end())
        return name;
    
    std::string prefix = GetObjectNumberPrefix(name);
    int counter = GetObjectNumberSuffix(name);

    while (m_editor->scene.assets.m_meshes.find(prefix + std::to_string(++counter)) != m_editor->scene.assets.m_meshes.end());

    return prefix + std::to_string(counter);
}
// std::string LE3EditorUI::GetValidObjectName(std::string objectName)
// {
//     if (m_editor->scene.objectPool.find(objectName) == m_editor->scene.objectPool.end())
//         return objectName;
    
//     std::string prefix = GetObjectNumberPrefix(objectName);
//     int counter = GetObjectNumberSuffix(objectName);

//     while (m_editor->scene.objectPool.find(prefix + std::to_string(++counter)) != m_editor->scene.objectPool.end());

//     return prefix + std::to_string(counter);
// }


void LE3EditorUI::OnAddCube( wxCommandEvent& event )
{
    LE3AddCubeDialog dialog(this);

    // Populate materials
    for (auto [key, value] : m_editor->scene.assets.m_materials)
        dialog.m_materialText->Append(key);
    dialog.m_materialText->SetValue(DEFAULT_MATERIAL_NAME);

    m_editor->bPauseUpdate = true;
    if (dialog.ShowModal() == wxID_OK)
    {
        std::string name = m_editor->scene.GetValidObjectName(dialog.m_nameText->GetValue().ToStdString());
        std::string materialName = dialog.m_materialText->GetValue().ToStdString();
        std::string width = dialog.m_widthText->GetValue().ToStdString();
        std::string height = dialog.m_heightText->GetValue().ToStdString();
        std::string depth = dialog.m_depthText->GetValue().ToStdString();

        std::string del(1, gPrimitivePathDelimiter);
        std::string zero("0");

        std::string meshName = std::string(1, gPrimitivePathPrefix) + std::string(gTokenBox) + del +
                zero + del + zero + del + zero + del +
                width + del +
                height + del +
                depth + del;
        m_editor->scene.assets.AddMeshPath(name, meshName);
        m_editor->scene.AddStaticMesh(name, name, materialName);

        RefreshAssets();
        RefreshSceneGraph();
    }
    m_editor->bPauseUpdate = false;
}
void LE3EditorUI::OnAddCylinder( wxCommandEvent& event )
{
    LE3AddCylinderDialog dialog(this);

    // Populate materials
    for (auto [key, value] : m_editor->scene.assets.m_materials)
        dialog.m_materialText->Append(key);
    dialog.m_materialText->SetValue(DEFAULT_MATERIAL_NAME);

    m_editor->bPauseUpdate = true;
    if (dialog.ShowModal() == wxID_OK)
    {
        std::string name = m_editor->scene.GetValidObjectName(dialog.m_nameText->GetValue().ToStdString());
        std::string materialName = dialog.m_materialText->GetValue().ToStdString();
        std::string radius = dialog.m_radiusText->GetValue().ToStdString();
        std::string height = dialog.m_heightText->GetValue().ToStdString();
        std::string resolution = dialog.m_resolutionText->GetValue().ToStdString();
        std::string withCpas = std::to_string((GLushort)dialog.m_capsBool->GetValue());

        std::string del(1, gPrimitivePathDelimiter);
        std::string zero("0");

        std::string meshName = std::string(1, gPrimitivePathPrefix) + std::string(gTokenCylinder) + del +
                zero + del + zero + del + zero + del +
                radius + del +
                height + del +
                resolution + del +
                withCpas + del;
        m_editor->scene.assets.AddMeshPath(name, meshName);
        m_editor->scene.AddStaticMesh(name, name, materialName);

        RefreshAssets();
        RefreshSceneGraph();
    }
    m_editor->bPauseUpdate = false;
}
void LE3EditorUI::OnAddCone( wxCommandEvent& event )
{
    LE3AddConeDialog dialog(this);

    // Populate materials
    for (auto [key, value] : m_editor->scene.assets.m_materials)
        dialog.m_materialText->Append(key);
    dialog.m_materialText->SetValue(DEFAULT_MATERIAL_NAME);

    m_editor->bPauseUpdate = true;
    if (dialog.ShowModal() == wxID_OK)
    {
        std::string name = m_editor->scene.GetValidObjectName(dialog.m_nameText->GetValue().ToStdString());
        std::string materialName = dialog.m_materialText->GetValue().ToStdString();
        std::string radius = dialog.m_radiusText->GetValue().ToStdString();
        std::string height = dialog.m_heightText->GetValue().ToStdString();
        std::string resolution = dialog.m_resolutionText->GetValue().ToStdString();

        std::string del(1, gPrimitivePathDelimiter);
        std::string zero("0");

        std::string meshName = std::string(1, gPrimitivePathPrefix) + std::string(gTokenCone) + del +
                zero + del + zero + del + zero + del +
                radius + del +
                height + del +
                resolution + del;
        m_editor->scene.assets.AddMeshPath(name, meshName);
        m_editor->scene.AddStaticMesh(name, name, materialName);

        RefreshAssets();
        RefreshSceneGraph();
    }
    m_editor->bPauseUpdate = false;
}
void LE3EditorUI::OnAddTorus( wxCommandEvent& event )
{
    LE3AddTorusDialog dialog(this);

    // Populate materials
    for (auto [key, value] : m_editor->scene.assets.m_materials)
        dialog.m_materialText->Append(key);
    dialog.m_materialText->SetValue(DEFAULT_MATERIAL_NAME);

    m_editor->bPauseUpdate = true;
    if (dialog.ShowModal() == wxID_OK)
    {
        std::string name = m_editor->scene.GetValidObjectName(dialog.m_nameText->GetValue().ToStdString());
        std::string materialName = dialog.m_materialText->GetValue().ToStdString();
        std::string majorRadius = dialog.m_majorRadiusText->GetValue().ToStdString();
        std::string minorRadius = dialog.m_minorRadiusText->GetValue().ToStdString();
        std::string resolution = dialog.m_resolutionText->GetValue().ToStdString();

        std::string del(1, gPrimitivePathDelimiter);
        std::string zero("0");

        std::string meshName = std::string(1, gPrimitivePathPrefix) + std::string(gTokenTorus) + del +
                zero + del + zero + del + zero + del +
                majorRadius + del +
                minorRadius + del +
                resolution + del;
        m_editor->scene.assets.AddMeshPath(name, meshName);
        m_editor->scene.AddStaticMesh(name, name, materialName);

        RefreshAssets();
        RefreshSceneGraph();
    }
    m_editor->bPauseUpdate = false;
}
void LE3EditorUI::OnAddSphere( wxCommandEvent& event )
{
    LE3AddSphereDialog dialog(this);

    // Populate materials
    for (auto [key, value] : m_editor->scene.assets.m_materials)
        dialog.m_materialText->Append(key);
    dialog.m_materialText->SetValue(DEFAULT_MATERIAL_NAME);

    m_editor->bPauseUpdate = true;
    if (dialog.ShowModal() == wxID_OK)
    {
        std::string name = m_editor->scene.GetValidObjectName(dialog.m_nameText->GetValue().ToStdString());
        std::string materialName = dialog.m_materialText->GetValue().ToStdString();
        std::string radius = dialog.m_radiusText->GetValue().ToStdString();
        std::string resolution = dialog.m_resolutionText->GetValue().ToStdString();

        std::string del(1, gPrimitivePathDelimiter);
        std::string zero("0");

        std::string meshName = std::string(1, gPrimitivePathPrefix) + std::string(gTokenSphere) + del +
                zero + del + zero + del + zero + del +
                radius + del +
                resolution + del;
        m_editor->scene.assets.AddMeshPath(name, meshName);
        m_editor->scene.AddStaticMesh(name, name, materialName);

        RefreshAssets();
        RefreshSceneGraph();
    }
    m_editor->bPauseUpdate = false;
}
void LE3EditorUI::OnAddStaticMesh( wxCommandEvent& event )
{
    LE3AddStaticMeshDialog dialog(this);

    // Populate static meshes
    for (auto [key, value] : m_editor->scene.assets.m_meshesPaths)
    {
        if (value.path != std::string("") && value.path[0] == gPrimitivePathPrefix)
            continue;
        dialog.m_meshCombo->Append(key);
    }

    // Populate materials
    for (auto [key, value] : m_editor->scene.assets.m_materials)
        dialog.m_materialText->Append(key);
    dialog.m_materialText->SetValue(DEFAULT_MATERIAL_NAME);

    m_editor->bPauseUpdate = true;
    if (dialog.ShowModal() == wxID_OK)
    {
        std::string name = m_editor->scene.GetValidObjectName(dialog.m_nameText->GetValue().ToStdString());
        std::string materialName = dialog.m_materialText->GetValue().ToStdString();
        std::string meshName = dialog.m_meshCombo->GetValue().ToStdString();

        m_editor->scene.AddStaticMesh(name, meshName, materialName);

        RefreshAssets();
        RefreshSceneGraph();
    }
    m_editor->bPauseUpdate = false;
}
void LE3EditorUI::OnAddEmpty( wxCommandEvent& event )
{
    LE3AddEmptyDialog dialog(this);
    m_editor->bPauseUpdate = true;
    if (dialog.ShowModal() == wxID_OK)
    {
        std::string name = m_editor->scene.GetValidObjectName(dialog.m_nameText->GetValue().ToStdString());

        m_editor->scene.AddObject(name);

        RefreshAssets();
        RefreshSceneGraph();
    }
    m_editor->bPauseUpdate = false;
}

void LE3EditorUI::OnReparent( wxCommandEvent& event )
{
    LE3ReparentDialog dialog(this);

    // Populate objects and parents
    dialog.m_parentText->Append("__Root__");
    for (auto [key, value] : m_editor->scene.objectPool)
    {
        dialog.m_objectText->Append(key);
        dialog.m_parentText->Append(key);
    }
    dialog.m_objectText->SetValue("");
    if (m_editor->GetSelectedObject())
        dialog.m_objectText->SetValue(m_editor->GetSelectedObject()->GetName());
    dialog.m_parentText->SetValue("");

    m_editor->bPauseUpdate = true;
    if (dialog.ShowModal() == wxID_OK)
    {
        std::string name = dialog.m_objectText->GetValue().ToStdString();
        std::string parent = dialog.m_parentText->GetValue().ToStdString();
        if (parent == std::string("__Root__"))
            parent = std::string("");

        if (name != parent)
            m_editor->scene.Reparent(name, parent);

        RefreshAssets();
        RefreshSceneGraph();
    }
    m_editor->bPauseUpdate = false;
}

void LE3EditorUI::OnDuplicate( wxCommandEvent& event )
{
    LE3Object* selectedObject = m_editor->GetSelectedObject();
    if (!selectedObject)
        return;

    m_editor->bPauseUpdate = true;
    std::string parentName = selectedObject->GetParent()->GetName();
    if (selectedObject->GetParent()->GetName() == "Root")
        parentName = "";
    LE3Object* newObj = m_editor->scene.DuplicateObject(
        m_editor->scene.GetObject(selectedObject->GetName()),
        parentName
    ).get();
    m_editor->SetSelectedObject(newObj);


    RefreshAssets();
    RefreshSceneGraph();
    RefreshPropertyGrid();
    m_editor->scene.UpdateLightManager();
    m_editor->scene.AddLightSprites();
    m_editor->scene.lightManager.RegisterLightCollisions(m_editor->scene.GetPhysics());

    m_editor->bPauseUpdate = false;
}

LE3Object* LE3EditorUI::Duplicate(LE3Object* obj, std::string parentName) 
{
    return nullptr;
    // std::string newName = GetValidObjectName(obj->GetName());

    // // Try casting and creating all types of objects
    // // If we cannot cast, then the object is just the base class
    // bool bBaseObject = true; 

    // LE3Object* newObj = nullptr;
    
    // LE3StaticMesh* staticMesh = dynamic_cast<LE3StaticMesh*>(obj);
    // if (staticMesh) 
    // {
    //     m_editor->scene.AddStaticMesh(newName, staticMesh->meshName, staticMesh->materialName, staticMesh->GetScale(), staticMesh->m_bHasCollision, parentName);
    //     bBaseObject = false;
    // }

    // if (bBaseObject) 
    // {
    //     m_editor->scene.AddObject(newName, parentName);
    // }

    // newObj = m_editor->scene.GetObject(newName).get();
    // if (newObj)
    // {
    //     // Copy transformations
    //     newObj->SetPosition(obj->GetPosition());
    //     newObj->SetRotation(obj->GetRotation());
    //     newObj->SetScale(obj->GetScale());
    //     newObj->SetHiddenInSceneGraph(obj->GetHiddenInSceneGraph());
    //     newObj->SetHidden(obj->GetHidden());

    //     for (auto child : obj->GetChildren())
    //         Duplicate(child, newName);
    // }

    // return newObj;
}

void LE3EditorUI::OnGizmoSelect( wxCommandEvent& event )
{
    m_editor->m_editorState.gizmoMode = LE3EditorGizmoModes::LE3EDITOR_GIZMO_SELECT;
}
void LE3EditorUI::OnGizmoMove( wxCommandEvent& event )
{
    m_editor->m_editorState.gizmoMode = LE3EditorGizmoModes::LE3EDITOR_GIZMO_MOVE;
}
void LE3EditorUI::OnGizmoRotate( wxCommandEvent& event )
{
    m_editor->m_editorState.gizmoMode = LE3EditorGizmoModes::LE3EDITOR_GIZMO_ROTATE;
}
void LE3EditorUI::OnGizmoScale( wxCommandEvent& event )
{
    m_editor->m_editorState.gizmoMode = LE3EditorGizmoModes::LE3EDITOR_GIZMO_SCALE;
}

void LE3EditorUI::OnAddAmbientLight( wxCommandEvent& event )
{
    if (!m_editor->scene.lightManager.GetAmbientLight())
        m_editor->scene.AddAmbientLight();
    else
        wxMessageBox( wxT("Only one ambient light is allowed per scene."), wxT("Add Ambient Light"), wxICON_INFORMATION);
    m_editor->scene.lightManager.RegisterLightCollisions(m_editor->scene.GetPhysics());
    m_editor->scene.AddLightSprites();
    RefreshSceneGraph();
}
void LE3EditorUI::OnAddDirectionalLight( wxCommandEvent& event )
{
    m_editor->scene.AddDirectionalLight(m_editor->scene.GetValidObjectName("directional_light"));
    m_editor->scene.lightManager.RegisterLightCollisions(m_editor->scene.GetPhysics());
    m_editor->scene.AddLightSprites();
    RefreshSceneGraph();
}
void LE3EditorUI::OnAddPointLight( wxCommandEvent& event )
{
    m_editor->scene.AddPointLight(m_editor->scene.GetValidObjectName("point_light"));
    m_editor->scene.lightManager.RegisterLightCollisions(m_editor->scene.GetPhysics());
    m_editor->scene.AddLightSprites();
    RefreshSceneGraph();
}
void LE3EditorUI::OnAddSpotLight( wxCommandEvent& event )
{
    m_editor->scene.AddSpotLight(m_editor->scene.GetValidObjectName("spot_light"));
    m_editor->scene.lightManager.RegisterLightCollisions(m_editor->scene.GetPhysics());
    m_editor->scene.AddLightSprites();
    RefreshSceneGraph();
}