#include "scripting/le3_script_bindings.h"
#include "core/le3_engine_systems.h"
using namespace le3;

FBIND(LE3StaticModel, get_mesh) 
    GET_UDATA_OBJECT(self, LE3StaticModel)
    LE3StaticMeshPtr mesh = self->getMesh();
    if (mesh.expired()) {
        PUSH_STRING("")
    }
    else {
        PUSH_STRING(mesh.lock()->getName())
    }
FEND()
FBIND(LE3StaticModel, set_mesh)
    GET_UDATA_OBJECT(self, LE3StaticModel)
    GET_STRING(name)
    self->setMesh(LE3GetAssetManager().getStaticMesh(name));
FEND()

LIB(LE3StaticModel, 
    get_mesh, set_mesh
)

FBIND(LE3SkeletalModel, get_mesh) 
    GET_UDATA_OBJECT(self, LE3SkeletalModel)
    LE3SkeletalMeshPtr mesh = self->getMesh();
    if (mesh.expired()) {
        PUSH_STRING("")
    }
    else {
        PUSH_STRING(mesh.lock()->getName())
    }
FEND()
FBIND(LE3SkeletalModel, set_mesh)
    GET_UDATA_OBJECT(self, LE3SkeletalModel)
    GET_STRING(name)
    self->setMesh(LE3GetAssetManager().getSkeletalMesh(name));
FEND()


FBIND_OBJECT_GETTER_STRING(LE3SkeletalModel, get_current_animation, getCurrentAnimation)
FBIND(LE3SkeletalModel, set_current_animation)
    GET_UDATA_OBJECT(self, LE3SkeletalModel)
    GET_STRING(animationName)
    GET_NUMBER(blendTime)
    self->setCurrentAnimation(animationName, blendTime);
FEND()
FBIND_OBJECT_GETTER_BOOL(LE3SkeletalModel, is_animation_playing, isAnimationPlaying)
FBIND_OBJECT_SETTER_BOOL(LE3SkeletalModel, set_animation_playing, setAnimationPlaying)
FBIND(LE3SkeletalModel, reset_animation)
    GET_UDATA_OBJECT(self, LE3SkeletalModel)
    self->resetAnimation();
FEND()

LIB(LE3SkeletalModel, 
    get_mesh, set_mesh,

    get_current_animation, set_current_animation,
    is_animation_playing, set_animation_playing,
    reset_animation,
)