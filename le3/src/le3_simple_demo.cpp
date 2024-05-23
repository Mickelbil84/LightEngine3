#include "le3_simple_demo.h"
using namespace le3;

#include "le3_engine_systems.h"

void LE3SimpleDemo::init() {
    LE3GetSceneManager().createScene("scene", m_engineState);

    LE3GetSceneManager().getActiveScene()->init(m_engineState.getWindowWidth(), m_engineState.getWindowHeight());
    LE3GetAssetManager().addShaderFromFile("S_default", "/engine/shaders/blinn_phong/blinn_phong.vs", "/engine/shaders/blinn_phong/blinn_phong.fs");
    LE3GetAssetManager().addMaterial("M_default", "S_default");

    LE3GetSceneManager().getActiveScene()->addFreeCamera("camera");
    LE3GetSceneManager().getActiveScene()->getMainCamera()->setAspectRatio(m_engineState.getAspectRatio());
    LE3GetSceneManager().getActiveScene()->getMainCamera()->getTransform().setPosition(m_initialPosition);
    
    LE3GetSceneManager().getActiveScene()->addDirectionalLight("sun");
    std::dynamic_pointer_cast<LE3DirectionalLight>(LE3GetSceneManager().getActiveScene()->getObject("sun"))->getTransform().setRotationRPY(0.785, 0.785, 0.785);

    LE3GetSceneManager().getActiveScene()->drawDebug = [this]() { this->renderDebug(); };
}

void LE3SimpleDemo::update(float deltaTime) {
    // Setup FPS camera
    LE3GetSceneManager().getActiveScene()->getMainCamera()->addPitchYaw(m_sensitivity * m_cameraRotation.y, -m_sensitivity * m_cameraRotation.x);
    LE3GetSceneManager().getActiveScene()->getMainCamera()->moveForward(deltaTime * m_walkSpeed * m_cameraVelocity.y);
    LE3GetSceneManager().getActiveScene()->getMainCamera()->moveRight(deltaTime * m_walkSpeed * m_cameraVelocity.x);
    LE3GetSceneManager().getActiveScene()->getMainCamera()->moveUp(deltaTime * m_walkSpeed * m_cameraVelocity.z);

    LE3GetSceneManager().updateScenes(deltaTime);
}

void LE3SimpleDemo::render() {
    LE3GetSceneManager().getActiveScene()->draw();
}

void LE3SimpleDemo::renderDebug() {}

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