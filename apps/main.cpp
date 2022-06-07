#include <le3_application.h>
#include <le3_shader.h>
#include <le3_mesh.h>
#include <le3_primitives.h>

#include <vector>

class LE3Demo : public LE3Application
{
public:
    LE3Demo(LE3ApplicationSettings settings) : LE3Application(settings)
    {
        defaultWidth = settings.windowWidth, defaultHeight = settings.windowHeight;
    }

    LE3Shader shader;
    LE3Mesh<LE3Vertex3p> mesh;
    GLuint m_vao;
    int defaultWidth, defaultHeight;

    virtual int Init() 
    {
        std::vector<LE3Vertex3p> triangle;
        std::vector<GLushort> indices;
        AddIsoscelesTriangle(triangle, 0.f, 0.f, 0.f, 1.f, 1.f);
        indices.push_back(0);
        indices.push_back(1);
        indices.push_back(2);
        mesh.LoadMeshData(triangle);


        shader.CompileShader(
            "../../resources/shaders/basic/basic.vs",
            "../../resources/shaders/basic/basic.fs"
        );
        
        return 0;
    }

    virtual void HandleInput(SDL_Event e) 
    {   
        if (e.type == SDL_KEYDOWN)
        {
            if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
            {
                m_bShouldRun = false;
            }
            if (e.key.keysym.scancode == SDL_SCANCODE_F11)
            {
                ToggleFullscreen();
            }
        }
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
        glDeleteVertexArrays(1, &m_vao);
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