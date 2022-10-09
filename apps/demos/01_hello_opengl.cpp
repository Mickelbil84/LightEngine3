#include <le3_application.h>
#include <le3_shader.h>
#include <le3_mesh.h>
#include <le3_primitives.h>

#include <vector>

#ifndef __APPLE__
const std::string resource_prefix = std::string("../../");
#else
const std::string resource_prefix = std::string("../");
#endif

class App01_Hello_OpenGL : public LE3Application
{
public:
    App01_Hello_OpenGL(LE3ApplicationSettings settings) : LE3Application(settings)
    {
        defaultWidth = settings.windowWidth, defaultHeight = settings.windowHeight;
    }

    LE3Shader shader;
    LE3Mesh<LE3Vertex3p3c> mesh;
    int defaultWidth, defaultHeight;

    virtual int Init() 
    {
        std::vector<LE3Vertex3p3c> triangle;
        AddHelloOpenGLTriangle(triangle);
        mesh.LoadMeshData(triangle);


        shader.CompileShader(
            resource_prefix + "resources/shaders/hello_opengl/hello_opengl.vs",
            resource_prefix + "resources/shaders/hello_opengl/hello_opengl.fs"
        );

        UpdateWindowTitle("LightEngine3 - (01) \"Hello OpenGL\" Demo");
        
        return 0;
    }

    virtual void HandleInput(LE3Input input) 
    {   
        if (input.keyboard[SDL_SCANCODE_ESCAPE])
            m_bShouldRun = false;
        
        if (input.keyboard[SDL_SCANCODE_F11])
            ToggleFullscreen();
    }

    virtual void Update(double deltaTime)
    {

    }

    virtual void Render()
    {
        shader.Use();
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

    App01_Hello_OpenGL app(settings);
    return app.Run();
}