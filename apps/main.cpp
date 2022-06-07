#include <le3_application.h>
#include <le3_shader.h>

class LE3Demo : public LE3Application
{
public:
    LE3Demo(LE3ApplicationSettings settings) : LE3Application(settings)
    {
        defaultWidth = settings.windowWidth, defaultHeight = settings.windowHeight;
    }

    LE3Shader shader;
    GLuint m_vao;
    int defaultWidth, defaultHeight;

    virtual int Init() 
    {
        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);
        

        GLuint m_vbo;
        glGenBuffers(1, &m_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        
        float triangle[] = {
            -0.5f, -0.5f, 0.f,
            0.f, 0.5f, 0.f,
            0.5f, -0.5f, 0.f
        };
        glBufferData(GL_ARRAY_BUFFER, 9*sizeof(float), triangle, GL_STATIC_DRAW);
        
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

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
        glBindVertexArray(m_vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
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