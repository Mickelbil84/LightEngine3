#pragma once

#include <map>
#include <vector>
#include <string>

#include <wx/wx.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>
#include <wx/treelist.h>

#include <le3_shader.h>
#include <le3_asset_manager.h>
#include <le3_scene_manager.h>

#include "editor_bookkeeping.h"

bool UpdateShaderPropertyGrid(wxPropertyGrid* pg, wxTreeListCtrl* treeList, wxTreeListEvent& event, LE3AssetManager& assets);
void ShaderPropertyGridChanged(wxPropertyGrid* pg, wxTreeListCtrl* treeList, wxPropertyGridEvent& event, LE3AssetManager& assets, LE3SceneManager& scene, std::string selectedName);

bool UpdateMaterialPropertyGrid(wxPropertyGrid* pg, wxTreeListCtrl* treeList, wxTreeListEvent& event, LE3AssetManager& assets);
void MaterialPropertyGridChanged(wxPropertyGrid* pg, wxTreeListCtrl* treeList, wxPropertyGridEvent& event, LE3AssetManager& assets, LE3SceneManager& scene, std::string selectedName);

bool UpdateTexturePropertyGrid(wxPropertyGrid* pg, wxTreeListCtrl* treeList, wxTreeListEvent& event, LE3AssetManager& assets);
void TexturePropertyGridChanged(wxPropertyGrid* pg, wxTreeListCtrl* treeList, wxPropertyGridEvent& event, LE3AssetManager& assets, LE3SceneManager& scene, std::string selectedName);

bool UpdateMeshPropertyGrid(wxPropertyGrid* pg, wxTreeListCtrl* treeList, wxTreeListEvent& event, LE3AssetManager& assets);
void MeshPropertyGridChanged(wxPropertyGrid* pg, wxTreeListCtrl* treeList, wxPropertyGridEvent& event, LE3AssetManager& assets, LE3SceneManager& scene, std::string selectedName);