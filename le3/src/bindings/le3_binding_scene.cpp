#include "le3_script_bindings.h"
#include "le3_engine_systems.h"
using namespace le3;


FBIND(LE3Scene, add_empty_object)
    GET_UDATA(scene, LE3Scene)
    GET_STRING(name)
    scene->addEmptyObject(name);
FEND()

FBIND(LE3Scene, add_box)
    GET_UDATA(scene, LE3Scene)
    GET_STRING(name)
    GET_STRING(materialName)
    GET_VEC3(position)
    GET_NUMBER(extentX) 
    GET_NUMBER(extentY) 
    GET_NUMBER(extentZ)
    glm::vec3 extent(extentX, extentY, extentZ);
    scene->addBox(name, materialName, position, extent);
FEND()

FBIND(LE3Scene, add_cylinder)
    GET_UDATA(scene, LE3Scene)
    GET_STRING(name)
    GET_STRING(materialName)
    GET_VEC3(position)
    GET_NUMBER(radius)
    GET_NUMBER(height)
    GET_NUMBER(resolution)
    GET_BOOL(withCaps)
    scene->addCylinder(name, materialName, position, radius, height, resolution, withCaps);
FEND()

FBIND(LE3Scene, add_cone)
    GET_UDATA(scene, LE3Scene)
    GET_STRING(name)
    GET_STRING(materialName)
    GET_VEC3(position)
    GET_NUMBER(radius)
    GET_NUMBER(height)
    GET_NUMBER(resolution)
    GET_BOOL(withCaps)
    scene->addCone(name, materialName, position, radius, height, resolution, withCaps);
FEND()

FBIND(LE3Scene, add_static_model)
    GET_UDATA(scene, LE3Scene)
    GET_STRING(name)
    GET_STRING(meshName)
    GET_STRING(materialName)
    scene->addStaticModel(name, meshName, materialName);
FEND()

FBIND(LE3Scene, add_skeletal_model)
    GET_UDATA(scene, LE3Scene)
    GET_STRING(name)
    GET_STRING(meshName)
    GET_STRING(materialName)
    scene->addSkeletalModel(name, meshName, materialName);
FEND()

FBIND(LE3Scene, add_point_cloud)
    GET_UDATA(scene, LE3Scene)
    GET_STRING(name)
    GET_STRING(materialName)
    scene->addPointCloud(name, materialName);
FEND()

FBIND(LE3Scene, add_script_object)
    GET_UDATA(scene, LE3Scene)
    GET_STRING(name)
    GET_STRING(classname)
    scene->addScriptObject(name, classname);
FEND()

FBIND(LE3Scene, add_free_camera)
    GET_UDATA(scene, LE3Scene)
    GET_STRING(name)
    scene->addFreeCamera(name);
FEND()

FBIND(LE3Scene, add_orbit_camera)
    GET_UDATA(scene, LE3Scene)
    GET_STRING(name)
    scene->addOrbitCamera(name);
FEND()

FBIND(LE3Scene, set_main_camera)
    GET_UDATA(scene, LE3Scene)
    GET_STRING(camera)
    scene->setMainCamera(camera);
FEND()

FBIND(LE3Scene, add_ambient_light)
    GET_UDATA(scene, LE3Scene)
    GET_STRING(name)
    scene->addAmbientLight(name);
FEND()

FBIND(LE3Scene, add_directional_light)
    GET_UDATA(scene, LE3Scene)
    GET_STRING(name)
    scene->addDirectionalLight(name);
FEND()

FBIND(LE3Scene, add_point_light)
    GET_UDATA(scene, LE3Scene)
    GET_STRING(name)
    scene->addPointLight(name);
FEND()

FBIND(LE3Scene, add_spot_light)
    GET_UDATA(scene, LE3Scene)
    GET_STRING(name)
    scene->addSpotLight(name);
FEND()

// --------

FBIND(LE3Scene, reparent)
    GET_UDATA(scene, LE3Scene)
    GET_STRING(child)
    GET_STRING(parent)
    scene->getObject(child)->reparent(scene->getObject(parent));
FEND()

FBIND(LE3Scene, get_object)
    GET_UDATA(scene, LE3Scene)
    GET_STRING(name)
    LE3ObjectPtr& obj = scene->getObject(name);
    PUSH_UDATA(&obj, LE3ObjectPtr);
FEND()

FBIND_GETTER_VEC3(LE3Scene, get_background_color, getBackgroundColor)
FBIND_SETTER_VEC3(LE3Scene, set_background_color, setBackgroundColor)
FBIND_SETTER_BOOL(LE3Scene, set_culling, setCulling)


// --------

LIB(LE3Scene,
    add_empty_object, add_script_object,
    add_box, add_cylinder, add_cone,
    add_static_model, add_skeletal_model, add_point_cloud,
    add_free_camera, add_orbit_camera, set_main_camera,
    add_ambient_light, add_directional_light, add_point_light, add_spot_light,
    reparent, get_object,
    get_background_color, set_background_color,
    set_culling
)
