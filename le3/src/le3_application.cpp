#include "le3_application.h"

LE3Application::LE3Application() : m_bShouldRun(true), m_deltaTime(0)
{

}

int LE3Application::_Init()
{
    SDL_Init(SDL_INIT_VIDEO);

    m_pWindow = SDL_CreateWindow(
        "LightEngine3", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL
    );

    if (!m_pWindow)
    {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        return -1;
    }

    m_glcontext = SDL_GL_CreateContext(m_pWindow);
    glewInit();


    return this->Init();
}
int LE3Application::_Run()
{
    Uint64 currTime = SDL_GetPerformanceCounter();
    Uint64 prevTime = 0;
    while (m_bShouldRun)
    {
        /*
        * Handle time calculations
        */
       prevTime = currTime;
       currTime = SDL_GetPerformanceCounter();
       m_deltaTime = (double)((currTime - prevTime) * 1000 / (double)SDL_GetPerformanceFrequency());
       m_deltaTime *= 0.001;

       /*
        * Process the event queue
        */
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                m_bShouldRun = false;
            }
            this->HandleInput(e);
        }

        /*
        * Update application logic
        */
       this->Update(m_deltaTime);

       /*
        * Render the frame
        */
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        this->Render();

        SDL_GL_SwapWindow(m_pWindow);
    }

    return 0;
}
void LE3Application::_Shutdown()
{
    this->Shutdown();
    SDL_GL_DeleteContext(m_glcontext);
    SDL_DestroyWindow(m_pWindow);
    SDL_Quit();
}

int LE3Application::Run()
{
    if (this->_Init() < 0) return -1; 
    if (this->_Run() < 0) return -1;
    this->_Shutdown();
    return 0;
}
