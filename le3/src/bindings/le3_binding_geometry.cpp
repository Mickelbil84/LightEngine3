#include "scripting/le3_script_bindings.h"
#include "core/le3_engine_systems.h"
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

FBIND(LE3StaticMesh, get_collider_type)
    GET_STRING(meshName)
    std::shared_ptr<LE3StaticMesh> mesh = LE3GetAssetManager().getStaticMesh(meshName).lock();
    if (!mesh) {PUSH_NIL()}
    else {PUSH_STRING(LE3ColliderType_toString(mesh->getColliderType()))}
FEND()

FBIND(LE3StaticMesh, set_collider_type)
    GET_STRING(meshName)
    GET_STRING(type)
    LE3ColliderType colliderType = LE3ColliderType_fromString(type);
    std::shared_ptr<LE3StaticMesh> mesh = LE3GetAssetManager().getStaticMesh(meshName).lock();
    if (mesh) {mesh->setColliderType(colliderType);}
FEND()

LIB(LE3StaticMesh, 
    get_name, set_name,
    get_mesh_path, set_mesh_path,
    reload_mesh,
    get_collider_type, set_collider_type
)


// ---------------------------

FBIND(LE3SkeletalMesh, set_name)
    GET_STRING(meshName)
    GET_STRING(name)
    LE3GetAssetManager().renameSkeletalMesh(meshName, name);
FEND()

FBIND(LE3SkeletalMesh, get_name)
    GET_STRING(meshName)
    std::shared_ptr<LE3SkeletalMesh> mesh = LE3GetAssetManager().getSkeletalMesh(meshName).lock();
    if (!mesh) {PUSH_STRING("")}
    else {PUSH_STRING(mesh->getName())}
FEND()

FBIND(LE3SkeletalMesh, reload_mesh)
    GET_STRING(meshName)
    GET_STRING(path)
    LE3GetAssetManager().reloadSkeletalMesh(meshName, path);
FEND()

FBIND(LE3SkeletalMesh, get_mesh_path)
    GET_STRING(meshName)
    PUSH_STRING(LE3GetAssetManager().getMeshPath(meshName))
FEND()

FBIND(LE3SkeletalMesh, set_mesh_path)
    GET_STRING(meshName)
    GET_STRING(path)
    LE3GetAssetManager().setMeshPath(meshName, path);
FEND()

FBIND(LE3SkeletalMesh, get_collider_type)
    GET_STRING(meshName)
    std::shared_ptr<LE3SkeletalMesh> mesh = LE3GetAssetManager().getSkeletalMesh(meshName).lock();
    if (!mesh) {PUSH_NIL()}
    else {PUSH_STRING(LE3ColliderType_toString(mesh->getColliderType()))}
FEND()

FBIND(LE3SkeletalMesh, set_collider_type)
    GET_STRING(meshName)
    GET_STRING(type)
    LE3ColliderType colliderType = LE3ColliderType_fromString(type);
    std::shared_ptr<LE3SkeletalMesh> mesh = LE3GetAssetManager().getSkeletalMesh(meshName).lock();
    if (mesh) {mesh->setColliderType(colliderType);}
FEND()

FBIND(LE3SkeletalMesh, get_num_animations)
    GET_STRING(meshName)
    std::shared_ptr<LE3SkeletalMesh> mesh = LE3GetAssetManager().getSkeletalMesh(meshName).lock();
    if (!mesh) {PUSH_NUMBER(0)}
    else {PUSH_NUMBER(mesh->getAnimationTracks().size())}
FEND()
FBIND(LE3SkeletalMesh, get_animation_at_idx)
    GET_STRING(meshName)
    GET_NUMBER(animIdx)
    std::shared_ptr<LE3SkeletalMesh> mesh = LE3GetAssetManager().getSkeletalMesh(meshName).lock();
    if (!mesh) {PUSH_NIL()}
    else {
        std::string animName;
        int i = 0;
        for (auto const & [name, track] : mesh->getAnimationTracks()) {
            if (i++ == (int)animIdx) {
                animName = name;
                break;
            }
        }
        std::string animPath = LE3GetAssetManager().getSkeletalAnimationPath(animName, meshName);
        PUSH_STRING(animName)
        PUSH_STRING(animPath)
    }
FEND()

LIB(LE3SkeletalMesh, 
    get_name, set_name,
    get_mesh_path, set_mesh_path,
    reload_mesh,
    get_collider_type, set_collider_type,
    get_num_animations, get_animation_at_idx
)