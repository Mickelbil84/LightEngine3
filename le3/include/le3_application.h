#pragma once
#define SDL_MAIN_HANDLED
#include "SDL.h"
#include <gl/glew.h>
#include <iostream>

// Base abstract class for any LE3 based application.
// User should implement all abstract functions (they may be empty).
// Usage:
//      class AppName : public LE3Application {...} // Override any functionality
//      
//      int main(int argc, char** argv)
//      {
//          AppName app;
//          return app.Run();
//      }
class LE3Application
{
public:
    LE3Application();

    // Initialized all user data. Called only once, at the beginning of the program.
    virtual int Init() = 0;
    // Handles the input (or any other event). Runs each frame, if some user event occured.
    virtual void HandleInput(SDL_Event e) = 0;
    // Updates the application/game state. Runs each frame. The argument `deltaTime` is
    // the time (in seconds) that took to process the last frame and can be used to update/move entities 
    // in a speed that is independant from the running speed of the application.
    virtual void Update(double deltaTime) = 0;
    // Renders objects to screen. Runs each frame.
    virtual void Render() = 0;
    // Frees any alocated memory and any other processing that is needed
    // at the end of the application. Runs only once, at the end of the program.
    virtual void Shutdown() = 0;

    // Initialized, runs and cleans the program. This is the only method of the application
    // that the user should call.
    int Run();
protected:
    bool m_bShouldRun;
    double m_deltaTime;

private:
    // Initialized internal structures of the application.
    int _Init();
    // Runs the game loop of the application.
    int _Run();
    // Frees internal structures of the application.
    void _Shutdown();

    SDL_Window* m_pWindow;
    SDL_GLContext m_glcontext;
};