#pragma once

namespace le3 {
    // Engine state is updated within the LE3Application
    // Members are specifically private (for LE3GameLogic) as they are read-only.
    struct LE3EngineState {
    public:
        inline float getElapsedTime() const { return m_elapsedTime; }

        inline int getWindowWidth() const { return m_windowWidth; }
        inline int getWindowHeight() const { return m_windowHeight; }
        inline float getAspectRatio() const { return (float)m_windowWidth / (float)m_windowHeight; }

        inline void notifyWantsQuit() { m_bWantsQuit = true; }
        inline void notifyWantsRelativeMOuse(bool relativeMouse) { m_bWantsRelativeMouse = relativeMouse; }
        inline bool isRelativeMouse() const { return m_bReltaiveMouse; }

        inline bool isFocused() const { return m_bFocused; } // True only if window is focused (and not on GUI)
        inline void setFocusedOverride(bool override) { m_bFocusedOverride = override; } // If set to true, ignore window focus and propagate user input
        inline bool getFocusedOverride() const { return m_bFocusedOverride; }
        inline std::string getFocusOverrider() const { return m_focusOverrider; }
        inline void setFocusOverrider(std::string overrider) { m_focusOverrider = overrider; }

    private:
        float m_elapsedTime = 0.f;
        int m_windowWidth, m_windowHeight;
        bool m_bWantsQuit = false;
        bool m_bWantsRelativeMouse = false;
        bool m_bReltaiveMouse = false;
        bool m_bFocused = true, m_bFocusedOverride = false;
        std::string m_focusOverrider = "";

    public:
        friend class LE3Application;
    };
}