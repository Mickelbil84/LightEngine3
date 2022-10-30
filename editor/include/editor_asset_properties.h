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

bool UpdateShaderPropertyGrid(wxPropertyGrid* pg, wxTreeListCtrl* treeList, wxTreeListEvent& event, LE3AssetManager& assets);
void ShaderPropertyGridChanged(wxPropertyGrid* pg, wxTreeListCtrl* treeList, wxPropertyGridEvent& event, LE3AssetManager& assets, std::string selectedName);