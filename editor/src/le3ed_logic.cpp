#include "le3ed_logic.h"
using namespace le3;

#include <fmt/core.h>

LE3EditorLogic::LE3EditorLogic() :
        m_gui(m_engineState), 
        m_scenes(m_engineState) {
    m_pComponents.push_back(&m_gui);
    m_pComponents.push_back(&m_scenes);
}

void LE3EditorLogic::init() {
    LE3GetDatFileSystem().addArchive("editor", "editor.dat");
    // Init Subsystems;
    for (auto component : m_pComponents) component->init();

    // TEMP
    LE3GetDatFileSystem().addArchive("demos", "demos.dat");
    LE3GetAssetManager().addShaderFromFile(
            "hello_opengl",
            "/demos/shaders/moving_car/moving_car.vs",
            "/demos/shaders/moving_car/moving_car.fs"
        );
    LE3GetAssetManager().addMaterial("default", "hello_opengl");
    LE3GetAssetManager().addStaticMesh("carBody",  "/demos/models/cars/Car Body.fbx");
    LE3GetAssetManager().addStaticMesh("carWheel",  "/demos/models/cars/Car Wheel.fbx");

    LE3GetActiveScene()->addEmptyObject("car");
    LE3GetActiveScene()->getObject("car")->getTransform().setScale(2.5f);
    LE3GetActiveScene()->addStaticModel("carBody", "carBody", "default", "car");
    LE3GetActiveScene()->getObject("carBody")->getTransform().setRotationRPY(-3.14159265f / 2.f, 0.f, -3.14159265f / 2.f);
    LE3GetActiveScene()->getObject("carBody")->getTransform().setScale(0.3f);
    LE3GetActiveScene()->getObject("carBody")->getTransform().setPosition(glm::vec3(-2.06f * 0.3f, 0.f, 0.f));
    LE3GetActiveScene()->addEmptyObject("wheelsFront", "car");
    LE3GetActiveScene()->getObject("wheelsFront")->getTransform().setPosition(glm::vec3(.285f -2.06f * 0.3f, 0.095f, 0.f));
    LE3GetActiveScene()->addEmptyObject("wheelsBack", "car");
    LE3GetActiveScene()->getObject("wheelsBack")->getTransform().setPosition(glm::vec3(1.035f -2.06f * 0.3f, 0.095f, 0.f));
    LE3GetActiveScene()->addStaticModel("wheel1", "carWheel", "default", "wheelsFront");
    LE3GetActiveScene()->getObject("wheel1")->getTransform().setPosition(glm::vec3(0.f, 0.f, -.3f));
    LE3GetActiveScene()->getObject("wheel1")->getTransform().setScale(0.33f);
    LE3GetActiveScene()->getObject("wheel1")->getTransform().setRotationRPY(-3.14159265f / 2.f, 0.f, 3.14159265f / 2.f);
    LE3GetActiveScene()->addStaticModel("wheel2", "carWheel", "default", "wheelsFront");
    LE3GetActiveScene()->getObject("wheel2")->getTransform().setPosition(glm::vec3(0.f, 0.f, .3f));
    LE3GetActiveScene()->getObject("wheel2")->getTransform().setScale(0.33f);
    LE3GetActiveScene()->getObject("wheel2")->getTransform().setRotationRPY(-3.14159265f / 2.f, 0.f, -3.14159265f / 2.f);
    LE3GetActiveScene()->addStaticModel("wheel3", "carWheel", "default", "wheelsBack");
    LE3GetActiveScene()->getObject("wheel3")->getTransform().setPosition(glm::vec3(0.f, 0.f, -.3f));
    LE3GetActiveScene()->getObject("wheel3")->getTransform().setScale(0.33f);
    LE3GetActiveScene()->getObject("wheel3")->getTransform().setRotationRPY(-3.14159265f / 2.f, 0.f, 3.14159265f / 2.f);
    LE3GetActiveScene()->addStaticModel("wheel4", "carWheel", "default", "wheelsBack");
    LE3GetActiveScene()->getObject("wheel4")->getTransform().setPosition(glm::vec3(0.f, 0.f, .3f));
    LE3GetActiveScene()->getObject("wheel4")->getTransform().setScale(0.33f);
    LE3GetActiveScene()->getObject("wheel4")->getTransform().setRotationRPY(-3.14159265f / 2.f, 0.f, -3.14159265f / 2.f);
}
void LE3EditorLogic::update(float deltaTime) {
    for (auto component : m_pComponents) component->update(deltaTime);
}
void LE3EditorLogic::render() {
    for (auto component : m_pComponents) component->render();
}
void LE3EditorLogic::renderDebug() {
    for (auto component : m_pComponents) component->renderDebug();
}
void LE3EditorLogic::handleInput(LE3Input input) {
    for (auto component : m_pComponents) component->handleInput(input);
}
