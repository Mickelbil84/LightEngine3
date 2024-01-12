#include "le3_application.h"
using namespace le3;

#include <fmt/core.h>

#include <gl/glew.h>
#include <SDL2/SDL.h>

using fmt::format;


struct LE3Application::_Internal {
    _Internal() {}
    std::shared_ptr<SDL_Window> m_pWindow;
    SDL_GLContext m_glContext;
};

LE3Application::LE3Application(std::unique_ptr<LE3GameLogic> pGameLogic) :
    m_pGameLogic(std::move(pGameLogic)),
    m_pInternal(std::make_shared<LE3Application::_Internal>()),
    m_bShouldRun(true) {
    if (m_pGameLogic == nullptr)
        throw std::runtime_error("Cannot start game application with nullptr logic.");
}


void LE3Application::run() {
    init();
    while(m_bShouldRun) {
        handleInput();
        update();
        render();
    }
    shutdown();
}

void LE3Application::init() {
    _initSDL();
    _initOpenGL();
    m_pGameLogic->init();
}

void LE3Application::handleInput() {
    SDL_Event e;
    LE3Input input;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) m_bShouldRun = false;
    }

    m_pGameLogic->handleInput(input);
}

void LE3Application::update() {
    // Update delta time computation
    m_currTime = SDL_GetTicks();
    m_deltaTime = (double)((m_currTime - m_prevTime) * 1000 / (double)SDL_GetPerformanceFrequency());
    m_deltaTime *= 0.001;
    m_prevTime = m_currTime;
    m_pGameLogic->m_engineState.m_elapsedTime += m_deltaTime;

    m_pGameLogic->update(m_deltaTime);
}

void LE3Application::render() {
    glClearColor(0.8f, 0.8f, 0.8f, 1.f); // TODO: Propagate to game config
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_pGameLogic->render();

    SDL_GL_SwapWindow(m_pInternal->m_pWindow.get());
}

void LE3Application::shutdown() {
    m_pGameLogic->shutdown();

    SDL_GL_DeleteContext(m_pInternal->m_glContext);
    if (m_pInternal->m_pWindow) {
        SDL_DestroyWindow(m_pInternal->m_pWindow.get());
        m_pInternal->m_pWindow = nullptr;
    }
    SDL_Quit();
}

void LE3Application::_initSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        throw std::runtime_error(format("Could not initialize SDL: {}\n", SDL_GetError()));
    
    // TODO: Enumerate largest version of OpenGL and GLSL on device
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16); // TODO: Propagate multisamples into engine config

    Uint32 flags = 0;
    flags |= SDL_WINDOW_OPENGL;
    flags |= SDL_WINDOW_RESIZABLE; // TODO: Propagate resizability (and fullscreen) into engine config

    // TODO: Propagate window title and size into game config
    m_pInternal->m_pWindow = std::shared_ptr<SDL_Window>(SDL_CreateWindow(
        "LightEngine3 v0.2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 800, flags
    ), SDL_DestroyWindow);
    // SDL_SetRelativeMouseMode(SDL_TRUE);

    if (!m_pInternal->m_pWindow)
        throw std::runtime_error(format("Could not create SDL window: {}\n", SDL_GetError()));
    m_pInternal->m_glContext = SDL_GL_CreateContext(m_pInternal->m_pWindow.get());
    m_pGameLogic->m_engineState.m_windowWidth = 1200;
    m_pGameLogic->m_engineState.m_windowHeight = 800;

    m_prevTime = m_currTime = SDL_GetPerformanceCounter();

    // if (false) // TODO: Allow fullscreen on init
        // setFullscreen(true);
}
void LE3Application::_initOpenGL() {
    if (glewInit() != GLEW_OK)
        throw std::runtime_error(format("Could not init GLEW: {}", (char *)glewGetErrorString(glewInit())));
    
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glEnable(GL_MULTISAMPLE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}