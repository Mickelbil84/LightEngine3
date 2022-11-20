#include "editor_asset_properties.h"

bool UpdateShaderPropertyGrid(wxPropertyGrid* pg, wxTreeListCtrl* treeList, wxTreeListEvent& event, LE3AssetManager& assets)
{
    pg->Clear();
    wxString name = treeList->GetItemText(event.GetItem());

    if (name.IsEmpty())
        return false;
    
    pg->Append(new wxStringProperty(wxT("Name"), wxPG_LABEL, name));
    pg->Append(new wxStringProperty(wxT("Vertex Shader Path"), wxPG_LABEL, assets.m_shaders[name.ToStdString()].m_vertexShaderPath));
    pg->Append(new wxStringProperty(wxT("Fragment Shader Path"), wxPG_LABEL, assets.m_shaders[name.ToStdString()].m_fragmentShaderPath));

    return true;
}
void ShaderPropertyGridChanged(wxPropertyGrid* pg, wxTreeListCtrl* treeList, wxPropertyGridEvent& event, LE3AssetManager& assets, std::string selectedName)
{
    if (event.GetPropertyName() == wxT("Name"))
    {
        std::string newName = event.GetPropertyValue().GetString().ToStdString();
        std::string vertexShaderPath = assets.m_shaders[selectedName].m_vertexShaderPath;
        std::string fragmentShaderPath = assets.m_shaders[selectedName].m_fragmentShaderPath;

        assets.m_shadersPaths.erase(selectedName);
        assets.AddShaderPath(newName, vertexShaderPath, fragmentShaderPath);
        
        UpdateShaderBookkeeping(assets, selectedName, newName);

        assets.m_shaders.erase(selectedName);
    }
    else if (event.GetPropertyName() == wxT("Vertex Shader Path"))
    {
        LE3Shader* shader = assets.GetShader(selectedName);
        shader->m_vertexShaderPath = event.GetPropertyValue().GetString().ToStdString();
        assets.m_shadersPaths[selectedName].vertexShaderPath = event.GetPropertyValue().GetString().ToStdString();
        wxMessageBox(wxT("Please reload the scene to recompile shaders."), wxT("Update Shaders"), wxICON_INFORMATION);
    }
    else if (event.GetPropertyName() == wxT("Fragment Shader Path"))
    {
        LE3Shader* shader = assets.GetShader(selectedName);
        shader->m_fragmentShaderPath = event.GetPropertyValue().GetString().ToStdString();
        assets.m_shadersPaths[selectedName].fragmentShaderPath = event.GetPropertyValue().GetString().ToStdString();
        wxMessageBox(wxT("Please reload the scene to recompile shaders."), wxT("Update Shaders"), wxICON_INFORMATION);
    }
}

bool UpdateMaterialPropertyGrid(wxPropertyGrid* pg, wxTreeListCtrl* treeList, wxTreeListEvent& event, LE3AssetManager& assets)
{
    pg->Clear();
    wxString name = treeList->GetItemText(event.GetItem());

    if (name.IsEmpty())
        return false;

    pg->Append(new wxStringProperty(wxT("Name"), wxPG_LABEL, name));
    pg->Append(new wxStringProperty(wxT("Shader Name"), wxPG_LABEL, assets.m_materials[name.ToStdString()].shaderName));

    pg->Append(new wxPropertyCategory(wxT("Diffuse")));
    // pg->Append(new wxColourProperty(wxT("Diffuse Color"), wxPG_LABEL, 
    //     wxColour(
    //         assets.m_materials[name.ToStdString()].diffuseColor.r,
    //         assets.m_materials[name.ToStdString()].diffuseColor.g,
    //         assets.m_materials[name.ToStdString()].diffuseColor.b
    // )));
    pg->Append(new wxFloatProperty(wxT("Diffuse R"), wxPG_LABEL, assets.m_materials[name.ToStdString()].diffuseColor.r));
    pg->Append(new wxFloatProperty(wxT("Diffuse G"), wxPG_LABEL, assets.m_materials[name.ToStdString()].diffuseColor.g));
    pg->Append(new wxFloatProperty(wxT("Diffuse B"), wxPG_LABEL, assets.m_materials[name.ToStdString()].diffuseColor.b));
    pg->Append(new wxStringProperty(wxT("Diffuse Texture"), wxPG_LABEL, assets.m_materials[name.ToStdString()].diffuseTextureName));
    pg->Append(new wxBoolProperty(wxT("Use Diffuse Texture"), wxPG_LABEL, assets.m_materials[name.ToStdString()].bUseDiffuseTexture));
    pg->Append(new wxFloatProperty(wxT("Tiling X"), wxPG_LABEL, assets.m_materials[name.ToStdString()].tilingX));
    pg->Append(new wxFloatProperty(wxT("Tiling Y"), wxPG_LABEL, assets.m_materials[name.ToStdString()].tilingY));

    return true;
}
void MaterialPropertyGridChanged(wxPropertyGrid* pg, wxTreeListCtrl* treeList, wxPropertyGridEvent& event, LE3AssetManager& assets, std::string selectedName)
{
    LE3Material* material = assets.GetMaterial(selectedName);

    if (event.GetPropertyName() == wxT("Name"))
    {
        std::string newName = event.GetPropertyValue().GetString().ToStdString();
        auto nh = assets.m_materials.extract(selectedName);
        nh.key() = newName;
        assets.m_materials.insert(std::move(nh));
    }
    else if (event.GetPropertyName() == wxT("Shader Name"))
    {
        material->shaderName = event.GetPropertyValue().GetString().ToStdString();
    }
    // else if (event.GetPropertyName() == wxT("Diffuse Color"))
    // {
    //     wxVariant value = event.GetPropertyValue();
    //     wxColour color;
    //     color << value;
    //     material->diffuseColor.r = color.Red();
    //     material->diffuseColor.g = color.Green();
    //     material->diffuseColor.b = color.Blue();
    // }
    else if (event.GetPropertyName() == wxT("Diffuse R"))
    {
        material->diffuseColor.r = event.GetPropertyValue().GetDouble();
    }
    else if (event.GetPropertyName() == wxT("Diffuse G"))
    {
        material->diffuseColor.g = event.GetPropertyValue().GetDouble();
    }
    else if (event.GetPropertyName() == wxT("Diffuse B"))
    {
        material->diffuseColor.b = event.GetPropertyValue().GetDouble();
    }
    else if (event.GetPropertyName() == wxT("Diffuse Texture"))
    {
        material->diffuseTextureName = event.GetPropertyValue().GetString().ToStdString();
    }
    else if (event.GetPropertyName() == wxT("Use Diffuse Texture"))
    {
        material->bUseDiffuseTexture = event.GetPropertyValue().GetBool();
    }
    else if (event.GetPropertyName() == wxT("Tiling X"))
    {
        material->tilingX = event.GetPropertyValue().GetDouble();
    }
    else if (event.GetPropertyName() == wxT("Tiling Y"))
    {
        material->tilingY = event.GetPropertyValue().GetDouble();
    }


    // Refresh material
    material->SetShader(assets.GetShader(material->shaderName));
    material->SetDiffuseTexture(assets.GetTexture(material->diffuseTextureName));
}

bool UpdateTexturePropertyGrid(wxPropertyGrid* pg, wxTreeListCtrl* treeList, wxTreeListEvent& event, LE3AssetManager& assets)
{
    pg->Clear();
    wxString name = treeList->GetItemText(event.GetItem());

    if (name.IsEmpty())
        return false;
    
    pg->Append(new wxStringProperty(wxT("Name"), wxPG_LABEL, name));
    pg->Append(new wxStringProperty(wxT("Path"), wxPG_LABEL, assets.m_texturesPaths[name.ToStdString()].path));

    return true;
}
void TexturePropertyGridChanged(wxPropertyGrid* pg, wxTreeListCtrl* treeList, wxPropertyGridEvent& event, LE3AssetManager& assets, std::string selectedName)
{
    if (event.GetPropertyName() == wxT("Name"))
    {
        std::string newName = event.GetPropertyValue().GetString().ToStdString();
        std::string path = assets.m_texturesPaths[selectedName].path;

        assets.m_texturesPaths.erase(selectedName);
        assets.AddTexturePath(newName, path);
        
        UpdateTextureBookkeeping(assets, selectedName, newName);

        assets.m_textures.erase(selectedName);
    }
    else if (event.GetPropertyName() == wxT("Path"))
    {
        assets.m_texturesPaths[selectedName].path = event.GetPropertyValue().GetString().ToStdString();
        assets.m_textures[selectedName].Delete();
        assets.m_textures[selectedName].Load(assets.m_texturesPaths[selectedName].path);
    }
}

bool UpdateMeshPropertyGrid(wxPropertyGrid* pg, wxTreeListCtrl* treeList, wxTreeListEvent& event, LE3AssetManager& assets)
{
    pg->Clear();
    wxString name = treeList->GetItemText(event.GetItem());

    if (name.IsEmpty())
        return false;
    
    pg->Append(new wxStringProperty(wxT("Name"), wxPG_LABEL, name));
    pg->Append(new wxStringProperty(wxT("Path"), wxPG_LABEL, assets.m_meshesPaths[name.ToStdString()].path));

    return true;
}
void MeshPropertyGridChanged(wxPropertyGrid* pg, wxTreeListCtrl* treeList, wxPropertyGridEvent& event, LE3AssetManager& assets, std::string selectedName)
{
    if (event.GetPropertyName() == wxT("Name"))
    {
        std::string newName = event.GetPropertyValue().GetString().ToStdString();
        auto nh = assets.m_meshes.extract(selectedName);
        nh.key() = newName;
        assets.m_meshes.insert(std::move(nh));
        auto nh2 = assets.m_meshesPaths.extract(selectedName);
        nh2.key() = newName;
        assets.m_meshesPaths.insert(std::move(nh2));
    }
    else if (event.GetPropertyName() == wxT("Path"))
    {
        assets.m_meshesPaths[selectedName].path = event.GetPropertyValue().GetString().ToStdString();
        assets.LoadMesh(selectedName, assets.m_meshesPaths[selectedName].path);
    }
}