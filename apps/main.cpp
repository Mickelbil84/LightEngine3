#include <le3_application.h>
#include <le3_shader.h>
#include <le3_mesh.h>
#include <le3_primitives.h>
#include <le3_camera.h>

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

    LE3Shader shader;
    LE3Mesh<LE3Vertex> mesh;

    LE3Camera camera;
    glm::vec2 cameraVelocity;
    glm::vec2 cameraRotation;
    float walkSpeed, sensitivity;

    glm::mat4 modelMatrix, viewMatrix, projMatrix;


    int defaultWidth, defaultHeight;

    virtual int Init() 
    {
        std::vector<LE3Vertex> box;
        AddBox(box, 0.f, 0.f, 0.f, 20.f, 1.f, 20.f);
        AddBox(box, 0.f, 0.f, -5.f, 1.f, 1.f, 1.f);
        mesh.LoadMeshData(box);


        shader.CompileShader(
            "../../resources/shaders/basic/basic.vs",
            "../../resources/shaders/basic/basic.fs"
        );

        modelMatrix = glm::translate(glm::vec3(0.0f, 0.0f, .0f));
        projMatrix = glm::perspective(glm::radians(45.f), (float)defaultWidth / (float)defaultHeight, 0.1f, 100.f);
        
        walkSpeed = 1.2f;
        sensitivity = 0.005f;

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


        glm::vec3 cameraPos = camera.GetPosition();
        glm::vec3 forward = camera.GetForward();
        forward.y = 0.f;
        forward = glm::normalize(forward);
        cameraPos += (float)deltaTime * walkSpeed * cameraVelocity.y * forward;
        cameraPos += (float)deltaTime * walkSpeed * cameraVelocity.x * camera.GetRight();
        camera.SetPosition(cameraPos);

        // std::cout << xRel << std::endl;
        camera.AddRotationY(sensitivity * cameraRotation.x);
        camera.AddRotationX(sensitivity * cameraRotation.y);

        camera.Update(deltaTime);
        viewMatrix = camera.GetViewMatrix();
    }

    virtual void Render()
    {
        shader.Use();
        shader.Uniform("model", modelMatrix);
        shader.Uniform("view", viewMatrix);
        shader.Uniform("projection", projMatrix);
        mesh.Draw();
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

    LE3Demo app(settings);
    return app.Run();
}