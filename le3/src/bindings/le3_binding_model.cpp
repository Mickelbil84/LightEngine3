#include "le3_script_bindings.h"
#include "le3_engine_systems.h"
using namespace le3;

FBIND_OBJECT_GETTER_STRING(LE3StaticModel, get_mesh_name, getMeshName)
FBIND_OBJECT_GETTER_STRING(LE3StaticModel, get_material_name, getMaterialName)
FBIND_OBJECT_SETTER_STRING(LE3StaticModel, set_mesh_name, setMeshName)
FBIND_OBJECT_SETTER_STRING(LE3StaticModel, set_material_name, setMaterialName)
LIB(LE3StaticModel, 
    get_mesh_name, 
    get_material_name,
    set_mesh_name,
    set_material_name
)


FBIND_OBJECT_GETTER_STRING(LE3SkeletalModel, get_mesh_name, getMeshName)
FBIND_OBJECT_GETTER_STRING(LE3SkeletalModel, get_material_name, getMaterialName)
FBIND_OBJECT_SETTER_STRING(LE3SkeletalModel, set_mesh_name, setMeshName)
FBIND_OBJECT_SETTER_STRING(LE3SkeletalModel, set_material_name, setMaterialName)

FBIND_OBJECT_GETTER_STRING(LE3SkeletalModel, get_current_animation, getCurrentAnimation)
FBIND_OBJECT_SETTER_STRING(LE3SkeletalModel, set_current_animation, setCurrentAnimation)
FBIND_OBJECT_GETTER_BOOL(LE3SkeletalModel, is_animation_playing, isAnimationPlaying)
FBIND_OBJECT_SETTER_BOOL(LE3SkeletalModel, set_animation_playing, setAnimationPlaying)
FBIND(LE3SkeletalModel, reset_animation)
    GET_UDATA_OBJECT(self, LE3SkeletalModel)
    self->resetAnimation();
FEND()

LIB(LE3SkeletalModel, 
    get_mesh_name, set_mesh_name,
    get_material_name, set_material_name,

    get_current_animation, set_current_animation,
    is_animation_playing, set_animation_playing,
    reset_animation,
)