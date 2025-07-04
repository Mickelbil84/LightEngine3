#include "scripting/le3_script_bindings.h"
#include "core/le3_engine_systems.h"
using namespace le3;

FBIND_OBJECT_GETTER_VEC3(LE3Box, get_box_position, getBoxPosition)
FBIND_OBJECT_GETTER_VEC3(LE3Box, get_box_extent, getBoxExtent)
LIB(LE3Box, 
    get_box_position, 
    get_box_extent
)

FBIND_OBJECT_GETTER_NUMBER(LE3Cylinder, get_x0, getX0)
FBIND_OBJECT_GETTER_NUMBER(LE3Cylinder, get_y0, getY0)
FBIND_OBJECT_GETTER_NUMBER(LE3Cylinder, get_z0, getZ0)
FBIND_OBJECT_GETTER_NUMBER(LE3Cylinder, get_radius, getRadius)
FBIND_OBJECT_GETTER_NUMBER(LE3Cylinder, get_height, getHeight)
FBIND_OBJECT_GETTER_NUMBER(LE3Cylinder, get_resolution, getResolution)
FBIND_OBJECT_GETTER_BOOL(LE3Cylinder, get_with_caps, getWithCaps)
LIB(LE3Cylinder,
    get_x0, get_y0, get_z0,
    get_radius,
    get_height,
    get_resolution,
    get_with_caps
)

FBIND_OBJECT_GETTER_NUMBER(LE3Cone, get_x0, getX0)
FBIND_OBJECT_GETTER_NUMBER(LE3Cone, get_y0, getY0)
FBIND_OBJECT_GETTER_NUMBER(LE3Cone, get_z0, getZ0)
FBIND_OBJECT_GETTER_NUMBER(LE3Cone, get_radius, getRadius)
FBIND_OBJECT_GETTER_NUMBER(LE3Cone, get_height, getHeight)
FBIND_OBJECT_GETTER_NUMBER(LE3Cone, get_resolution, getResolution)
FBIND_OBJECT_GETTER_BOOL(LE3Cone, get_with_caps, getWithCaps)
LIB(LE3Cone,
    get_x0, get_y0, get_z0,
    get_radius,
    get_height,
    get_resolution,
    get_with_caps
)

FBIND_OBJECT_GETTER_NUMBER(LE3Torus, get_x0, getX0)
FBIND_OBJECT_GETTER_NUMBER(LE3Torus, get_y0, getY0)
FBIND_OBJECT_GETTER_NUMBER(LE3Torus, get_z0, getZ0)
FBIND_OBJECT_GETTER_NUMBER(LE3Torus, get_major_radius, getMajorRadius)
FBIND_OBJECT_GETTER_NUMBER(LE3Torus, get_minor_radius, getMinorRadius)
FBIND_OBJECT_GETTER_NUMBER(LE3Torus, get_resolution, getResolution)
LIB(LE3Torus,
    get_x0, get_y0, get_z0,
    get_major_radius,
    get_minor_radius,
    get_resolution
)

FBIND_OBJECT_GETTER_NUMBER(LE3Sphere, get_x0, getX0)
FBIND_OBJECT_GETTER_NUMBER(LE3Sphere, get_y0, getY0)
FBIND_OBJECT_GETTER_NUMBER(LE3Sphere, get_z0, getZ0)
FBIND_OBJECT_GETTER_NUMBER(LE3Sphere, get_radius, getRadius)
FBIND_OBJECT_GETTER_NUMBER(LE3Sphere, get_resolution, getResolution)
LIB(LE3Sphere,
    get_x0, get_y0, get_z0,
    get_radius,
    get_resolution
)