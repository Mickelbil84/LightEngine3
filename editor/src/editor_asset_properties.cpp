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
void ShaderPropertyGridChanged(wxPropertyGrid* pg, wxTreeListCtrl* treeList, wxPropertyGridEvent& event, LE3AssetManager& assets, LE3SceneManager& scene, std::string selectedName)
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
    int i;

    if (name.IsEmpty())
        return false;

    pg->Append(new wxStringProperty(wxT("Name"), wxPG_LABEL, name));

    wxPGChoices shaderChoices;
    i = 0;
    for (auto [key, value] : assets.m_shadersPaths)
        shaderChoices.Add(key, i++);
    pg->Append(new wxEnumProperty(wxT("Shader Name"), wxPG_LABEL, shaderChoices, shaderChoices.Index(assets.m_materials[name.ToStdString()].shaderName)));

    pg->Append(new wxPropertyCategory(wxT("Diffuse")));
    pg->Append(new wxFloatProperty(wxT("Diffuse R"), wxPG_LABEL, assets.m_materials[name.ToStdString()].diffuseColor.r));
    pg->Append(new wxFloatProperty(wxT("Diffuse G"), wxPG_LABEL, assets.m_materials[name.ToStdString()].diffuseColor.g));
    pg->Append(new wxFloatProperty(wxT("Diffuse B"), wxPG_LABEL, assets.m_materials[name.ToStdString()].diffuseColor.b));

    wxPGChoices textureChoices;
    i = 0;
    textureChoices.Add("", i++);
    for (auto [key, value] : assets.m_texturesPaths)
        textureChoices.Add(key, i++);
    pg->Append(new wxEnumProperty(wxT("Diffuse Texture"), wxPG_LABEL, textureChoices, textureChoices.Index(assets.m_materials[name.ToStdString()].diffuseTextureName)));
    pg->Append(new wxBoolProperty(wxT("Use Diffuse Texture"), wxPG_LABEL, assets.m_materials[name.ToStdString()].bUseDiffuseTexture));

    pg->Append(new wxPropertyCategory(wxT("Specular")));
    pg->Append(new wxFloatProperty(wxT("Specular R"), wxPG_LABEL, assets.m_materials[name.ToStdString()].specularColor.r));
    pg->Append(new wxFloatProperty(wxT("Specular G"), wxPG_LABEL, assets.m_materials[name.ToStdString()].specularColor.g));
    pg->Append(new wxFloatProperty(wxT("Specular B"), wxPG_LABEL, assets.m_materials[name.ToStdString()].specularColor.b));
    pg->Append(new wxFloatProperty(wxT("Specular Intensity"), wxPG_LABEL, assets.m_materials[name.ToStdString()].specularIntensity));
    pg->Append(new wxFloatProperty(wxT("Shininess"), wxPG_LABEL, assets.m_materials[name.ToStdString()].shininess));
    wxPGChoices specularTextureChoices;
    i = 0;
    specularTextureChoices.Add("", i++);
    for (auto [key, value] : assets.m_texturesPaths)
        specularTextureChoices.Add(key, i++);
    pg->Append(new wxEnumProperty(wxT("Specular Texture"), wxPG_LABEL, specularTextureChoices, specularTextureChoices.Index(assets.m_materials[name.ToStdString()].specularTextureName)));
    pg->Append(new wxBoolProperty(wxT("Use Specular Texture"), wxPG_LABEL, assets.m_materials[name.ToStdString()].bUseSpecularTexture));

    pg->Append(new wxPropertyCategory(wxT("Normal")));
    wxPGChoices normalTextureChoices;
    i = 0;
    normalTextureChoices.Add("", i++);
    for (auto [key, value] : assets.m_texturesPaths)
        normalTextureChoices.Add(key, i++);
    pg->Append(new wxEnumProperty(wxT("Normal Texture"), wxPG_LABEL, normalTextureChoices, normalTextureChoices.Index(assets.m_materials[name.ToStdString()].normalTextureName)));
    pg->Append(new wxBoolProperty(wxT("Use Normal Texture"), wxPG_LABEL, assets.m_materials[name.ToStdString()].bUseNormalTexture));

    pg->Append(new wxPropertyCategory(wxT("Reflections")));
    wxPGChoices reflectionTextureChoices;
    i = 0;
    reflectionTextureChoices.Add("", i++);
    for (auto [key, value] : assets.m_texturesPaths)
        reflectionTextureChoices.Add(key, i++);
    pg->Append(new wxEnumProperty(wxT("Reflection Texture"), wxPG_LABEL, reflectionTextureChoices, reflectionTextureChoices.Index(assets.m_materials[name.ToStdString()].cubemapName)));
    pg->Append(new wxFloatProperty(wxT("Reflection Intensity"), wxPG_LABEL, assets.m_materials[name.ToStdString()].reflectionIntensity));

    pg->Append(new wxPropertyCategory(wxT("Tiling")));
    pg->Append(new wxFloatProperty(wxT("Tiling X"), wxPG_LABEL, assets.m_materials[name.ToStdString()].tilingX));
    pg->Append(new wxFloatProperty(wxT("Tiling Y"), wxPG_LABEL, assets.m_materials[name.ToStdString()].tilingY));

    return true;
}
void MaterialPropertyGridChanged(wxPropertyGrid* pg, wxTreeListCtrl* treeList, wxPropertyGridEvent& event, LE3AssetManager& assets, LE3SceneManager& scene, std::string selectedName)
{
    LE3Material* material = assets.GetMaterial(selectedName);
    int i;

    if (event.GetPropertyName() == wxT("Name"))
    {
        std::string newName = event.GetPropertyValue().GetString().ToStdString();
        auto nh = assets.m_materials.extract(selectedName);
        nh.key() = newName;
        assets.m_materials.insert(std::move(nh));

        UpdateMaterialBookkeeping(scene, selectedName, newName);
    }
    else if (event.GetPropertyName() == wxT("Shader Name"))
    {
        wxPGChoices shaderChoices;
        i = 0;
        for (auto [key, value] : assets.m_shadersPaths)
            shaderChoices.Add(key, i++);
        material->shaderName = shaderChoices.GetLabel(event.GetPropertyValue().GetInteger());
    }
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
        wxPGChoices textureChoices;
        i = 0;
        textureChoices.Add("", i++);
        for (auto [key, value] : assets.m_texturesPaths)
            textureChoices.Add(key, i++);
        material->diffuseTextureName = textureChoices.GetLabel(event.GetPropertyValue().GetInteger());
    }
    else if (event.GetPropertyName() == wxT("Use Diffuse Texture"))
    {
        material->bUseDiffuseTexture = event.GetPropertyValue().GetBool();
    }
    else if (event.GetPropertyName() == wxT("Specular R"))
    {
        material->specularColor.r = event.GetPropertyValue().GetDouble();
    }
    else if (event.GetPropertyName() == wxT("Specular G"))
    {
        material->specularColor.g = event.GetPropertyValue().GetDouble();
    }
    else if (event.GetPropertyName() == wxT("Specular B"))
    {
        material->specularColor.b = event.GetPropertyValue().GetDouble();
    }
    else if (event.GetPropertyName() == wxT("Specular Intensity"))
    {
        material->specularIntensity = event.GetPropertyValue().GetDouble();
    }
    else if (event.GetPropertyName() == wxT("Shininess"))
    {
        material->shininess = event.GetPropertyValue().GetDouble();
    }
    else if (event.GetPropertyName() == wxT("Specular Texture"))
    {
        wxPGChoices textureChoices;
        i = 0;
        textureChoices.Add("", i++);
        for (auto [key, value] : assets.m_texturesPaths)
            textureChoices.Add(key, i++);
        material->specularTextureName = textureChoices.GetLabel(event.GetPropertyValue().GetInteger());
    }
    else if (event.GetPropertyName() == wxT("Use Specular Texture"))
    {
        material->bUseSpecularTexture = event.GetPropertyValue().GetBool();
    }
    else if (event.GetPropertyName() == wxT("Normal Texture"))
    {
        wxPGChoices textureChoices;
        i = 0;
        textureChoices.Add("", i++);
        for (auto [key, value] : assets.m_texturesPaths)
            textureChoices.Add(key, i++);
        material->normalTextureName = textureChoices.GetLabel(event.GetPropertyValue().GetInteger());
    }
    else if (event.GetPropertyName() == wxT("Use Normal Texture"))
    {
        material->bUseNormalTexture = event.GetPropertyValue().GetBool();
    }
    else if (event.GetPropertyName() == wxT("Reflection Texture"))
    {
        wxPGChoices textureChoices;
        i = 0;
        textureChoices.Add("", i++);
        for (auto [key, value] : assets.m_texturesPaths)
            textureChoices.Add(key, i++);
        material->cubemapName = textureChoices.GetLabel(event.GetPropertyValue().GetInteger());
    }
    else if (event.GetPropertyName() == wxT("Reflection Intensity"))
    {
        material->reflectionIntensity = event.GetPropertyValue().GetDouble();
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
    material->SetSpecularTexture(assets.GetTexture(material->specularTextureName));
    material->SetNormalTexture(assets.GetTexture(material->normalTextureName));
    material->SetCubemap(assets.GetTexture(material->cubemapName));
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
void TexturePropertyGridChanged(wxPropertyGrid* pg, wxTreeListCtrl* treeList, wxPropertyGridEvent& event, LE3AssetManager& assets, LE3SceneManager& scene, std::string selectedName)
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
void MeshPropertyGridChanged(wxPropertyGrid* pg, wxTreeListCtrl* treeList, wxPropertyGridEvent& event, LE3AssetManager& assets, LE3SceneManager& scene, std::string selectedName)
{
    if (event.GetPropertyName() == wxT("Name"))
    {
        std::string newName = event.GetPropertyValue().GetString().ToStdString();
        std::string path = assets.m_meshesPaths[selectedName].path;

        assets.m_meshesPaths.erase(selectedName);
        assets.AddMeshPath(newName, path);
        
        UpdateMeshBookkeeping(scene, selectedName, newName);

        assets.m_meshes.erase(selectedName);
    }
    else if (event.GetPropertyName() == wxT("Path"))
    {
        assets.m_meshesPaths[selectedName].path = event.GetPropertyValue().GetString().ToStdString();
        assets.LoadMesh(selectedName, assets.m_meshesPaths[selectedName].path);
    }
}