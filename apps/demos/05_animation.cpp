#include <le3_application.h>
#include <le3_shader.h>
#include <le3_mesh.h>
#include <le3_primitives.h>
#include <le3_camera.h>
#include <le3_texture.h>
#include <le3_material.h>
#include <le3_scene_root.h>
#include <le3_static_mesh.h>
#include <le3_asset_manager.h>
#include <le3_scene_manager.h>

#include <le3_engine_sprites.h>

#include <vector>
#include <string>
#include <glm/gtx/transform.hpp>

#include <fmt/core.h>
using fmt::print;

class LE3Demo : public LE3Application
{
public:
    LE3Demo(LE3ApplicationSettings settings) : LE3Application(settings)
    {
        defaultWidth = settings.windowWidth, defaultHeight = settings.windowHeight;
    }

    double runTime = 0.0;

    LE3SceneManager scene;

    glm::vec2 cameraVelocity;
    glm::vec2 cameraRotation;
    float walkSpeed, sensitivity;

    glm::mat4 viewMatrix, projMatrix;

    int defaultWidth, defaultHeight;

    virtual int Init() 
    {
        // ---------------------------
        //   Load Assets
        // ---------------------------
        scene.applicationSettings = &this->m_settings;
        scene.Init();

        scene.assets.AddShaderPath("S_blinn_phong", 
            "resources/shaders/blinn_phong/blinn_phong.vs",
            "resources/shaders/blinn_phong/blinn_phong.fs");

        scene.assets.AddTexturePath("T_DIF_soldier", "resources/textures/soldier/T_DIF_soldier.png");
        scene.assets.AddTexturePath("T_SPC_soldier", "resources/textures/soldier/T_SPC_soldier.png");
        scene.assets.AddTexturePath("T_NRM_soldier", "resources/textures/soldier/T_NRM_soldier.png");
        // scene.assets.AddTexturePath("T_DIF_soldier", "resources/textures/vampire/Vampire_diffuse.png");
        // scene.assets.AddTexturePath("T_SPC_soldier", "resources/textures/vampire/Vampire_specular.png");
        // scene.assets.AddTexturePath("T_NRM_soldier", "resources/textures/vampire/Vampire_normal.png");

        scene.assets.AddSkeletalMeshPath("SK_soldier", "resources/models/SK_soldier.fbx");
        // scene.assets.AddSkeletalMeshPath("SK_soldier", "resources/models/dancing_vampire.dae");
        // scene.assets.AddSkeletalMeshPath("SK_soldier", "resources/models/Idle.fbx");

        scene.assets.CreateMaterial("M_soldier", "S_blinn_phong");
        scene.assets.GetMaterial("M_soldier")->SetDiffuseTexture(scene.assets.GetTexture("T_DIF_soldier"));
        scene.assets.GetMaterial("M_soldier")->SetSpecularTexture(scene.assets.GetTexture("T_SPC_soldier"));
        scene.assets.GetMaterial("M_soldier")->SetNormalTexture(scene.assets.GetTexture("T_NRM_soldier"));
        scene.assets.GetMaterial("M_soldier")->bUseDiffuseTexture = true;
        scene.assets.GetMaterial("M_soldier")->bUseSpecularTexture = true;
        scene.assets.GetMaterial("M_soldier")->bUseNormalTexture = true;
        scene.assets.GetMaterial("M_soldier")->specularIntensity = .6f;
        scene.assets.GetMaterial("M_soldier")->shininess = 128.f;

        scene.assets.CreateMaterial("M_floor", "S_blinn_phong");
        scene.assets.GetMaterial("M_floor")->specularIntensity = .0f;
        scene.assets.GetMaterial("M_floor")->shininess = 128.f;

        scene.AddSkeletalMesh("soldier", "SK_soldier", "M_soldier", .01f);
        scene.GetObject("soldier")->SetPositionZ(-4.f);


        scene.AddAmbientLight(glm::vec3(0.9f, 0.4f, 0.1f), 0.05f);
        // scene.AddDirectionalLight("directional_light", glm::vec3(1.f), 1.3f);
        // scene.GetObject("directional_light")->SetRotationX(1.57f);
        scene.AddDirectionalLight("directional_light1", glm::vec3(1.f), .3f);
        scene.GetObject("directional_light1")->SetRotationX(-1.57f);

        scene.AddSpotLight("spot_light", glm::vec3(.9f, 1.f, 1.f), 0.6f);
        scene.GetObject("spot_light")->SetPosition(glm::vec3(0.f, 4.8f, 2.f));
        scene.GetObject("spot_light")->SetRotationX(0.7f);
        scene.lightManager.EnableShadows(std::dynamic_pointer_cast<LE3SpotLight>(scene.GetObject("spot_light")));

        scene.assets.AddMeshPath("floor", "$BOX_0_0_0_20.000000_0.0240000_20.000000_");
        scene.AddStaticMesh("floor", "floor", "M_floor");

        
        // Camera
        scene.AddFPSCamera();
        LE3VisualDebug::Init(scene.GetCamera().get());

        // ---------------------------
        //   Misc
        // ---------------------------
        
        scene.GetCamera()->SetPosition(glm::vec3(0.f, 1.6f, 0.f));
        scene.GetCamera()->SetAspectRatio((float)m_settings.windowWidth / (float)m_settings.windowHeight);
        
        walkSpeed = 2.2f;
        sensitivity = 0.005f;

        UpdateWindowTitle("LightEngine3 - (04) Lighting");

        return 0;
    }

    virtual void HandleInput(LE3Input input) 
    { 

        if (input.keyboard[SDL_SCANCODE_ESCAPE])
            m_bShouldRun = false;
        
        ////////////////////////
        // Camera Movement
        ////////////////////////
        if (input.keyboard[SDL_SCANCODE_W])
            cameraVelocity.y = 1.f;
        else if (input.keyboard[SDL_SCANCODE_S])
            cameraVelocity.y = -1.f;
        else
            cameraVelocity.y = 0.f;

        if (input.keyboard[SDL_SCANCODE_D])
            cameraVelocity.x = 1.f;
        else if (input.keyboard[SDL_SCANCODE_A])
            cameraVelocity.x = -1.f;
        else
            cameraVelocity.x = 0.f;
        
        cameraRotation.x = (float)input.xrel;
        cameraRotation.y = -(float)input.yrel;
    }

    virtual void Update(double deltaTime)
    {
        runTime += deltaTime;
        if (runTime < 0.05)
            return;

        glm::vec3 cameraPos = scene.GetCamera()->GetPosition();
        glm::vec3 forward = scene.GetCamera()->GetForward();
        forward.y = 0.f;
        forward = glm::normalize(forward);
        cameraPos += (float)deltaTime * walkSpeed * cameraVelocity.y * forward;
        cameraPos += (float)deltaTime * walkSpeed * cameraVelocity.x * scene.GetCamera()->GetRight();
        scene.GetCamera()->SetPosition(cameraPos);

        scene.GetCamera()->AddRotationY(sensitivity * cameraRotation.x);
        scene.GetCamera()->AddRotationX(sensitivity * cameraRotation.y);

        glm::vec3 deltaRotation = 0.000005f * glm::vec3(cosf(runTime) + sinf(runTime), 4.f * sinf(runTime + 2.f) * cosf(runTime + 2.f), 0.f);

        // Head bobble while moving
        if (cameraVelocity.y * cameraVelocity.y + cameraVelocity.x * cameraVelocity.x > 0.01f)
            deltaRotation.x += 0.00005f * sinf(runTime * 25.f);

        scene.GetCamera()->AddRotationX(deltaRotation.x);
        scene.GetCamera()->AddRotationY(deltaRotation.y);

        scene.GetRoot()->Update(deltaTime);

        glm::vec3 soldierPosition = scene.GetObject("soldier")->GetPosition();
        soldierPosition.z += deltaTime * 1.f;
        if (soldierPosition.z > 4.f)
            soldierPosition.z = -4.f;
        scene.GetObject("soldier")->SetPosition(soldierPosition);
        // scene.GetObject("soldier")->SetPosition(3.f * glm::vec3(
        //     cosf(runTime*1.f), 0.f, sinf(runTime*1.f)
        // ));
        // scene.GetObject("soldier")->SetRotationY(-runTime - 1.57*0);


        // Hotfix: Update gun and camera in sync to avoid "jagged" model matrix
        scene.GetCamera()->Update(deltaTime);
    }

    virtual void Render()
    {
        scene.Render();
    }

    virtual void Shutdown() 
    {
    }
    
};

int main() 
{
    LE3ApplicationSettings settings;
    settings.windowWidth = 1024;
    settings.windowHeight = 786;
    settings.defaultBackgroundR = 0.1f;
    settings.defaultBackgroundG = 0.1f;
    settings.defaultBackgroundB = 0.1f;

    LE3Demo app(settings);
    return app.Run();
}