#include "le3_application.h"

LE3Application::LE3Application(LE3ApplicationSettings settings) : m_bShouldRun(true), m_deltaTime(0), m_settings(settings)
{

}

int LE3Application::_Init()
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

    Uint32 flags = 0;
    flags |= SDL_WINDOW_OPENGL;
    if (m_settings.bIsResizable && !m_settings.bIsFullscreen)
        flags |= SDL_WINDOW_RESIZABLE;

    m_pWindow = SDL_CreateWindow(
        m_settings.windowTitle.c_str(), 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        m_settings.windowWidth, m_settings.windowHeight, 
        flags
    );
    // SDL_SetHintWithPriority(SDL_HINT_MOUSE_RELATIVE_MODE_WARP, "1", SDL_HINT_OVERRIDE);
    SDL_SetRelativeMouseMode(SDL_TRUE);

    if (!m_pWindow)
    {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        return -1;
    }

    m_glcontext = SDL_GL_CreateContext(m_pWindow);
    glewInit();

    if (m_settings.bIsFullscreen)
        SDL_SetWindowFullscreen(m_pWindow, SDL_WINDOW_FULLSCREEN);

    this->ApplyOpenGLSettings();

    m_physics.Init();
    m_lastInput.xrel = m_lastInput.yrel = 0;
    m_lastInput.bLeftMouseDown = false; m_lastInput.bRightMouseDown = false;


    return this->Init();
}
int LE3Application::_Run()
{
    Uint64 currTime = SDL_GetPerformanceCounter();
    Uint64 prevTime = 0;
    while (m_bShouldRun)
    {
       /*
        * Process the event queue
        */
        SDL_Event e;
        LE3Input input;
        input.xrel = 0; input.yrel  = 0;
        input.bLeftMouseDown = m_lastInput.bLeftMouseDown; input.bRightMouseDown = m_lastInput.bRightMouseDown;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                m_bShouldRun = false;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                if (e.button.button == SDL_BUTTON_LEFT)
                    input.bLeftMouseDown = true;
                if (e.button.button == SDL_BUTTON_RIGHT)
                    input.bRightMouseDown = true;
            }
            if (e.type == SDL_MOUSEBUTTONUP)
            {
                if (e.button.button == SDL_BUTTON_LEFT)
                    input.bLeftMouseDown = false;
                if (e.button.button == SDL_BUTTON_RIGHT)
                    input.bRightMouseDown = false;
            }
        }
        SDL_GetRelativeMouseState(&input.xrel, &input.yrel);
        input.keyboard = SDL_GetKeyboardState(NULL);
        this->HandleInput(input);
        m_lastInput = input;

        /*
        * Update application logic
        */
       this->Update(m_deltaTime);

       /*
        * Render the frame
        */
        glClearColor(
            m_settings.defaultBackgroundR, 
            m_settings.defaultBackgroundG, 
            m_settings.defaultBackgroundB, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        this->Render();

        SDL_GL_SwapWindow(m_pWindow);

        /*
        * Handle time calculations
        */
        prevTime = currTime;
        currTime = SDL_GetPerformanceCounter();
        m_deltaTime = (double)((currTime - prevTime) * 1000 / (double)SDL_GetPerformanceFrequency());
        m_deltaTime *= 0.001;
        if (m_deltaTime < 1.0 / (double)m_settings.maxFPS) // Cap frame rate
                SDL_Delay(Uint32((1.0 / (double)m_settings.maxFPS - m_deltaTime) * 1000));
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

void LE3Application::ApplyOpenGLSettings()
{
    if (m_settings.bEnableDepthTest)
        glEnable(GL_DEPTH_TEST);
    else
        glDisable(GL_DEPTH_TEST);

    if (m_settings.bWireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void LE3Application::ApplyWindowSettings()
{
    this->UpdateWindowTitle(m_settings.windowTitle);
    if (m_settings.bIsFullscreen)
    {
        SDL_SetWindowSize(m_pWindow, m_settings.windowWidth, m_settings.windowHeight);
        SDL_SetWindowFullscreen(m_pWindow, SDL_WINDOW_FULLSCREEN);
        SDL_SetWindowResizable(m_pWindow, SDL_FALSE);
    }
    else
    {   
        SDL_SetWindowFullscreen(m_pWindow, 0);
        SDL_SetWindowResizable(m_pWindow, (SDL_bool)m_settings.bIsResizable);
        SDL_SetWindowSize(m_pWindow, m_settings.windowWidth, m_settings.windowHeight);
    }
}

void LE3Application::UpdateWindowTitle(std::string windowTitle)
{
    m_settings.windowTitle = windowTitle;
    SDL_SetWindowTitle(m_pWindow, m_settings.windowTitle.c_str());
}