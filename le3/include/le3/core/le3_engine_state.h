#pragma once

#include "le3_engine_debug.h"

namespace le3 {
    // Engine state is updated within the LE3Application
    // Members are specifically private (for LE3GameLogic) as they are read-only.
    // These are also accesible by the scripting engine
    struct LE3EngineState {
    public:
        inline float getElapsedTime() const { return m_elapsedTime; }

        inline int getWindowWidth() const { return m_windowWidth; }
        inline int getWindowHeight() const { return m_windowHeight; }
        inline float getAspectRatio() const { return (float)m_windowWidth / (float)m_windowHeight; }
        void requestResize(int width, int height) { 
            m_windowWidth = width; m_windowHeight = height; 
            m_bWantsResize = true;
        }
        void requestRenameTitle(std::string title) { m_windowTitle = title; m_bWantsRenameTitle = true; }
        std::string getWindowTitle() const { return m_windowTitle; }


        inline void notifyWantsQuit() { m_bWantsQuit = true; }
        inline void notifyWantsRelativeMouse(bool relativeMouse) { m_bWantsRelativeMouse = relativeMouse; }
        inline bool isRelativeMouse() const { return m_bReltaiveMouse; }

        inline bool isFocused() const { return m_bFocused; } // True only if window is focused (and not on GUI)
        inline void setFocusedOverride(bool override) { m_bFocusedOverride = override; } // If set to true, ignore window focus and propagate user input
        inline bool getFocusedOverride() const { return m_bFocusedOverride; }
        inline std::string getFocusOverrider() const { return m_focusOverrider; }
        inline void setFocusOverrider(std::string overrider) { m_focusOverrider = overrider; }

    private:
        float m_elapsedTime = 0.f;
        int m_windowWidth, m_windowHeight;
        std::string m_windowTitle;
        bool m_bWantsRenameTitle = false;
        bool m_bWantsResize = false;
        bool m_bWantsQuit = false;
        bool m_bWantsRelativeMouse = false;
        bool m_bReltaiveMouse = false;
        bool m_bFocused = true, m_bFocusedOverride = false;
        std::string m_focusOverrider = "";


    public:
        friend class LE3Application;
    };
}