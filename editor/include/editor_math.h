#pragma once

#include <math.h>

#include <glm/glm.hpp>

const float eps_zero = 0.0001f;

float distance(glm::vec2 p, glm::vec2 q);
float square_distance(glm::vec2 p, glm::vec2 q);
float dot(glm::vec2 p, glm::vec2 q);
float minimum_distance(glm::vec2 a, glm::vec2 b, glm::vec2 p);