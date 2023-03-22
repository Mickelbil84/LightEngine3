#pragma once

#include <map>
#include <vector>
#include <string>

#include <wx/wx.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>

#include <le3_light.h>
#include <le3_object.h>
#include <le3_static_mesh.h>
#include <le3_asset_manager.h>
#include <le3_light_manager.h>

// LE3Object Properties
void UpdateObjectPropertyGrid(LE3Object* obj, wxPropertyGrid* pg, LE3AssetManager& assets);
void ObjectPropertyGridChanged(LE3Object* obj, wxPropertyGrid* pg, wxPropertyGridEvent& event, LE3AssetManager& assets, LE3LightManager& lightManager);

// LE3StaticMesh Properties
void UpdateStaticMeshPropertyGrid(LE3StaticMesh* obj, wxPropertyGrid* pg, LE3AssetManager& assets);
void StaticMeshPropertyGridChanged(LE3StaticMesh* obj, wxPropertyGrid* pg, wxPropertyGridEvent& event, LE3AssetManager& assets);

// Lights properties
void UpdateAmbientLightPropertyGrid(LE3AmbientLight* obj, wxPropertyGrid* pg);
void AmbientLightPropertyGridChanged(LE3AmbientLight* obj, wxPropertyGrid* pg, wxPropertyGridEvent& event);
void UpdateDirectionalLightPropertyGrid(LE3DirectionalLight* obj, wxPropertyGrid* pg);
void DirectionalLightPropertyGridChanged(LE3DirectionalLight* obj, wxPropertyGrid* pg, wxPropertyGridEvent& event, LE3LightManager& lightManager);
void UpdatePointLightPropertyGrid(LE3PointLight* obj, wxPropertyGrid* pg);
void PointLightPropertyGridChanged(LE3PointLight* obj, wxPropertyGrid* pg, wxPropertyGridEvent& event, LE3LightManager& lightManager);
void UpdateSpotLightPropertyGrid(LE3SpotLight* obj, wxPropertyGrid* pg);
void SpotLightPropertyGridChanged(LE3SpotLight* obj, wxPropertyGrid* pg, wxPropertyGridEvent& event, LE3LightManager& lightManager);
