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

#include <vector>
#include <glm/gtx/transform.hpp>


class LE3Demo : public LE3Application
{
public:
    LE3Demo(LE3ApplicationSettings settings) : LE3Application(settings)
    {
        defaultWidth = settings.windowWidth, defaultHeight = settings.windowHeight;
    }

    double runTime = 0.0;

    LE3SceneRoot root;
    LE3AssetManager assets;

    LE3Object car;
    LE3Object wheelsFront, wheelsBack;
    LE3StaticMesh carBodyMesh;
    LE3StaticMesh wheel1, wheel2, wheel3, wheel4;

    LE3FreeCamera camera;

    int defaultWidth, defaultHeight;

    virtual int Init() 
    {
        // ---------------------------
        //   Load Assets
        // ---------------------------
        assets.LoadShader("basic", 
            "resources/shaders/basic/basic.vs", 
            "resources/shaders/basic/basic.fs");

        std::vector<LE3Vertex> box;
        AddBox(box, 0.f, 0.f, 0.f, .5f, .5f, .3f);
        assets.LoadMesh("wheel", "resources/models/cars/Audi R8 Wheel.fbx");
        assets.LoadMesh("carBody", "resources/models/cars/Audi R8 Body.fbx");

        assets.CreateMaterial("red", "basic");
        assets.GetMaterial("red")->diffuseColor = glm::vec4(1.f, 0.f, 0.f, 1.f);
        assets.CreateMaterial("green", "basic");
        assets.GetMaterial("green")->diffuseColor = glm::vec4(0.f, 1.f, 0.f, 1.f);
        assets.CreateMaterial("blue", "basic");
        assets.GetMaterial("blue")->diffuseColor = glm::vec4(0.f, 0.f, 1.f, 1.f);
        assets.CreateMaterial("yellow", "basic");
        assets.GetMaterial("yellow")->diffuseColor = glm::vec4(1.f, 1.f, 0.f, 1.f);

        assets.CreateMaterial("carBody", "basic");
        assets.LoadTexture("wood", "resources/textures/woodparquet_59-2K/woodparquet_59_basecolor-2K-2K.png");
        assets.GetMaterial("carBody")->diffuseTexture = assets.GetTexture("wood");
        assets.GetMaterial("carBody")->bUseDiffuseTexture = false;
        
        // ---------------------------
        //   Create game objects
        // ---------------------------
        root.AppendChild(&camera);

        root.AppendChild(&car);
        // car.AddRotationY(-3.14159265f);
        car.SetPosition(glm::vec3(0.f, 0.f, 2.f));

        carBodyMesh.SetMesh(assets.GetMesh("carBody"));
        carBodyMesh.SetMaterial(assets.GetMaterial("carBody"));
        carBodyMesh.SetScale(0.3f);
        carBodyMesh.SetRotation(glm::vec3(-3.14159265f / 2.f, 0.f, -3.14159265f / 2.f));
        car.AppendChild(&carBodyMesh);

        wheelsFront.SetPosition(glm::vec3(-.705f, 0.175f, 0.f));
        car.AppendChild(&wheelsFront);
        wheelsBack.SetPosition(glm::vec3(.935f, 0.175f, 0.f));
        car.AppendChild(&wheelsBack);

        wheel1.SetMesh(assets.GetMesh("wheel"));
        wheel1.SetMaterial(assets.GetMaterial("red"));
        wheel1.SetPosition(glm::vec3(0.f, 0.f, -.5f));
        wheel1.SetScale(0.33f);
        wheel1.SetRotation(glm::vec3(-3.14159265f / 2.f, 0.f, -3.14159265f / 2.f));
        wheelsFront.AppendChild(&wheel1);

        wheel2.SetMesh(assets.GetMesh("wheel"));
        wheel2.SetMaterial(assets.GetMaterial("green"));
        wheel2.SetPosition(glm::vec3(0.f, 0.f, .5f));
        wheel2.SetScale(0.33f);
        wheel2.SetRotation(glm::vec3(-3.14159265f / 2.f, 0.f, 3.14159265f / 2.f));
        wheelsFront.AppendChild(&wheel2);

        wheel3.SetMesh(assets.GetMesh("wheel"));
        wheel3.SetMaterial(assets.GetMaterial("blue"));
        wheel3.SetPosition(glm::vec3(0.f, 0.f, -.5f));
        wheel3.SetScale(0.33f);
        wheel3.SetRotation(glm::vec3(-3.14159265f / 2.f, 0.f, -3.14159265f / 2.f));
        wheelsBack.AppendChild(&wheel3);

        wheel4.SetMesh(assets.GetMesh("wheel"));
        wheel4.SetMaterial(assets.GetMaterial("yellow"));
        wheel4.SetPosition(glm::vec3(0.f, 0.f, .55f));
        wheel4.SetScale(0.33f);
        wheel4.SetRotation(glm::vec3(-3.14159265f / 2.f, 0.f, 3.14159265f / 2.f));
        wheelsBack.AppendChild(&wheel4);


        // ---------------------------
        //   Misc
        // ---------------------------
        
        camera.SetPosition(glm::vec3(0.f, 1.f, 5.f));

        return 0;
    }

    virtual void HandleInput(LE3Input input) 
    { 

        if (input.keyboard[SDL_SCANCODE_ESCAPE])
            m_bShouldRun = false;
        
        if (input.keyboard[SDL_SCANCODE_F11])
            ToggleFullscreen();

        ////////////////////////
        // Camera Movement
        ////////////////////////
        if (input.keyboard[SDL_SCANCODE_W])
            camera.SetMoveVelocityY(1.f);
        else if (input.keyboard[SDL_SCANCODE_S])
            camera.SetMoveVelocityY(-1.f);
        else
            camera.SetMoveVelocityY(0.f);

        if (input.keyboard[SDL_SCANCODE_D])
            camera.SetMoveVelocityX(1.f);
        else if (input.keyboard[SDL_SCANCODE_A])
            camera.SetMoveVelocityX(-1.f);
        else
            camera.SetMoveVelocityX(0.f);

        if (input.keyboard[SDL_SCANCODE_E])
            camera.SetMoveVelocityZ(1.f);
        else if (input.keyboard[SDL_SCANCODE_Q])
            camera.SetMoveVelocityZ(-1.f);
        else
            camera.SetMoveVelocityZ(0.f);
        
        camera.SetLookVelocityX((float)input.xrel);
        camera.SetLookVelocityY(-(float)input.yrel);
    }

    virtual void Update(double deltaTime)
    {
        runTime += deltaTime;
        if (runTime < 0.05)
            return;

        glm::vec3 carPos = car.GetPosition();
        glm::vec3 tangent = glm::vec3(-carPos.z, 0.f, carPos.x);
        // carPos.x += 1.f * (float)deltaTime;
        // if (carPos.x > 2.f)
        //     carPos.x = -2.f;
        // car.SetPosition(carPos + (float)deltaTime * tangent);
        // car.SetRotation(glm::vec3(0.f, atan2(tangent.x, tangent.z) + 3.14159265f / 2.f, 0.f));
        // wheel1.AddRotationY((float)deltaTime * -1.9f);
        // wheel2.AddRotationY((float)deltaTime * -1.9f);
        // wheel3.AddRotationY((float)deltaTime * -1.9f);
        // wheel4.AddRotationY((float)deltaTime * -1.9f);

        root.Update(deltaTime);
    }

    virtual void Render()
    {
        assets.GetShader("basic")->Use();
        assets.GetShader("basic")->Uniform("view", camera.GetViewMatrix());
        assets.GetShader("basic")->Uniform("projection", camera.GetProjectionMatrix((float)defaultWidth / (float)defaultHeight));

        root.Draw();
    }

    virtual void Shutdown() 
    {
    }

    void ToggleFullscreen()
    {
        if (m_settings.bIsFullscreen)
        {
            m_settings.windowWidth = defaultWidth;
            m_settings.windowHeight = defaultHeight;
            m_settings.bIsFullscreen = false;
        }
        else
        {
            m_settings.windowWidth = 1920;
            m_settings.windowHeight = 1080;
            m_settings.bIsFullscreen = true;
        }

        ApplyWindowSettings();
    }
};

int main() {
    LE3ApplicationSettings settings;
    settings.windowWidth = 1024;
    settings.windowHeight = 786;
    // settings.bWireframe = true;

    LE3Demo app(settings);
    return app.Run();
}