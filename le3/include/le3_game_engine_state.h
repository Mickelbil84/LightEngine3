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

    private:
        float m_elapsedTime = 0.f;
        int m_windowWidth, m_windowHeight;

    public:
        friend class LE3Application;
    };
}