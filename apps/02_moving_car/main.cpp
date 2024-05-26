#include <le3.h>
using namespace le3;

#include <fmt/core.h>

#include <glm/gtx/string_cast.hpp>

class Demo02_MovingCar : public LE3GameLogic {
public:
    LE3Scene m_scene;
    glm::vec3 cameraVelocity, cameraRotation;

    // Gui panel info
    float orbitOffset = 3.f;


    float walkSpeed = 2.2f, sensitivity = 0.005f;

    void init() {
        LE3GetDatFileSystem().addArchive("demos", "demos.dat");

        LE3GetSceneManager().createScene("scene", m_engineState);
        LE3GetActiveScene()->init(m_engineState.getWindowWidth(), m_engineState.getWindowHeight());

        /////////////////

        LE3GetAssetManager().addShaderFromFile(
            "hello_opengl",
            "/demos/shaders/moving_car/moving_car.vs",
            "/demos/shaders/moving_car/moving_car.fs"
        );
        LE3GetAssetManager().addMaterial("default", "hello_opengl");

        LE3GetAssetManager().addStaticMesh("carBody",  "/demos/models/cars/Car Body.fbx");
        LE3GetAssetManager().addStaticMesh("carWheel",  "/demos/models/cars/Car Wheel.fbx");

        /////////////////

        LE3GetActiveScene()->addEmptyObject("player");
        LE3GetActiveScene()->getObject("player")->getTransform().setPosition(glm::vec3(0.f, 0.f, 0.f));

        LE3GetActiveScene()->addFreeCamera("cameraFree", "player");
        LE3GetActiveScene()->getMainCamera()->setAspectRatio(m_engineState.getAspectRatio());
        LE3GetActiveScene()->getMainCamera()->getTransform().setPosition(glm::vec3(.0f, 0.5f, 3.f));

        LE3GetActiveScene()->addOrbitCamera("cameraOrbit", "player");
        std::dynamic_pointer_cast<LE3OrbitCamera>(LE3GetActiveScene()->getObject("cameraOrbit"))->setAspectRatio(m_engineState.getAspectRatio());
        std::dynamic_pointer_cast<LE3OrbitCamera>(LE3GetActiveScene()->getObject("cameraOrbit"))->setOffset(orbitOffset);
        
        LE3GetActiveScene()->addBox("cube", "default", glm::vec3(0.f, -0.1f, 0.f), glm::vec3(50.f, 0.1f, 50.f));

        for (int i = 0; i < 10; i++) {
            LE3GetActiveScene()->addBox(fmt::format("block{}", 2 * i), "default", glm::vec3(-2.f + i, 0.5f, 2.f), glm::vec3(.5f));
            LE3GetActiveScene()->addBox(fmt::format("block{}", 2 * i + 1), "default", glm::vec3(-2.f + i, 0.5f, -2.f), glm::vec3(.5f));
        }

        LE3GetActiveScene()->addEmptyObject("car");
        LE3GetActiveScene()->getObject("car")->getTransform().setScale(2.5f);

        LE3GetActiveScene()->addStaticModel("carBody", "carBody", "default", "car");
        LE3GetActiveScene()->getObject("carBody")->getTransform().setRotationRPY(-3.14159265f / 2.f, 0.f, -3.14159265f / 2.f);
        LE3GetActiveScene()->getObject("carBody")->getTransform().setScale(0.3f);
        LE3GetActiveScene()->getObject("carBody")->getTransform().setPosition(glm::vec3(-2.06f * 0.3f, 0.f, 0.f));

        LE3GetActiveScene()->getObject("cameraOrbit")->reparent(LE3GetActiveScene()->getObject("car"));
        // std::dynamic_pointer_cast<LE3OrbitCamera>(LE3GetActiveScene()->getObject("cameraOrbit"))->setOrigin(glm::vec3(3.f, 0.f, 0.f));

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
    void update(float deltaTime) {
        updateGUI();

        // Setup FPS camera
        LE3GetActiveScene()->getMainCamera()->addPitchYaw(sensitivity * cameraRotation.y, -sensitivity * cameraRotation.x);
        LE3GetActiveScene()->getMainCamera()->moveForward(deltaTime * walkSpeed * cameraVelocity.y);
        LE3GetActiveScene()->getMainCamera()->moveRight(deltaTime * walkSpeed * cameraVelocity.x);
        LE3GetActiveScene()->getMainCamera()->moveUp(deltaTime * walkSpeed * cameraVelocity.z);

        std::dynamic_pointer_cast<LE3OrbitCamera>(LE3GetActiveScene()->getObject("cameraOrbit"))->setOffset(orbitOffset);

        // Move car forward
        glm::vec3 carPos = LE3GetActiveScene()->getObject("car")->getTransform().getPosition();
        carPos.x += -1.f * deltaTime;
        if (carPos.x < -3.f) carPos.x = 3.f;
        LE3GetActiveScene()->getObject("car")->getTransform().setPosition(carPos);
        
        for (int i = 1; i <= 4; i++)
            LE3GetActiveScene()->getObject(fmt::format("wheel{}", i))->getTransform().addRotationZ(1.9f * deltaTime);

        // Update scene
        LE3GetActiveScene()->update(deltaTime);  
    }

    void updateGUI() {
        ImGui::Begin("Demo 02: Moving Car");

        if (ImGui::CollapsingHeader("Camera Control", ImGuiTreeNodeFlags_DefaultOpen)) {
            if (ImGui::Button("Set FPS (Free) Camera")) {
                LE3GetActiveScene()->setMainCamera("cameraFree");
            }
            if (ImGui::Button("Set TPS (Orbit) Camera")) {
                LE3GetActiveScene()->setMainCamera("cameraOrbit");
            }
            ImGui::Text("Orbit Offset:");
            ImGui::SliderFloat("##orbitOffset", &orbitOffset, 0.f, 5.f);
            ImGui::Separator();
            ImGui::Text("Press F to toggle relative mouse.");

        }

        ImGui::End();
    }

    void render() {
        LE3GetActiveScene()->draw();
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
    LE3Application app(std::make_unique<Demo02_MovingCar>());
    app.run();
    return 0;
}