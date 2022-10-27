#include "editor_object_properties.h"

void UpdateObjectPropertyGrid(LE3Object* obj, wxPropertyGrid* pg)
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
        UpdateStaticMeshPropertyGrid(dynamic_cast<LE3StaticMesh*>(obj), pg);
}

void ObjectPropertyGridChanged(LE3Object* obj, wxPropertyGrid* pg, wxPropertyGridEvent& event)
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
        StaticMeshPropertyGridChanged(dynamic_cast<LE3StaticMesh*>(obj), pg, event);

}

void UpdateStaticMeshPropertyGrid(LE3StaticMesh* obj, wxPropertyGrid* pg)
{
    pg->Append(new wxPropertyCategory(wxT("LE3StaticMesh")));
    pg->Append(new wxStringProperty(wxT("Mesh Name"), wxPG_LABEL, obj->meshName));
    pg->Append(new wxStringProperty(wxT("Material Name"), wxPG_LABEL, obj->materialName));
}

void StaticMeshPropertyGridChanged(LE3StaticMesh* obj, wxPropertyGrid* pg, wxPropertyGridEvent& event)
{
    if (event.GetPropertyName() == wxT("Mesh Name"))
        obj->meshName = event.GetPropertyValue().GetString().ToStdString();
    if (event.GetPropertyName() == wxT("Material Name"))
        obj->materialName = event.GetPropertyValue().GetString().ToStdString();
}