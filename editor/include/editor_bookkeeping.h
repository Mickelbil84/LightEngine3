#pragma once

#include <le3_asset_manager.h>
#include <le3_scene_manager.h>

void UpdateShaderBookkeeping(LE3AssetManager& assets, std::string oldShader, std::string newShader=std::string(""));
void UpdateTextureBookkeeping(LE3AssetManager& assets, std::string oldTexture, std::string newTexture=std::string(""));
void UpdateMeshBookkeeping(LE3SceneManager& scene, std::string oldMesh, std::string newMesh=std::string(""));
void UpdateMaterialBookkeeping(LE3SceneManager& scene, std::string oldMaterial, std::string newMaterial=std::string(""));