#include "le3_script_bindings.h"
#include "le3_engine_systems.h"
using namespace le3;

FBIND(LE3StaticMesh, set_name)
    GET_STRING(meshName)
    GET_STRING(name)
    LE3GetAssetManager().renameStaticMesh(meshName, name);
FEND()

FBIND(LE3StaticMesh, get_name)
    GET_STRING(meshName)
    std::shared_ptr<LE3StaticMesh> mesh = LE3GetAssetManager().getStaticMesh(meshName).lock();
    if (!mesh) {PUSH_STRING("")}
    else {PUSH_STRING(mesh->getName())}
FEND()

FBIND(LE3StaticMesh, reload_mesh)
    GET_STRING(meshName)
    GET_STRING(path)
    GET_BOOL(keepData)
    LE3GetAssetManager().reloadStaticMesh(meshName, path, keepData);
FEND()

FBIND(LE3StaticMesh, get_mesh_path)
    GET_STRING(meshName)
    PUSH_STRING(LE3GetAssetManager().getMeshPath(meshName))
FEND()

FBIND(LE3StaticMesh, set_mesh_path)
    GET_STRING(meshName)
    GET_STRING(path)
    LE3GetAssetManager().setMeshPath(meshName, path);
FEND()

LIB(LE3StaticMesh, 
    get_name, set_name,
    get_mesh_path, set_mesh_path,
    reload_mesh
)


// ---------------------------

LIB(LE3SkeletalMesh)