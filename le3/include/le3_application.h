#pragma once
#define SDL_MAIN_HANDLED
#include "SDL.h"
#include <gl/glew.h>
#include <iostream>

class LE3Application
{
public:
    LE3Application();
    virtual int Init() = 0;
    virtual void HandleInput(SDL_Event e) = 0;
    virtual void Update(double deltaTime) = 0;
    virtual void Render() = 0;
    virtual void Shutdown() = 0;
    int Run();
protected:
    bool m_bShouldRun;
    double m_deltaTime;

private:
    int _Init();
    int _Run();
    void _Shutdown();

    SDL_Window* m_pWindow;
    SDL_GLContext m_glcontext;
};