#pragma once

#include <string>

#include "le3_scene.h"
#include "le3_engine_state.h"

namespace le3 {
    class LE3ImGuiUtils {
    public:
        void addSceneViewport(std::string title, LE3Scene& scene, LE3EngineState& engineState);
        void addDepthFramebufferViewport(std::string title, LE3FramebufferPtr& buffer);
    };
}