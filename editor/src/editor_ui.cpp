#include "editor_ui.h"

LE3EditorUI::LE3EditorUI(wxWindow* parent) : LE3EditorWindow(parent), m_selectedType(LE3_SELECTED_NONE)
{
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
    m_propertyGrid->Clear();
    wxString name = this->m_treeListShaders->GetItemText(event.GetItem());

    if (name.IsEmpty())
    {
        m_selectedType = LE3_SELECTED_NONE;
        m_selectedName = std::string("");
        return;
    }
    
    m_propertyGrid->Append(new wxStringProperty(wxT("Name"), wxPG_LABEL, name));
    m_propertyGrid->Append(new wxFileProperty(wxT("Vertex Shader Path"), wxPG_LABEL, this->m_editor->scene.assets.m_shaders[name.ToStdString()].m_vertexShaderPath));
    m_propertyGrid->Append(new wxFileProperty(wxT("Fragment Shader Path"), wxPG_LABEL, this->m_editor->scene.assets.m_shaders[name.ToStdString()].m_fragmentShaderPath));

    m_selectedType = LE3_SELECTED_SHADER;
    m_selectedName = name.ToStdString();
}
void LE3EditorUI::OnPropertyChangeShader(wxPropertyGridEvent& event)
{
    if (event.GetPropertyName() == wxT("Name"))
    {
        std::string newName = event.GetPropertyValue().GetString().ToStdString();
        auto nh = m_editor->scene.assets.m_shaders.extract(m_selectedName);
        nh.key() = newName;
        m_editor->scene.assets.m_shaders.insert(std::move(nh));

        // Refresh the assets pane
        RefreshAssets();
    }
    else if (event.GetPropertyName() == wxT("Vertex Shader Path"))
    {
        LE3Shader* shader = m_editor->scene.assets.GetShader(m_selectedName);
        shader->m_vertexShaderPath = event.GetPropertyValue().GetString().ToStdString();
        shader->CompileShader(shader->m_vertexShaderPath, shader->m_fragmentShaderPath);
    }
    else if (event.GetPropertyName() == wxT("Fragment Shader Path"))
    {
        LE3Shader* shader = m_editor->scene.assets.GetShader(m_selectedName);
        shader->m_fragmentShaderPath = event.GetPropertyValue().GetString().ToStdString();
        shader->CompileShader(shader->m_vertexShaderPath, shader->m_fragmentShaderPath);
    }
}

void LE3EditorUI::OnPropertyChange( wxPropertyGridEvent& event )
{
    switch(m_selectedType)
    {
    case LE3_SELECTED_SHADER:
        OnPropertyChangeShader(event);
        break;

    case LE3_SELECTED_NONE:
    default:
         event.Skip(); 
         break;
    }
}