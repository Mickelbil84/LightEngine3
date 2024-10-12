#include "widgets/le3ed_properties_panel.h"
using namespace le3;

/*
* Since object serialization happens in Lua anyway, it's also easier to use Lua
* For the properties panel
*/

void LE3EditorPropertiesPanel::init() {
    LE3GetScriptSystem().doFile("/editor/scripts/widgets_properties.lua");
}
void LE3EditorPropertiesPanel::update() {
    LE3ObjectPtr obj = LE3GetEditorManager().getSelection().pObject.lock();
    LE3ShaderPtr shader = LE3GetEditorManager().getSelection().pShader;
    LE3MaterialPtr material = LE3GetEditorManager().getSelection().pMaterial;
    LE3TexturePtr texture = LE3GetEditorManager().getSelection().pTexture;
    LE3StaticMeshPtr staticMesh = LE3GetEditorManager().getSelection().pStaticMesh;
    LE3SkeletalMeshPtr skeletalMesh = LE3GetEditorManager().getSelection().pSkeletalMesh;
    std::string animationTrack = LE3GetEditorManager().getSelection().animationTrack;

    switch (LE3GetEditorManager().getSelection().type)
    {
    case LE3EditorSelection::LE3SelectionType::LE3_SELECTION_OBJECT:
        if (!obj) break;
        LE3GetScriptSystem().getGlobal("update_object_properties_panel");
        LE3GetScriptSystem().pushUserType(&obj);
        LE3GetScriptSystem().callFunction(1, 0);
        break;

    case LE3EditorSelection::LE3SelectionType::LE3_SELECTION_ASSET_SHADER:
        if (shader.expired()) break;
        LE3GetScriptSystem().getGlobal("update_shader_properties_panel");
        LE3GetScriptSystem().pushString(shader.lock()->getName());
        LE3GetScriptSystem().callFunction(1, 0);
        break;

    case LE3EditorSelection::LE3SelectionType::LE3_SELECTION_ASSET_MATERIAL:
        if (material.expired()) break;
        LE3GetScriptSystem().getGlobal("update_material_properties_panel");
        LE3GetScriptSystem().pushString(material.lock()->name);
        LE3GetScriptSystem().callFunction(1, 0);
        break;
    
    case LE3EditorSelection::LE3SelectionType::LE3_SELECTION_ASSET_TEXTURE:
        if (texture.expired()) break;
        LE3GetScriptSystem().getGlobal("update_texture_properties_panel");
        LE3GetScriptSystem().pushString(texture.lock()->getName());
        LE3GetScriptSystem().callFunction(1, 0);
        break;

    case LE3EditorSelection::LE3SelectionType::LE3_SELECTION_ASSET_MESH:
        if (staticMesh.lock()) {
            LE3GetScriptSystem().getGlobal("update_static_mesh_properties_panel");
            LE3GetScriptSystem().pushString(staticMesh.lock()->getName());
            LE3GetScriptSystem().callFunction(1, 0);
        }
        else if (skeletalMesh.lock()) {
            LE3GetScriptSystem().getGlobal("update_skeletal_mesh_properties_panel");
            LE3GetScriptSystem().pushString(skeletalMesh.lock()->getName());
            LE3GetScriptSystem().callFunction(1, 0);
        }
        break;
    
    case LE3EditorSelection::LE3SelectionType::LE3_SELECTION_ASSET_ANIMATION:
        LE3GetScriptSystem().getGlobal("update_animation_properties_panel");
        LE3GetScriptSystem().pushString(skeletalMesh.lock()->getName());
        LE3GetScriptSystem().pushString(animationTrack);
        LE3GetScriptSystem().callFunction(2, 0);
        break;

    default:
        break;
    }
}