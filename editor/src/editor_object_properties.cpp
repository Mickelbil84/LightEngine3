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
    int i;

    wxPGChoices materialChoices;
    i = 0;
    for (auto [key, value] : assets.m_materials)
        materialChoices.Add(key, i++);

    if (primitiveDescription[0] != gPrimitivePathPrefix)
    {
        pg->Append(new wxPropertyCategory(wxT("LE3StaticMesh")));
        // pg->Append(new wxStringProperty(wxT("Mesh Name"), wxPG_LABEL, obj->meshName));
        wxPGChoices meshChoices;
        i = 0;
        for (auto [key, value] : assets.m_meshesPaths)
        {
            if (value.path != std::string("") && value.path[0] == gPrimitivePathPrefix)
                continue;
            meshChoices.Add(key, i++);
        }
        pg->Append(new wxEnumProperty(wxT("Mesh Name"), wxPG_LABEL, meshChoices, meshChoices.Index(obj->meshName)));
        

        // pg->Append(new wxStringProperty(wxT("Material Name"), wxPG_LABEL, obj->materialName));
        pg->Append(new wxEnumProperty(wxT("Material Name"), wxPG_LABEL, materialChoices, materialChoices.Index(obj->materialName)));
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
            // pg->Append(new wxStringProperty(wxT("Material Name"), wxPG_LABEL, obj->materialName));
            pg->Append(new wxEnumProperty(wxT("Material Name"), wxPG_LABEL, materialChoices, materialChoices.Index(obj->materialName)));
        }
        else if (tokens.token == gTokenCylinder)
        {
            pg->Append(new wxPropertyCategory(wxT("LE3Cylinder")));
            pg->Append(new wxFloatProperty(wxT("Radius"), wxPG_LABEL, tokens.params[3]));
            pg->Append(new wxFloatProperty(wxT("Height"), wxPG_LABEL, tokens.params[4]));
            pg->Append(new wxIntProperty(wxT("Resolution"), wxPG_LABEL, (GLushort)tokens.params[5]));
            if (tokens.params.size() >= 7)
                pg->Append(new wxBoolProperty(wxT("With Caps"), wxPG_LABEL, (GLushort)tokens.params[6]));
            else
                pg->Append(new wxBoolProperty(wxT("With Caps"), wxPG_LABEL, false));
            // pg->Append(new wxStringProperty(wxT("Material Name"), wxPG_LABEL, obj->materialName));
            pg->Append(new wxEnumProperty(wxT("Material Name"), wxPG_LABEL, materialChoices, materialChoices.Index(obj->materialName)));
        }
        else if (tokens.token == gTokenCone)
        {
            pg->Append(new wxPropertyCategory(wxT("LE3Cone")));
            pg->Append(new wxFloatProperty(wxT("Radius"), wxPG_LABEL, tokens.params[3]));
            pg->Append(new wxFloatProperty(wxT("Height"), wxPG_LABEL, tokens.params[4]));
            pg->Append(new wxIntProperty(wxT("Resolution"), wxPG_LABEL, (GLushort)tokens.params[5]));
            // pg->Append(new wxStringProperty(wxT("Material Name"), wxPG_LABEL, obj->materialName));
            pg->Append(new wxEnumProperty(wxT("Material Name"), wxPG_LABEL, materialChoices, materialChoices.Index(obj->materialName)));
        }
        else if (tokens.token == gTokenTorus)
        {
            pg->Append(new wxPropertyCategory(wxT("LE3Torus")));
            pg->Append(new wxFloatProperty(wxT("Major Radius"), wxPG_LABEL, tokens.params[3]));
            pg->Append(new wxFloatProperty(wxT("Minor Radius"), wxPG_LABEL, tokens.params[4]));
            pg->Append(new wxIntProperty(wxT("Resolution"), wxPG_LABEL, (GLushort)tokens.params[5]));
            pg->Append(new wxEnumProperty(wxT("Material Name"), wxPG_LABEL, materialChoices, materialChoices.Index(obj->materialName)));
        }
        else if (tokens.token == gTokenSphere)
        {
            pg->Append(new wxPropertyCategory(wxT("LE3Sphere")));
            pg->Append(new wxFloatProperty(wxT("Radius"), wxPG_LABEL, tokens.params[3]));
            pg->Append(new wxIntProperty(wxT("Resolution"), wxPG_LABEL, (GLushort)tokens.params[4]));
            // pg->Append(new wxStringProperty(wxT("Material Name"), wxPG_LABEL, obj->materialName));
            pg->Append(new wxEnumProperty(wxT("Material Name"), wxPG_LABEL, materialChoices, materialChoices.Index(obj->materialName)));
        }
    }
}

void StaticMeshPropertyGridChanged(LE3StaticMesh* obj, wxPropertyGrid* pg, wxPropertyGridEvent& event, LE3AssetManager& assets)
{
    int i;

    if (event.GetPropertyName() == wxT("Mesh Name"))
    {
        wxPGChoices meshChoices;
        i = 0;
        for (auto [key, value] : assets.m_meshesPaths)
        {
            if (value.path != std::string("") && value.path[0] == gPrimitivePathPrefix)
                continue;
            meshChoices.Add(key, i++);
        }
        obj->meshName = meshChoices.GetLabel(event.GetPropertyValue().GetInteger());
    }
    if (event.GetPropertyName() == wxT("Material Name"))
    {
        wxPGChoices materialChoices;
        i = 0;
        for (auto [key, value] : assets.m_materials)
            materialChoices.Add(key, i++);
        obj->materialName = materialChoices.GetLabel(event.GetPropertyValue().GetInteger());
    }

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
        else if (tokens.token == gTokenCylinder)
        {
            if (tokens.params.size() < 7)
                tokens.params.push_back(0);
            if (event.GetPropertyName() == wxT("Radius") ||
                event.GetPropertyName() == wxT("Height") ||
                event.GetPropertyName() == wxT("Resolution") ||
                event.GetPropertyName() == wxT("With Caps"))
            {
                float newVal = event.GetPropertyValue().GetDouble();
                size_t idx;
                if (event.GetPropertyName() == wxT("Radius")) idx = 3;
                if (event.GetPropertyName() == wxT("Height")) idx = 4;
                if (event.GetPropertyName() == wxT("Resolution")) idx = 5;
                if (event.GetPropertyName() == wxT("With Caps"))
                    tokens.params[6] = event.GetPropertyValue().GetBool();
                else
                    tokens.params[idx] = newVal;

                std::string del(1, gPrimitivePathDelimiter);
                std::string zero("0");
                std::string newPrimitiveDescription = 
                    std::string(1, gPrimitivePathPrefix) + tokens.token + del + 
                    zero + del + zero + del + zero + del +
                    std::to_string(tokens.params[3]) + del + 
                    std::to_string(tokens.params[4]) + del +
                    std::to_string(tokens.params[5]) + del + 
                    std::to_string((GLushort)tokens.params[6]) + del;
                
                assets.m_meshes.erase(obj->meshName);
                assets.m_meshesPaths.erase(obj->meshName);
                assets.LoadMeshPrimitive(obj->meshName, newPrimitiveDescription);
            }
        }
        else if (tokens.token == gTokenCone)
        {
            if (event.GetPropertyName() == wxT("Radius") ||
                event.GetPropertyName() == wxT("Height") ||
                event.GetPropertyName() == wxT("Resolution"))
            {
                float newVal = event.GetPropertyValue().GetDouble();
                size_t idx;
                if (event.GetPropertyName() == wxT("Radius")) idx = 3;
                if (event.GetPropertyName() == wxT("Height")) idx = 4;
                if (event.GetPropertyName() == wxT("Resolution")) idx = 5;
                tokens.params[idx] = newVal;

                std::string del(1, gPrimitivePathDelimiter);
                std::string zero("0");
                std::string newPrimitiveDescription = 
                    std::string(1, gPrimitivePathPrefix) + tokens.token + del + 
                    zero + del + zero + del + zero + del +
                    std::to_string(tokens.params[3]) + del + 
                    std::to_string(tokens.params[4]) + del +
                    std::to_string(tokens.params[5]) + del + 
                    std::to_string((GLushort)tokens.params[6]) + del;
                
                assets.m_meshes.erase(obj->meshName);
                assets.m_meshesPaths.erase(obj->meshName);
                assets.LoadMeshPrimitive(obj->meshName, newPrimitiveDescription);
            }
        }
        else if (tokens.token == gTokenTorus)
        {
            if (event.GetPropertyName() == wxT("Major Radius") ||
                event.GetPropertyName() == wxT("Minor Radius") ||
                event.GetPropertyName() == wxT("Resolution"))
            {
                float newVal = event.GetPropertyValue().GetDouble();
                size_t idx;
                if (event.GetPropertyName() == wxT("Major Radius")) idx = 3;
                if (event.GetPropertyName() == wxT("Minor Radius")) idx = 4;
                if (event.GetPropertyName() == wxT("Resolution")) idx = 5;
                tokens.params[idx] = newVal;

                std::string del(1, gPrimitivePathDelimiter);
                std::string zero("0");
                std::string newPrimitiveDescription = 
                    std::string(1, gPrimitivePathPrefix) + tokens.token + del + 
                    zero + del + zero + del + zero + del +
                    std::to_string(tokens.params[3]) + del + 
                    std::to_string(tokens.params[4]) + del +
                    std::to_string(tokens.params[5]) + del + 
                    std::to_string((GLushort)tokens.params[6]) + del;
                
                assets.m_meshes.erase(obj->meshName);
                assets.m_meshesPaths.erase(obj->meshName);
                assets.LoadMeshPrimitive(obj->meshName, newPrimitiveDescription);
            }
        }
        else if (tokens.token == gTokenSphere)
        {
            if (event.GetPropertyName() == wxT("Radius") ||
                event.GetPropertyName() == wxT("Resolution"))
            {
                float newVal = event.GetPropertyValue().GetDouble();
                size_t idx;
                if (event.GetPropertyName() == wxT("Radius")) idx = 3;
                if (event.GetPropertyName() == wxT("Resolution")) idx = 4;
                tokens.params[idx] = newVal;

                std::string del(1, gPrimitivePathDelimiter);
                std::string zero("0");
                std::string newPrimitiveDescription = 
                    std::string(1, gPrimitivePathPrefix) + tokens.token + del + 
                    zero + del + zero + del + zero + del +
                    std::to_string(tokens.params[3]) + del + 
                    std::to_string(tokens.params[4]) + del;
                
                assets.m_meshes.erase(obj->meshName);
                assets.m_meshesPaths.erase(obj->meshName);
                assets.LoadMeshPrimitive(obj->meshName, newPrimitiveDescription);
            }
        }
    }
}