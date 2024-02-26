#include "le3_script_bindings.h"
#include "le3_engine_systems.h"
using namespace le3;

FBIND(LE3PointCloud, create)
    GET_UDATA_OBJECT(obj, LE3PointCloud)
    obj->create();
FEND()

FBIND(LE3PointCloud, add_point)
    GET_UDATA_OBJECT(obj, LE3PointCloud)
    GET_VEC3_(position)
    GET_VEC3_(normal)
    obj->addPoint(position, normal);
FEND()

FBIND_OBJECT_SETTER_NUMBER(LE3PointCloud, set_point_size, setPointSize)

LIB(LE3PointCloud,
    create, add_point, set_point_size
)