#pragma once

#include <map>
#include <vector>
#include <string>

#include <wx/wx.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>

#include <le3_object.h>
#include <le3_static_mesh.h>

// LE3Object Properties
void UpdateObjectPropertyGrid(LE3Object* obj, wxPropertyGrid* pg);
void ObjectPropertyGridChanged(LE3Object* obj, wxPropertyGrid* pg, wxPropertyGridEvent& event);

// LE3StaticMesh Properties
void UpdateStaticMeshPropertyGrid(LE3StaticMesh* obj, wxPropertyGrid* pg);
void StaticMeshPropertyGridChanged(LE3StaticMesh* obj, wxPropertyGrid* pg, wxPropertyGridEvent& event);