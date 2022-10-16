#include "editor_math.h"

float distance(glm::vec2 p, glm::vec2 q)
{
    return sqrt(
        (p.x - q.x) * (p.x - q.x) +
        (p.y - q.y) * (p.y - q.y)
    );
}
float square_distance(glm::vec2 p, glm::vec2 q)
{
    return (
        (p.x - q.x) * (p.x - q.x) +
        (p.y - q.y) * (p.y - q.y)
    );
}
float dot(glm::vec2 p, glm::vec2 q)
{
    return p.x * q.x + p.y * q.y;
}
float minimum_distance(glm::vec2 a, glm::vec2 b, glm::vec2 p)
{
    const float l2 = square_distance(a, b);
    if (abs(l2) < eps_zero) return distance(a, p);

    float t = dot(p - a, b - a) / l2;
    if (t > 1.f) t = 1.f;
    if (t < 0.f) t = 0.f;
    const glm::vec2 projection = a + t * (b - a);
    return distance(p, projection);
}

glm::vec2 WorldToScreen(glm::mat4 projViewMatrix, glm::vec3 p)
{
    glm::vec4 res = projViewMatrix * glm::vec4(p, 1.f);
    return glm::vec2(res.x / res.z, res.y / res.z);
}