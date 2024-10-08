#include "le3_math_utils.h"

// Taken from https://stackoverflow.com/questions/849211/shortest-distance-between-a-point-and-a-line-segment
float le3::distancePointLineSegment(glm::vec2 v, glm::vec2 w, glm::vec2 p) {
    float l2 = glm::dot(v-w, v-w);
    if (abs(l2) < 1e-4) return glm::length(v - p);
    float t = glm::dot(p - v, w - v) / l2;
    if (t > 1.f) t = 1.f;
    if (t < 0.f) t = 0.f;
    glm::vec2 projection = v + t * (w - v);
    return glm::length(p - projection);
}

glm::vec2 le3::worldToScreen(glm::mat4 projViewMatrix, glm::vec3 p) {
    glm::vec4 res = projViewMatrix * glm::vec4(p, 1.f);
    glm::vec3 ndc = glm::vec3(res) / res.w;
    return glm::vec2(res.x / res.w, res.y / res.w);
}