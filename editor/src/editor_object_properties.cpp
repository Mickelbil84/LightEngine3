#include "editor_object_properties.h"

void UpdateObjectPropertyGrid(LE3Object* obj, wxPropertyGrid* pg, LE3AssetManager& assets)
{
    pg->Clear();

    pg->Append(new wxPropertyCategory(wxT("Name ")));
    pg->Append(new wxStringProperty(wxT("Name"), wxPG_LABEL, obj->GetName()));

    pg->Append(new wxPropertyCategory(wxT("Position")));
    pg->Append(new wxFloatProperty(wxT("Position X"), wxPG_LABEL, obj->GetPosition().x));
    pg->Append(new wxFloatProperty(wxT("Position Y"), wxPG_LABEL, obj->GetPosition().y));
    pg->Append(new wxFloatProperty(wxT("Position Z"), wxPG_LABEL, obj->GetPosition().z));

    pg->Append(new wxPropertyCategory(wxT("Rotation")));
    pg->Append(new wxFloatProperty(wxT("Rotation X"), wxPG_LABEL, obj->GetRotation().x));
    pg->Append(new wxFloatProperty(wxT("Rotation Y"), wxPG_LABEL, obj->GetRotation().y));
    pg->Append(new wxFloatProperty(wxT("Rotation Z"), wxPG_LABEL, obj->GetRotation().z));

    pg->Append(new wxPropertyCategory(wxT("Scale ")));
    pg->Append(new wxFloatProperty(wxT("Scale"), wxPG_LABEL, obj->GetScale()));

    if (dynamic_cast<LE3StaticMesh*>(obj))
        UpdateStaticMeshPropertyGrid(dynamic_cast<LE3StaticMesh*>(obj), pg, assets);
}

void ObjectPropertyGridChanged(LE3Object* obj, wxPropertyGrid* pg, wxPropertyGridEvent& event, LE3AssetManager& assets)
{
    if (event.GetPropertyName() == wxT("Name"))
        obj->SetName(event.GetPropertyValue().GetString().ToStdString());
    if (event.GetPropertyName() == wxT("Position X"))
        obj->SetPositionX(event.GetPropertyValue().GetDouble());
    if (event.GetPropertyName() == wxT("Position Y"))
        obj->SetPositionY(event.GetPropertyValue().GetDouble());
    if (event.GetPropertyName() == wxT("Position Z"))
        obj->SetPositionZ(event.GetPropertyValue().GetDouble());
    if (event.GetPropertyName() == wxT("Rotation X"))
        obj->SetRotationX(event.GetPropertyValue().GetDouble());
    if (event.GetPropertyName() == wxT("Rotation Y"))
        obj->SetRotationY(event.GetPropertyValue().GetDouble());
    if (event.GetPropertyName() == wxT("Rotation Z"))
        obj->SetRotationZ(event.GetPropertyValue().GetDouble());
    if (event.GetPropertyName() == wxT("Scale"))
        obj->SetScale(event.GetPropertyValue().GetDouble());

    if (dynamic_cast<LE3StaticMesh*>(obj))
        StaticMeshPropertyGridChanged(dynamic_cast<LE3StaticMesh*>(obj), pg, event, assets);

}

void UpdateStaticMeshPropertyGrid(LE3StaticMesh* obj, wxPropertyGrid* pg, LE3AssetManager& assets)
{
    std::string primitiveDescription = assets.m_meshesPaths[obj->meshName].path;
    if (primitiveDescription[0] != gPrimitivePathPrefix)
    {
        pg->Append(new wxPropertyCategory(wxT("LE3StaticMesh")));
        pg->Append(new wxStringProperty(wxT("Mesh Name"), wxPG_LABEL, obj->meshName));
        pg->Append(new wxStringProperty(wxT("Material Name"), wxPG_LABEL, obj->materialName));
    }
    else
    {
        LE3PrimitiveTokens tokens = ParsePrimitivePath(primitiveDescription);

        if (tokens.token == gTokenBox)
        {
            pg->Append(new wxPropertyCategory(wxT("LE3Cube")));
            pg->Append(new wxFloatProperty(wxT("Width"), wxPG_LABEL, tokens.params[3]));
            pg->Append(new wxFloatProperty(wxT("Height"), wxPG_LABEL, tokens.params[4]));
            pg->Append(new wxFloatProperty(wxT("Depth"), wxPG_LABEL, tokens.params[5]));
            pg->Append(new wxStringProperty(wxT("Material Name"), wxPG_LABEL, obj->materialName));
        }
    }
}

void StaticMeshPropertyGridChanged(LE3StaticMesh* obj, wxPropertyGrid* pg, wxPropertyGridEvent& event, LE3AssetManager& assets)
{
    if (event.GetPropertyName() == wxT("Mesh Name"))
        obj->meshName = event.GetPropertyValue().GetString().ToStdString();
    if (event.GetPropertyName() == wxT("Material Name"))
        obj->materialName = event.GetPropertyValue().GetString().ToStdString();

    std::string primitiveDescription = assets.m_meshesPaths[obj->meshName].path;
    if (primitiveDescription[0] == gPrimitivePathPrefix)
    {
        LE3PrimitiveTokens tokens = ParsePrimitivePath(primitiveDescription);

        if (tokens.token == gTokenBox)
        {
            if (event.GetPropertyName() == wxT("Width") ||
                event.GetPropertyName() == wxT("Height") ||
                event.GetPropertyName() == wxT("Depth"))
            {
                float newVal = event.GetPropertyValue().GetDouble();
                size_t idx;
                if (event.GetPropertyName() == wxT("Width")) idx = 3;
                if (event.GetPropertyName() == wxT("Height")) idx = 4;
                if (event.GetPropertyName() == wxT("Depth")) idx = 5;
                tokens.params[idx] = newVal;

                std::string del(1, gPrimitivePathDelimiter);
                std::string zero("0");
                std::string newPrimitiveDescription = 
                    std::string(1, gPrimitivePathPrefix) + tokens.token + del + 
                    zero + del + zero + del + zero + del +
                    std::to_string(tokens.params[3]) + del + 
                    std::to_string(tokens.params[4]) + del +
                    std::to_string(tokens.params[5]) + del;
                
                assets.m_meshes.erase(obj->meshName);
                assets.m_meshesPaths.erase(obj->meshName);
                assets.LoadMeshPrimitive(obj->meshName, newPrimitiveDescription);
            }
        }
    }
}