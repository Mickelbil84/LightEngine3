#include "scripting/le3_script_bindings.h"
#include "core/le3_engine_systems.h"
using namespace le3;

// Exact triangle-mesh contacts between named, posed meshes (see LE3PhysicsManager::addCollisionMesh)

// (name, datPath) -> triangles: appends a binary STL (metres) to mesh `name`
FBIND(LE3MeshCollision, add)
    GET_STRING(name)
    GET_STRING(path)
    LE3DatBuffer buffer = LE3GetDatFileSystem().getFileContent(path);
    uint32_t n = 0;
    if (buffer.data.size() >= 84) memcpy(&n, buffer.data.data() + 80, 4);
    if (buffer.data.size() < 84 + (size_t)n * 50) n = 0;
    std::vector<glm::vec3> triangles(3 * n);
    for (uint32_t i = 0; i < n; i++) memcpy(&triangles[3 * i], buffer.data.data() + 84 + i * 50 + 12, 36);
    LE3GetPhysicsManager().addCollisionMesh(name, triangles);
    PUSH_NUMBER(n)
FEND()

// (name, px, py, pz, qw, qx, qy, qz): world pose of the mesh
FBIND(LE3MeshCollision, set_pose)
    GET_STRING(name)
    GET_NUMBER(px)
    GET_NUMBER(py)
    GET_NUMBER(pz)
    GET_NUMBER(qw)
    GET_NUMBER(qx)
    GET_NUMBER(qy)
    GET_NUMBER(qz)
    LE3GetPhysicsManager().setCollisionMeshPose(name, glm::dvec3(px, py, pz), glm::dquat(qw, qx, qy, qz));
FEND()

// (nameA, nameB): never report this pair
FBIND(LE3MeshCollision, ignore)
    GET_STRING(nameA)
    GET_STRING(nameB)
    LE3GetPhysicsManager().ignoreCollisionMeshPair(nameA, nameB);
FEND()

// () -> {a1, b1, a2, b2, ...}: every pair of meshes whose surfaces touch or overlap
FBIND(LE3MeshCollision, pairs)
    PUSH_STRING_ARRAY(LE3GetPhysicsManager().getCollidingMeshPairs())
FEND()

LIB(LE3MeshCollision, add, set_pose, ignore, pairs)
