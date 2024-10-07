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
    LE3ObjectPtr obj;
    LE3ShaderPtr shader;
    LE3MaterialPtr material;
    LE3TexturePtr texture;
    LE3StaticMeshPtr staticMesh;
    LE3SkeletalMeshPtr skeletalMesh;


    switch (LE3GetEditorManager().getSelection().type)
    {
    case LE3EditorSelection::LE3SelectionType::LE3_SELECTION_OBJECT:
        obj = LE3GetEditorManager().getSelection().pObject.lock();
        LE3GetScriptSystem().getGlobal("update_object_properties_panel");
        LE3GetScriptSystem().pushUserType(&obj);
        LE3GetScriptSystem().callFunction(1, 0);
        break;

    case LE3EditorSelection::LE3SelectionType::LE3_SELECTION_ASSET_SHADER:
        shader = LE3GetEditorManager().getSelection().pShader;
        LE3GetScriptSystem().getGlobal("update_shader_properties_panel");
        LE3GetScriptSystem().pushUserType(&shader);
        LE3GetScriptSystem().callFunction(1, 0);
        break;

    case LE3EditorSelection::LE3SelectionType::LE3_SELECTION_ASSET_MATERIAL:
        material = LE3GetEditorManager().getSelection().pMaterial;
        LE3GetScriptSystem().getGlobal("update_material_properties_panel");
        LE3GetScriptSystem().pushUserType(&material);
        LE3GetScriptSystem().callFunction(1, 0);
        break;
    
    case LE3EditorSelection::LE3SelectionType::LE3_SELECTION_ASSET_TEXTURE:
        texture = LE3GetEditorManager().getSelection().pTexture;
        LE3GetScriptSystem().getGlobal("update_texture_properties_panel");
        LE3GetScriptSystem().pushUserType(&texture);
        LE3GetScriptSystem().callFunction(1, 0);
        break;

    case LE3EditorSelection::LE3SelectionType::LE3_SELECTION_ASSET_MESH:
        if ((staticMesh = LE3GetEditorManager().getSelection().pStaticMesh)) {
            LE3GetScriptSystem().getGlobal("update_static_mesh_properties_panel");
            LE3GetScriptSystem().pushUserType(&staticMesh);
            LE3GetScriptSystem().callFunction(1, 0);
        }
        else if ((skeletalMesh = LE3GetEditorManager().getSelection().pSkeletalMesh)) {
            LE3GetScriptSystem().getGlobal("update_skeletal_mesh_properties_panel");
            LE3GetScriptSystem().pushUserType(&skeletalMesh);
            LE3GetScriptSystem().callFunction(1, 0);
        }
        break;
    
    default:
        break;
    }
}