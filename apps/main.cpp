#include <le3_application.h>

class LE3Demo : public LE3Application
{
public:
    GLuint m_vao;

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
        
        return 0;
    }

    virtual void HandleInput(SDL_Event e) 
    {
        if (e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_W)
        {
            std::cout << "hi ^_^" << std::endl;
        }
    }

    virtual void Update(double deltaTime)
    {

    }

    virtual void Render()
    {
        glBindVertexArray(m_vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    virtual void Shutdown() 
    {
        glDeleteVertexArrays(1, &m_vao);
    }
};

int main() {
    LE3Demo app;
    return app.Run();
}