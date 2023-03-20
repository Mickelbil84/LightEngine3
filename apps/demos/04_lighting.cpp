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

#include <vector>
#include <glm/gtx/transform.hpp>

#ifndef __APPLE__
const std::string resource_prefix = std::string("../../");
#else
const std::string resource_prefix = std::string("../");
#endif


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
        // LoadScene(scene, "../resources/scenes/04_lighting.json");
        
        // Meshes
        scene.assets.AddMeshPath("floor", "$BOX_0_0_0_10.000000_0.200000_10.000000_");
        scene.assets.AddMeshPath("sphere", "$SPH_0_0_0_0.700000_64.000000_");
        scene.assets.AddMeshPath("bunny", resource_prefix + "resources/models/bunny.obj");

        // Textures
        scene.assets.AddTexturePath("TD_tile_floor", resource_prefix + "resources/textures/tile_floor.jpg");
        scene.assets.AddTexturePath("TN_tile_floor", resource_prefix + "resources/textures/tile_floor_normal.png");
        scene.assets.AddTexturePath("TD_wood", resource_prefix + "resources/textures/wood.png");
        scene.assets.AddTexturePath("TN_wood", resource_prefix + "resources/textures/wood_normal.png");
        scene.assets.AddTexturePath("TD_bunny", resource_prefix + "resources/textures/bunny.png");
        scene.assets.AddTexturePath("TN_bunny", resource_prefix + "resources/textures/bunny_normal.png");
        scene.assets.AddTexturePath("CM_basilica", resource_prefix + "resources/textures/distribution_board_4k.png");
        // scene.assets.AddCubemapPath("CM_basilica", resource_prefix + "resources/cubemaps/basilica");

        // Shaders
        scene.assets.AddShaderPath("S_blinn_phong", 
            resource_prefix + "resources/shaders/blinn_phong/blinn_phong.vs", 
            resource_prefix + "resources/shaders/blinn_phong/blinn_phong.fs");
        
        // Materials
        scene.assets.CreateMaterial("M_floor", "S_blinn_phong");
        scene.assets.GetMaterial("M_floor")->SetDiffuseTexture(scene.assets.GetTexture("TD_tile_floor"));
        scene.assets.GetMaterial("M_floor")->bUseDiffuseTexture = true;
        scene.assets.GetMaterial("M_floor")->specularIntensity = 2.f;
        scene.assets.GetMaterial("M_floor")->shininess = 128.f;
        scene.assets.GetMaterial("M_floor")->SetSpecularTexture(scene.assets.GetTexture("TD_tile_floor"));
        scene.assets.GetMaterial("M_floor")->bUseSpecularTexture = true;
        scene.assets.GetMaterial("M_floor")->SetNormalTexture(scene.assets.GetTexture("TN_tile_floor"));
        scene.assets.GetMaterial("M_floor")->bUseNormalTexture = true;
        scene.assets.GetMaterial("M_floor")->tilingX = 0.5f;
        scene.assets.GetMaterial("M_floor")->tilingY = 0.5f;
        scene.assets.GetMaterial("M_floor")->SetCubemap(scene.assets.GetTexture("CM_basilica"));
        scene.assets.GetMaterial("M_floor")->reflectionIntensity = 0.2f;

        scene.assets.CreateMaterial("M_sphere", "S_blinn_phong");
        scene.assets.GetMaterial("M_sphere")->SetDiffuseTexture(scene.assets.GetTexture("TD_wood"));
        scene.assets.GetMaterial("M_sphere")->bUseDiffuseTexture = true;
        scene.assets.GetMaterial("M_sphere")->specularIntensity = 6.f;
        scene.assets.GetMaterial("M_sphere")->shininess = 64.f;
        scene.assets.GetMaterial("M_sphere")->SetSpecularTexture(scene.assets.GetTexture("TD_wood"));
        scene.assets.GetMaterial("M_sphere")->bUseSpecularTexture = true;
        scene.assets.GetMaterial("M_sphere")->SetNormalTexture(scene.assets.GetTexture("TN_wood"));
        scene.assets.GetMaterial("M_sphere")->bUseNormalTexture = true;
        scene.assets.GetMaterial("M_sphere")->tilingX = 1.f;
        scene.assets.GetMaterial("M_sphere")->tilingY = 1.f;
        scene.assets.GetMaterial("M_sphere")->SetCubemap(scene.assets.GetTexture("CM_basilica"));
        scene.assets.GetMaterial("M_sphere")->reflectionIntensity = 0.3f;

        scene.assets.CreateMaterial("M_bunny", "S_blinn_phong");
        scene.assets.GetMaterial("M_bunny")->SetDiffuseTexture(scene.assets.GetTexture("TD_tile_floor"));
        scene.assets.GetMaterial("M_bunny")->bUseDiffuseTexture = true;
        scene.assets.GetMaterial("M_bunny")->specularIntensity = 6.f;
        scene.assets.GetMaterial("M_bunny")->shininess = 512.f;
        scene.assets.GetMaterial("M_bunny")->SetSpecularTexture(scene.assets.GetTexture("TD_tile_floor"));
        scene.assets.GetMaterial("M_bunny")->bUseSpecularTexture = true;
        scene.assets.GetMaterial("M_bunny")->SetNormalTexture(scene.assets.GetTexture("TN_tile_floor"));
        scene.assets.GetMaterial("M_bunny")->bUseNormalTexture = true;
        scene.assets.GetMaterial("M_bunny")->SetCubemap(scene.assets.GetTexture("CM_basilica"));
        scene.assets.GetMaterial("M_bunny")->reflectionIntensity = 0.9f;


        scene.assets.GetMaterial("M_bunny")->tilingX = 3.f;
        scene.assets.GetMaterial("M_bunny")->tilingY = 3.f;

        // Objects
        scene.AddStaticMesh("floor", "floor", "M_floor");

        scene.AddStaticMesh("sphere", "sphere", "M_sphere");
        scene.GetObject("sphere")->SetPosition(glm::vec3(0.f, 0.6959f, 1.2027f));

        scene.AddStaticMesh("bunny", "bunny", "M_bunny", 6.f);
        scene.GetObject("bunny")->SetPosition(glm::vec3(0.f, -0.1959f, -1.5027f));
        // scene.GetObject("bunny")->SetRotationX(-1.57f);

        // Lights
        scene.AddAmbientLight(glm::vec3(1.f, 1.f, 1.f), 0.1f);

        scene.AddDirectionalLight("directional_light01", glm::vec3(1.f), 0.7);
        scene.GetObject("directional_light01")->SetRotationX(-1.5f);
        scene.lightManager.EnableShadows(dynamic_pointer_cast<LE3DirectionalLight>(scene.GetObject("directional_light01")));

        scene.AddDirectionalLight("directional_light02", glm::vec3(0.05f, 0.8f, 0.95f), 0.5);
        scene.lightManager.EnableShadows(dynamic_pointer_cast<LE3DirectionalLight>(scene.GetObject("directional_light02")));

        scene.AddPointLight("point_light01", glm::vec3(0.95f, 0.7f, 0.2f), 0.7f);
        scene.GetObject("point_light01")->SetPosition(glm::vec3(0.f, 1.f, -.7f));

        scene.AddSpotLight("spot_light01");
        scene.GetObject("spot_light01")->SetPosition(glm::vec3(0.f, 1.5f, 0.6f));
        scene.GetObject("spot_light01")->SetRotationX(1.3f);
        scene.lightManager.EnableShadows(dynamic_pointer_cast<LE3SpotLight>(scene.GetObject("spot_light01")));

        SaveScene(scene, resource_prefix + "resources/scenes/04_lighting.json");

        // Camera
        scene.AddFPSCamera();


        // ---------------------------
        //   Misc
        // ---------------------------
        
        scene.GetCamera()->SetPosition(glm::vec3(0.f, 1.25f, 0.f));
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