#include "le3_simple_demo.h"
using namespace le3;

#include "le3_engine_systems.h"

void LE3SimpleDemo::init() {
    m_scene.init(m_engineState.getWindowWidth(), m_engineState.getWindowHeight());
    LE3GetAssetManager().addShaderFromFile("S_default", "/engine/shaders/blinn_phong/blinn_phong.vs", "/engine/shaders/blinn_phong/blinn_phong.fs");
    LE3GetAssetManager().addMaterial("M_default", "S_default");

    m_scene.addFreeCamera("camera");
    m_scene.getMainCamera()->setAspectRatio(m_engineState.getAspectRatio());
    m_scene.getMainCamera()->getTransform().setPosition(m_initialPosition);
    
    m_scene.addDirectionalLight("sun");
    std::dynamic_pointer_cast<LE3DirectionalLight>(m_scene.getObject("sun"))->getTransform().setRotationRPY(0.785, 0.785, 0.785);
}

void LE3SimpleDemo::update(float deltaTime) {
    // Setup FPS camera
    m_scene.getMainCamera()->addPitchYaw(m_sensitivity * m_cameraRotation.y, -m_sensitivity * m_cameraRotation.x);
    m_scene.getMainCamera()->moveForward(deltaTime * m_walkSpeed * m_cameraVelocity.y);
    m_scene.getMainCamera()->moveRight(deltaTime * m_walkSpeed * m_cameraVelocity.x);
    m_scene.getMainCamera()->moveUp(deltaTime * m_walkSpeed * m_cameraVelocity.z);

    m_scene.update(deltaTime);
}

void LE3SimpleDemo::render() {
    m_scene.draw();
}

void LE3SimpleDemo::handleInput(LE3Input input) {
    if (input.keys["KEY_ESCAPE"]) m_engineState.notifyWantsQuit();

    if (input.isKeyDownEvent("KEY_F")) m_engineState.notifyWantsRelativeMOuse(!m_engineState.isRelativeMouse());

    ////////////////////////
    // Camera Movement
    ////////////////////////
    m_cameraVelocity = glm::vec3();
    m_cameraRotation = glm::vec3();
    if (input.bLeftMouseDown || m_engineState.isRelativeMouse()) {
        if (input.keys["KEY_W"]) m_cameraVelocity.y = 1.f;
        else if (input.keys["KEY_S"]) m_cameraVelocity.y = -1.f;
        else m_cameraVelocity.y = 0.f;

        if (input.keys["KEY_D"]) m_cameraVelocity.x = 1.f;
        else if (input.keys["KEY_A"]) m_cameraVelocity.x = -1.f;
        else m_cameraVelocity.x = 0.f;

        if (input.keys["KEY_E"]) m_cameraVelocity.z = 1.f;
        else if (input.keys["KEY_Q"]) m_cameraVelocity.z = -1.f;
        else m_cameraVelocity.z = 0.f;

        m_cameraRotation.x = (float)input.xrel;
        m_cameraRotation.y = -(float)input.yrel;
    }
}