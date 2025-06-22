#pragma once 

#ifndef GLM_ENABLE_EXPERIMENTAL
#define GLM_ENABLE_EXPERIMENTAL
#endif

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

namespace le3 {
    float distancePointLineSegment(glm::vec2 v, glm::vec2 w, glm::vec2 p);
    glm::vec2 worldToScreen(glm::mat4 projViewMatrix, glm::vec3 p);

    glm::vec3 posFromMatrix(glm::mat4 matrix);
    glm::vec3 scaleFromMatrix(glm::mat4 matrix);
    glm::quat rotFromMatrix(glm::mat4 matrix);
}