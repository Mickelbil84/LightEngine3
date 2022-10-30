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
        auto nh = assets.m_shaders.extract(selectedName);
        nh.key() = newName;
        assets.m_shaders.insert(std::move(nh));
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