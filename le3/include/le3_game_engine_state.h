#pragma once

namespace le3 {
    // Engine state is updated within the LE3Application
    // Members are specifically private (for LE3GameLogic) as they are read-only.
    struct LE3GameEngineState {
    public:
        inline float getElapsedTime() const { return m_elapsedTime; }

        inline int getWindowWidth() const { return m_windowWidth; }
        inline int getWindowHeight() const { return m_windowHeight; }
        inline float getAspectRatio() const { return (float)m_windowWidth / (float)m_windowHeight; }

        inline void notifyWantsQuit() { m_bWantsQuit = true; }
        inline void notifyWantsRelativeMOuse(bool relativeMouse) { m_bWantsRelativeMouse = relativeMouse; }
        inline bool isRelativeMouse() const { return m_bReltaiveMouse; }

        inline bool isFocused() const { return m_bFocused; } // True only if window is focused (and not on GUI)

    private:
        float m_elapsedTime = 0.f;
        int m_windowWidth, m_windowHeight;
        bool m_bWantsQuit = false;
        bool m_bWantsRelativeMouse = false;
        bool m_bReltaiveMouse = false;
        bool m_bFocused = true;

    public:
        friend class LE3Application;
    };
}