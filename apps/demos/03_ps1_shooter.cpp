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

#define PS1_RESOLUTION_WIDTH 320 * 2
#define PS1_RESOLUTION_HEIGHT 240 * 2


class LE3Demo : public LE3Application
{
public:
    LE3Demo(LE3ApplicationSettings settings) : LE3Application(settings)
    {
        defaultWidth = settings.windowWidth, defaultHeight = settings.windowHeight;
    }

    double runTime = 0.0;

    LE3SceneManager scene;
    GLuint m_outFramebuffer;

    glm::vec2 cameraVelocity;
    glm::vec2 cameraRotation;
    float walkSpeed, sensitivity;

    bool bCanShoot, bIsShooting, bAimDownSights;
    double shotBeginTime;

    glm::mat4 viewMatrix, projMatrix;

    int defaultWidth, defaultHeight;

    virtual int Init() 
    {
        // ---------------------------
        //   Load Assets
        // ---------------------------
        LE3Texture::g_bPS1TextureMode = true;
        scene.Init();
        // LoadScene(scene, "../resources/scenes/03_ps1_shooter.json");
        LoadScene(scene, "../resources/scenes/demo_environment3.json");
        scene.AddFPSCamera();


        // Add Gun
        scene.assets.LoadMesh("glock", "../resources/models/weapons/glock.obj");
        scene.assets.LoadTexture("glockDiffuse", "../resources/textures/weapons/glock_diffuse.tga");
        scene.assets.CreateMaterial("glockMat", "S_default");
        scene.assets.GetMaterial("glockMat")->SetDiffuseTexture(scene.assets.GetTexture("glockDiffuse"));
        scene.assets.GetMaterial("glockMat")->bUseDiffuseTexture = true;

        scene.AddStaticMesh("gun", "glock", "glockMat", 0.05f, false, "camera");

        std::cout << scene.GetObject("gun")->GetParent()->GetName() << std::endl;

        // ---------------------------
        //   Misc
        // ---------------------------
        
        scene.GetCamera()->SetPosition(glm::vec3(0.f, 1.25f, 0.f));
        scene.GetCamera()->SetAspectRatio((float)m_settings.windowWidth / (float)m_settings.windowHeight);
        
        walkSpeed = 2.2f;
        sensitivity = 0.005f;

        UpdateWindowTitle("LightEngine3 - (03) PS1 Shooter");

        // ---------------------------
        //   Create framebuffer
        // ---------------------------
        glGenFramebuffers(1, &m_outFramebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, m_outFramebuffer);

        GLuint bufferTexture, depthTexture;
        glGenTextures(1, &bufferTexture);
        glBindTexture(GL_TEXTURE_2D, bufferTexture);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, PS1_RESOLUTION_WIDTH, PS1_RESOLUTION_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, bufferTexture, 0);  

        glGenTextures(1, &depthTexture);
        glBindTexture(GL_TEXTURE_2D, depthTexture);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, PS1_RESOLUTION_WIDTH, PS1_RESOLUTION_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 
        glTexImage2D(
            GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, PS1_RESOLUTION_WIDTH, PS1_RESOLUTION_HEIGHT, 0, 
            GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL
        );

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);  

        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "Framebuffer incomplete! EC: " << glCheckFramebufferStatus(GL_FRAMEBUFFER) << m_outFramebuffer << std::endl;

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        return 0;
    }

    virtual void HandleInput(LE3Input input) 
    { 

        if (input.keyboard[SDL_SCANCODE_ESCAPE])
            m_bShouldRun = false;
        
        if (input.keyboard[SDL_SCANCODE_F1])
            ToggleFullscreen();

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

        ////////////////////////
        // Shooting
        ////////////////////////
        if (input.bLeftMouseDown && bCanShoot)
        {
            bCanShoot = false;
            bIsShooting = true;
            shotBeginTime = runTime;
        }

        if (input.bRightMouseDown)
        {
            bAimDownSights = true;
        }
        else
        {
            bAimDownSights = false;
        }
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

        ///////////////
        // Update Gun
        ///////////////
        glm::vec3 deltaRotation = 0.00005f * glm::vec3(cosf(runTime) + sinf(runTime), 4.f * sinf(runTime + 2.f) * cosf(runTime + 2.f), 0.f);

        scene.GetObject("gun")->SetRotation(glm::vec3(8.f * 3.14159265 / 180.f, -3.14159265f + 5.f * 3.14159265 / 180.f, 0.f) + deltaRotation * 100.f);
        scene.GetObject("gun")->SetPosition(glm::vec3(0.12f, -.1f, -0.4f));

        if (bAimDownSights)
        {
            scene.GetObject("gun")->SetRotation(glm::vec3(4.f * 3.14159265 / 180.f, -3.14159265f + 0.f * 3.14159265 / 180.f, 0.f) + deltaRotation * 70.f);
            scene.GetObject("gun")->SetPosition(glm::vec3(0.0f, -.1f, -0.3f));
            scene.GetCamera()->SetFOV(glm::radians(35.f));
        }
        else
        {
            scene.GetCamera()->SetFOV(glm::radians(45.f));
        }

        float shotDuration = 0.1f;
        if (bIsShooting)
        {
            float gunSine = sinf((runTime - shotBeginTime) * (2 * 3.14159265f) / shotDuration);
            deltaRotation.x += 0.005f * gunSine;

            scene.GetObject("gun")->SetPosition(scene.GetObject("gun")->GetPosition() + glm::vec3(0.0f, 0.01f * gunSine, 0.f));
            scene.GetObject("gun")->SetRotation(scene.GetObject("gun")->GetRotation() + glm::vec3(0.05f * gunSine, 0.f, 0.f));
            if (runTime - shotBeginTime > shotDuration)
            {
                bIsShooting = false;
            }
        }
        else if (!bCanShoot && (runTime - shotBeginTime > 2 * shotDuration))
            bCanShoot = true;

        // Head bobble while moving
        if (cameraVelocity.y * cameraVelocity.y + cameraVelocity.x * cameraVelocity.x > 0.01f)
            deltaRotation.x += 0.001f * sinf(runTime * 25.f);

        scene.GetCamera()->AddRotationX(deltaRotation.x);
        scene.GetCamera()->AddRotationY(deltaRotation.y);

        scene.GetRoot()->Update(deltaTime);

        // Hotfix: Update gun and camera in sync to avoid "jagged" model matrix
        scene.GetCamera()->Update(deltaTime);
        scene.GetObject("gun")->Update(deltaTime);
    }

    virtual void Render()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_outFramebuffer);
        glViewport(0, 0, PS1_RESOLUTION_WIDTH, PS1_RESOLUTION_HEIGHT);
        glClearColor(0.1f, 0.1f, 0.1f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (const auto& [key, value] : scene.assets.m_shaders)
        {
            LE3Shader* shader = scene.assets.GetShader(key);
            shader->Use();
            shader ->Uniform("view", scene.GetCamera()->GetViewMatrix());
            shader->Uniform("projection", scene.GetCamera()->GetProjectionMatrix());
        }

        scene.GetRoot()->Draw();


        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
        glViewport(0, 0, m_settings.windowWidth, m_settings.windowHeight);
        glClearColor(0.7f, 0.7f, 0.7f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBlitFramebuffer(0, 0, PS1_RESOLUTION_WIDTH, PS1_RESOLUTION_HEIGHT, 0, 0, m_settings.windowWidth, m_settings.windowHeight, 
            GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, GL_NEAREST);
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
        scene.GetCamera()->SetAspectRatio((float)m_settings.windowWidth / (float)m_settings.windowHeight);
    }
};

int main() {
    LE3ApplicationSettings settings;
    settings.windowWidth = 1024;
    settings.windowHeight = 786;

    LE3Demo app(settings);
    return app.Run();
}