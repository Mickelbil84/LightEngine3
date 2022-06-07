#pragma once
#include <gl/glew.h>
#include <string>

struct LE3ApplicationSettings
{
    /////////////////////
    //  Window Settings
    /////////////////////
    std::string windowTitle = "LightEngine3";
    int windowWidth = 800, windowHeight = 600;
    bool bIsResizable = false, bIsFullscreen = false;


    /////////////////////
    //  OpenGL Settings
    /////////////////////
    GLclampf defaultBackgroundR = 100.f/255.f;
    GLclampf defaultBackgroundG = 149.f/255.f;
    GLclampf defaultBackgroundB = 237.f/255.f;
    bool bEnableDepthTest = true;
};