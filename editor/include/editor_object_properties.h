#pragma once

#include <map>
#include <vector>
#include <string>

#include <wx/wx.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>

#include <le3_object.h>
#include <le3_static_mesh.h>
#include <le3_asset_manager.h>

// LE3Object Properties
void UpdateObjectPropertyGrid(LE3Object* obj, wxPropertyGrid* pg, LE3AssetManager& assets);
void ObjectPropertyGridChanged(LE3Object* obj, wxPropertyGrid* pg, wxPropertyGridEvent& event, LE3AssetManager& assets);

// LE3StaticMesh Properties
void UpdateStaticMeshPropertyGrid(LE3StaticMesh* obj, wxPropertyGrid* pg, LE3AssetManager& assets);
void StaticMeshPropertyGridChanged(LE3StaticMesh* obj, wxPropertyGrid* pg, wxPropertyGridEvent& event, LE3AssetManager& assets);
