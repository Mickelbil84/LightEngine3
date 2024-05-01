#pragma once

#include <string>

#include "le3_scene.h"
#include "le3_engine_state.h"

namespace le3 {
    class LE3ImGuiUtils {
    public:
        void addSceneViewport(std::string title, LE3Scene& scene, LE3EngineState& engineState);
        void addDepthFramebufferViewport(std::string title, LE3FramebufferPtr& buffer);

        // Return mouse position in relative position to some window (of size width x height, placed at (offsetX, offsetY))
        // The xy coords are the pos. The third coord is > 0.f if the cursor is inside that rectangle, < 0.f otherwise.
        glm::vec3 getRelativeCursor(int width, int height, int offsetX, int offsetY);
    };
}