#include "physics/le3_physics_manager.h"
#include "core/le3_engine_systems.h"
using namespace le3;

#include <bullet/btBulletDynamicsCommon.h>
#include <bullet/BulletCollision/NarrowPhaseCollision/btPersistentManifold.h>

struct LE3PhysicsManager::_LE3PhysicsManager_Internal {
    _LE3PhysicsManager_Internal() {}
    std::unique_ptr<btDefaultCollisionConfiguration> m_collisionConfiguration;
    std::unique_ptr<btCollisionDispatcher> m_dispatcher;
    std::unique_ptr<btBroadphaseInterface> m_overlappingPairCache;
    std::unique_ptr<btSequentialImpulseConstraintSolver> m_solver;
    std::unique_ptr<btDiscreteDynamicsWorld> m_dynamicsWorld;

    std::map<std::string, btRigidBody*> m_rigidBodies;  // Each object/component should only have one rigid body
    std::map<btRigidBody*, std::string> m_ownerNames;    // Reverse map: rigid body -> object name
};

LE3PhysicsManager::LE3PhysicsManager() : m_pInternal(std::make_shared<_LE3PhysicsManager_Internal>()) {
    reset();
}

void LE3PhysicsManager::reset() {
    // Delete previous references in a safe order
    m_pInternal->m_dynamicsWorld = nullptr;
    m_pInternal->m_dispatcher = nullptr;
    m_pInternal->m_collisionConfiguration = nullptr;
    m_pInternal->m_overlappingPairCache = nullptr;
    m_pInternal->m_solver = nullptr;

    m_pInternal->m_collisionConfiguration = std::make_unique<btDefaultCollisionConfiguration>();
    m_pInternal->m_dispatcher = std::make_unique<btCollisionDispatcher>(m_pInternal->m_collisionConfiguration.get());
    m_pInternal->m_overlappingPairCache = std::make_unique<btDbvtBroadphase>();
    m_pInternal->m_solver = std::make_unique<btSequentialImpulseConstraintSolver>();

    m_pInternal->m_dynamicsWorld = std::make_unique<btDiscreteDynamicsWorld>(
        m_pInternal->m_dispatcher.get(), m_pInternal->m_overlappingPairCache.get(), m_pInternal->m_solver.get(), m_pInternal->m_collisionConfiguration.get());
    m_pInternal->m_dynamicsWorld->setGravity(btVector3(0, -10, 0));

    m_pInternal->m_rigidBodies.clear();
    m_pInternal->m_ownerNames.clear();
}

void LE3PhysicsManager::update(float deltaTime) {
    if (!m_bPhysicsEnabled) return;
    m_pInternal->m_dynamicsWorld->stepSimulation(deltaTime);
    checkCollisions();
}

void LE3PhysicsManager::registerComponent(std::string name, LE3PhysicsComponent& component) {
    clearComponent(name);
    btRigidBody* rb = (btRigidBody*)component.getRigidBody();
    m_pInternal->m_dynamicsWorld->addRigidBody(rb);
    m_pInternal->m_rigidBodies[name] = rb;
    m_pInternal->m_ownerNames[rb] = component.getOwnerName();
}

void LE3PhysicsManager::clearComponent(std::string name) {
    if (m_pInternal->m_rigidBodies.find(name) != m_pInternal->m_rigidBodies.end()) {
        m_pInternal->m_ownerNames.erase(m_pInternal->m_rigidBodies[name]);
        m_pInternal->m_dynamicsWorld->removeRigidBody(m_pInternal->m_rigidBodies[name]);
        m_pInternal->m_rigidBodies.erase(name);
    }
}

void LE3PhysicsManager::checkCollisions() {
    lua_State* L = LE3GetScriptSystem().getLuaState();
    btCollisionDispatcher* dispatcher = m_pInternal->m_dispatcher.get();
    int numManifolds = dispatcher->getNumManifolds();

    for (int i = 0; i < numManifolds; i++) {
        btPersistentManifold* manifold = dispatcher->getManifoldByIndexInternal(i);
        if (manifold->getNumContacts() <= 0) continue;

        const btCollisionObject* objA = manifold->getBody0();
        const btCollisionObject* objB = manifold->getBody1();

        auto itA = m_pInternal->m_ownerNames.find((btRigidBody*)objA);
        auto itB = m_pInternal->m_ownerNames.find((btRigidBody*)objB);
        if (itA == m_pInternal->m_ownerNames.end() || itB == m_pInternal->m_ownerNames.end()) continue;
        if (itA->second.empty() || itB->second.empty()) continue;

        // Use the deepest contact point
        btManifoldPoint& pt = manifold->getContactPoint(0);
        btVector3 posA = pt.getPositionWorldOnA();
        btVector3 normal = pt.m_normalWorldOnB;
        float impulse = pt.getAppliedImpulse();

        // Build data table once, store in registry for reuse
        lua_newtable(L);
        lua_pushstring(L, itA->second.c_str()); lua_setfield(L, -2, "objectA");
        lua_pushstring(L, itB->second.c_str()); lua_setfield(L, -2, "objectB");
        lua_pushnumber(L, posA.x()); lua_setfield(L, -2, "contactX");
        lua_pushnumber(L, posA.y()); lua_setfield(L, -2, "contactY");
        lua_pushnumber(L, posA.z()); lua_setfield(L, -2, "contactZ");
        lua_pushnumber(L, normal.x()); lua_setfield(L, -2, "normalX");
        lua_pushnumber(L, normal.y()); lua_setfield(L, -2, "normalY");
        lua_pushnumber(L, normal.z()); lua_setfield(L, -2, "normalZ");
        lua_pushnumber(L, impulse); lua_setfield(L, -2, "impulse");
        int dataRef = luaL_ref(L, LUA_REGISTRYINDEX);

        // Fire EVT_ON_COLLISION__{objectA}
        std::string eventA = "EVT_ON_COLLISION__" + itA->second;
        lua_getglobal(L, "LE3EventManager");
        lua_getfield(L, -1, "notify");
        lua_remove(L, -2);
        lua_pushstring(L, eventA.c_str());
        lua_rawgeti(L, LUA_REGISTRYINDEX, dataRef);
        if (lua_pcall(L, 2, 0, 0) != 0) lua_pop(L, 1);

        // Fire EVT_ON_COLLISION__{objectB}
        std::string eventB = "EVT_ON_COLLISION__" + itB->second;
        lua_getglobal(L, "LE3EventManager");
        lua_getfield(L, -1, "notify");
        lua_remove(L, -2);
        lua_pushstring(L, eventB.c_str());
        lua_rawgeti(L, LUA_REGISTRYINDEX, dataRef);
        if (lua_pcall(L, 2, 0, 0) != 0) lua_pop(L, 1);

        luaL_unref(L, LUA_REGISTRYINDEX, dataRef);
    }
}

bool LE3PhysicsManager::rayTest(glm::vec3 from, glm::vec3 to) {
    if (!m_bPhysicsEnabled) return false;

    btVector3 btFrom(from.x, from.y, from.z);
    btVector3 btTo(to.x, to.y, to.z);
    btCollisionWorld::ClosestRayResultCallback rayCallback(btFrom, btTo);
    m_pInternal->m_dynamicsWorld->rayTest(btFrom, btTo, rayCallback);

    return rayCallback.hasHit();
}
