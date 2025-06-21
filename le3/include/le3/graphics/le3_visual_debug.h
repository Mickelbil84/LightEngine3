#pragma once

#include "graphics/le3_camera.h"

namespace le3 {

    class LE3VisualDebug {
    public:
        void reset();

        inline void setActiveCamera(LE3CameraPtr camera) { m_activeCamera = camera; }

        void drawDebugLine(glm::vec3 start, glm::vec3 end, glm::vec3 color);

        void drawDebugBox(glm::vec3 position, glm::quat rotation, glm::vec3 scale, glm::vec3 color);
        void drawDebugBox(glm::mat4 modelMatrix, glm::vec3 color, bool drawDiagonal = false);

        void drawDebugSphere(glm::mat4 modelMatrix, glm::vec3 color);

        void drawDebugCylinder(glm::vec3 position, float radius, float height, glm::vec3 color);
        void drawDebugCone(glm::vec3 position, float radius, float height, glm::vec3 color);

        void setDrawDebugSkeletons(bool draw) { m_bDrawDebugSkeletons = draw; }
        bool getDrawDebugSkeletons() const { return m_bDrawDebugSkeletons; }

        void drawDebugMesh(std::weak_ptr<LE3DebugMesh> pMesh, glm::mat4 model, glm::vec3 color);


    private:
        LE3CameraPtr m_activeCamera = nullptr;

        void setupDebugShader(glm::mat4 modelMatrix, glm::vec3 color);

        // Toggles
        bool m_bDrawDebugSkeletons = false;
    };
}