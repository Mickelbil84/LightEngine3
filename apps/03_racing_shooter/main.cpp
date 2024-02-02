#include <le3.h>
using namespace le3;

#include <fmt/core.h>
using fmt::print, fmt::format;

#include <glm/gtx/string_cast.hpp>

class Demo03_RacingShooter : public LE3GameLogic {
public:
    LE3Scene m_scene;
    glm::vec3 cameraVelocity, cameraRotation;

    // Gui panel info
    float orbitOffset = 3.f;
    float carSpeed = .0f;


    float walkSpeed = 2.2f, sensitivity = 0.005f;

    void init() {
        LE3GetDatFileSystem().addArchive("demos", "demos.dat");
        m_scene.init();
        m_scene.load("/demos/scripts/racing_shooter/scene.lua");

        /////////////////

        // m_scene.addEmptyObject("player");
        // m_scene.getObject("player")->getTransform().setPosition(glm::vec3(0.f, 0.f, 0.f));

        // m_scene.addFreeCamera("cameraFree", "player");
        // m_scene.getMainCamera()->setAspectRatio(m_engineState.getAspectRatio());
        // m_scene.getMainCamera()->getTransform().setPosition(glm::vec3(.0f, 0.5f, 3.f));

        // m_scene.addOrbitCamera("cameraOrbit", "player");
        // std::dynamic_pointer_cast<LE3OrbitCamera>(m_scene.getObject("cameraOrbit"))->setAspectRatio(m_engineState.getAspectRatio());
        // std::dynamic_pointer_cast<LE3OrbitCamera>(m_scene.getObject("cameraOrbit"))->setOffset(orbitOffset);
        
        // m_scene.addCube("cube", "M_default", glm::vec3(0.f, -0.1f, 0.f), glm::vec3(50.f, 0.1f, 50.f));

        // for (int i = 0; i < 10; i++) {
        //     m_scene.addCube(format("block{}", 2 * i), "M_default", glm::vec3(-2.f + i, 0.5f, 2.f), glm::vec3(.5f));
        //     m_scene.addCube(format("block{}", 2 * i + 1), "M_default", glm::vec3(-2.f + i, 0.5f, -2.f), glm::vec3(.5f));
        // }

        // m_scene.addEmptyObject("car");
        // m_scene.getObject("car")->getTransform().setScale(2.5f);

        // m_scene.addStaticModel("carBody", "SM_carBody", "M_carBody", "car");
        // m_scene.getObject("carBody")->getTransform().setRotationRPY(-3.14159265f / 2.f, 0.f, -3.14159265f / 2.f);
        // m_scene.getObject("carBody")->getTransform().setScale(0.3f);
        // m_scene.getObject("carBody")->getTransform().setPosition(glm::vec3(-2.06f * 0.3f, 0.f, 0.f));

        // m_scene.getObject("cameraOrbit")->reparent(m_scene.getObject("car"));
        // // std::dynamic_pointer_cast<LE3OrbitCamera>(m_scene.getObject("cameraOrbit"))->setOrigin(glm::vec3(3.f, 0.f, 0.f));

        // m_scene.addEmptyObject("wheelsFront", "car");
        // m_scene.getObject("wheelsFront")->getTransform().setPosition(glm::vec3(.285f -2.06f * 0.3f, 0.095f, 0.f));
        // m_scene.addEmptyObject("wheelsBack", "car");
        // m_scene.getObject("wheelsBack")->getTransform().setPosition(glm::vec3(1.035f -2.06f * 0.3f, 0.095f, 0.f));
        
        // m_scene.addStaticModel("wheel1", "SM_carWheel", "M_wheel", "wheelsFront");
        // m_scene.getObject("wheel1")->getTransform().setPosition(glm::vec3(0.f, 0.f, -.3f));
        // m_scene.getObject("wheel1")->getTransform().setScale(0.33f);
        // m_scene.getObject("wheel1")->getTransform().setRotationRPY(-3.14159265f / 2.f, 0.f, 3.14159265f / 2.f);

        // m_scene.addStaticModel("wheel2", "SM_carWheel", "M_wheel", "wheelsFront");
        // m_scene.getObject("wheel2")->getTransform().setPosition(glm::vec3(0.f, 0.f, .3f));
        // m_scene.getObject("wheel2")->getTransform().setScale(0.33f);
        // m_scene.getObject("wheel2")->getTransform().setRotationRPY(-3.14159265f / 2.f, 0.f, -3.14159265f / 2.f);

        // m_scene.addStaticModel("wheel3", "SM_carWheel", "M_wheel", "wheelsBack");
        // m_scene.getObject("wheel3")->getTransform().setPosition(glm::vec3(0.f, 0.f, -.3f));
        // m_scene.getObject("wheel3")->getTransform().setScale(0.33f);
        // m_scene.getObject("wheel3")->getTransform().setRotationRPY(-3.14159265f / 2.f, 0.f, 3.14159265f / 2.f);

        // m_scene.addStaticModel("wheel4", "SM_carWheel", "M_wheel", "wheelsBack");
        // m_scene.getObject("wheel4")->getTransform().setPosition(glm::vec3(0.f, 0.f, .3f));
        // m_scene.getObject("wheel4")->getTransform().setScale(0.33f);
        // m_scene.getObject("wheel4")->getTransform().setRotationRPY(-3.14159265f / 2.f, 0.f, -3.14159265f / 2.f);

    }
    void update(float deltaTime) {
        updateGUI();

        // Setup FPS camera
        m_scene.getMainCamera()->addPitchYaw(sensitivity * cameraRotation.y, -sensitivity * cameraRotation.x);
        m_scene.getMainCamera()->moveForward(deltaTime * walkSpeed * cameraVelocity.y);
        m_scene.getMainCamera()->moveRight(deltaTime * walkSpeed * cameraVelocity.x);
        m_scene.getMainCamera()->moveUp(deltaTime * walkSpeed * cameraVelocity.z);

        std::dynamic_pointer_cast<LE3OrbitCamera>(m_scene.getObject("cameraOrbit"))->setOffset(orbitOffset);

        // Move car forward
        // glm::vec3 carPos = m_scene.getObject("car")->getTransform().getPosition();
        // carPos.x += -1.f * deltaTime * carSpeed;
        // if (carPos.x < -3.f) carPos.x = 7.f;
        // m_scene.getObject("car")->getTransform().setPosition(carPos);
        
        // for (int i = 1; i <= 4; i++)
        //     m_scene.getObject(format("wheel{}", i))->getTransform().addRotationZ(1.9f * carSpeed * deltaTime);

        // Update scene
        m_scene.update(deltaTime);  
    }

    void updateGUI() {
        ImGui::Begin("Demo 03: Racing Shooter");

        if (ImGui::CollapsingHeader("Camera Control", ImGuiTreeNodeFlags_DefaultOpen)) {
            if (ImGui::Button("Set FPS (Free) Camera")) {
                m_scene.setMainCamera("cameraFree");
            }
            if (ImGui::Button("Set TPS (Orbit) Camera")) {
                m_scene.setMainCamera("cameraOrbit");
            }
            ImGui::Text("Orbit Offset:");
            ImGui::SliderFloat("##orbitOffset", &orbitOffset, 0.f, 5.f);
            ImGui::Separator();
            ImGui::Text("Press F to toggle relative mouse.");

        }
        if (ImGui::CollapsingHeader("Camera Control", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::Text("Car Speed:");
            ImGui::SliderFloat("##carSpeed", &carSpeed, 0.f, 3.f);
        }

        ImGui::End();
    }

    void render() {
        m_scene.getShader("S_default")->use();
        m_scene.getShader("S_default")->uniform("ambientLight.color", glm::vec3(1.f));
        m_scene.getShader("S_default")->uniform("ambientLight.intensity", 0.3f);

        m_scene.getShader("S_default")->uniform("directionalLights[0].color", glm::vec3(1.f));
        m_scene.getShader("S_default")->uniform("directionalLights[0].intensity", 1.3f);
        m_scene.getShader("S_default")->uniform("directionalLights[0].direction", glm::vec3(-1.f / sqrt(3.f), -1.f / sqrt(3.f), -1.f / sqrt(3.f)));
        m_scene.draw();
    }

    void handleInput(LE3Input input) {
        if (input.keys["KEY_ESCAPE"]) m_engineState.notifyWantsQuit();

        if (input.isKeyDownEvent("KEY_F")) m_engineState.notifyWantsRelativeMOuse(!m_engineState.isRelativeMouse());

        ////////////////////////
        // Camera Movement
        ////////////////////////
        cameraVelocity = glm::vec3();
        cameraRotation = glm::vec3();
        if (input.bLeftMouseDown || m_engineState.isRelativeMouse()) {
            if (input.keys["KEY_W"]) cameraVelocity.y = 1.f;
            else if (input.keys["KEY_S"]) cameraVelocity.y = -1.f;
            else cameraVelocity.y = 0.f;

            if (input.keys["KEY_D"]) cameraVelocity.x = 1.f;
            else if (input.keys["KEY_A"]) cameraVelocity.x = -1.f;
            else cameraVelocity.x = 0.f;

            if (input.keys["KEY_E"]) cameraVelocity.z = 1.f;
            else if (input.keys["KEY_Q"]) cameraVelocity.z = -1.f;
            else cameraVelocity.z = 0.f;

            cameraRotation.x = (float)input.xrel;
            cameraRotation.y = -(float)input.yrel;
        }
    }
};

int main() {
    LE3Application app(std::make_unique<Demo03_RacingShooter>());
    app.run();
    return 0;
}