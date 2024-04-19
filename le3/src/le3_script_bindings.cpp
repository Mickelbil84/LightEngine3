#include "le3_script_bindings.h"
using namespace le3;

void le3::bindLE3Types(lua_State* L) {
    REGISTER(LE3EngineConfig);
    REGISTER(LE3AssetManager);
    REGISTER(LE3VisualDebug);

    REGISTER(LE3Scene);
    REGISTER(LE3Shader);
    REGISTER(LE3Texture);
    REGISTER(LE3Material);
    REGISTER(LE3StaticMesh);
    REGISTER(LE3SkeletalMesh);
    REGISTER(LE3PointCloud);

    REGISTER(LE3Object);
    REGISTER(LE3ScriptObject);
    REGISTER(LE3Transform);
    REGISTER(LE3SceneRoot);
    REGISTER(LE3StaticModel);
    REGISTER(LE3SkeletalModel);
    REGISTER(LE3Input);
    REGISTER(LE3DrawableObject);
    REGISTER(LE3Camera);
    REGISTER(LE3OrbitCamera);
    REGISTER(LE3FreeCamera);
    REGISTER(LE3Box);
    REGISTER(LE3Cylinder);
    REGISTER(LE3Cone);

    REGISTER(LE3Light);
    REGISTER(LE3AmbientLight);
    REGISTER(LE3DirectionalLight);
    REGISTER(LE3PointLight);
    REGISTER(LE3SpotLight);

    // Bind enums
    // TODO: simpler code for that also
    SET_GLOBAL_NUMBER(L, "DRAW_PRIORITY_LOW", 0);
    SET_GLOBAL_NUMBER(L, "DRAW_PRIORITY_MEDIUM", 1);
    SET_GLOBAL_NUMBER(L, "DRAW_PRIORITY_HIGH", 2);
    SET_GLOBAL_NUMBER(L, "DRAW_PRIORITY_UI", 3);
}