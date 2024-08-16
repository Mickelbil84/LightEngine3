#include "le3_transform.h"
using namespace le3;

#ifndef GLM_ENABLE_EXPERIMENTAL
#define GLM_ENABLE_EXPERIMENTAL
#endif

#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>

LE3Transform::LE3Transform() : 
    m_position(glm::vec3(0.f)),
    m_rotation(glm::quat(1.f, 0.f, 0.f, 0.f)),
    m_scale(glm::vec3(1.f))
{}

glm::mat4 LE3Transform::getTransformMatrix() const {
    glm::mat4 res(1.f);
    res = glm::scale(res, m_scale);
    res = glm::toMat4(m_rotation) * res;
    res = glm::translate(glm::mat4(1.f), m_position) * res;
    return res;
}

void LE3Transform::fromTransformMatrix(glm::mat4 transformMatrix) {
    m_position = glm::vec3(transformMatrix[3]);
    m_rotation = glm::quat_cast(transformMatrix);
    m_scale = glm::vec3(glm::length(glm::vec3(transformMatrix[0])), glm::length(glm::vec3(transformMatrix[1])), glm::length(glm::vec3(transformMatrix[2])));
}

glm::vec3 LE3Transform::getPosition() const {
    return m_position;
}
glm::quat LE3Transform::getRotation() const {
    return m_rotation;
}
glm::vec3 LE3Transform::getScale() const {
    return m_scale;
}

void LE3Transform::setPosition(glm::vec3 position) {
    m_position = position;
}
void LE3Transform::addPosition(glm::vec3 position) {
    m_position += position;
}
void LE3Transform::addPositionX(float amount) {
    m_position.x += amount;
}
void LE3Transform::addPositionY(float amount) {
    m_position.y += amount;
}
void LE3Transform::addPositionZ(float amount) {
    m_position.z += amount;
}

void LE3Transform::setRotation(glm::quat rotation) {
    m_rotation = rotation;
}
void LE3Transform::setRotationRPY(float roll, float pitch, float yaw) {
    m_rotation = glm::quat(glm::vec3(pitch, yaw, roll));
}
void LE3Transform::setOrbit(float roll, float pitch, float yaw, glm::vec3 origin, float offset) {
    glm::vec3 target = glm::vec3(0.f, 0.f, offset) - origin;
    glm::mat4 tmp = 
        glm::translate(glm::mat4(1.f), origin) *
        glm::toMat4(glm::quat(glm::vec3(pitch, yaw, roll))) *
        glm::translate(glm::mat4(1.f), target)
    ;
    m_position = glm::vec3(tmp[3]);
    m_rotation = glm::toQuat(tmp);
}

void LE3Transform::addRotationX(float amount) {
    addRotation(amount, glm::vec3(1.f, 0.f, 0.f));
}
void LE3Transform::addRotationY(float amount) {
    addRotation(amount, glm::vec3(0.f, 1.f, 0.f));
}
void LE3Transform::addRotationZ(float amount) {
    addRotation(amount, glm::vec3(0.f, 0.f, 1.f));
}
void LE3Transform::addRotation(float amount, glm::vec3 axis) {
    // m_rotation = m_rotation * glm::angleAxis(amount, axis);
    m_rotation = glm::quat(amount * axis) * m_rotation;
}

void LE3Transform::setScale(glm::vec3 scale) {
    m_scale = scale;
}
void LE3Transform::setScale(float scale) {
    m_scale = glm::vec3(scale);
}

void LE3Transform::lookAt(glm::vec3 target) {

}

void LE3Transform::disableZ() {
    m_rotation.z = 0.f;
    // glm::vec3 right = glm::cross(getForward(), glm::vec3(0.f, 1.f, 0.f));
    // glm::vec3 up = glm::cross(right, getForward());
    // glm::vec3 badUp = getUp();
    // m_rotation = rotationBetweenVectors(badUp, up) * m_rotation;
}

glm::quat LE3Transform::rotationBetweenVectors(glm::vec3 start, glm::vec3 dest){
	start = glm::normalize(start);
	dest = glm::normalize(dest);

	float cosTheta = glm::dot(start, dest);
	glm::vec3 rotationAxis;

	if (cosTheta < -1 + 0.001f){
		rotationAxis = glm::cross(glm::vec3(0.0f, 0.0f, 1.0f), start);
		if (glm::length2(rotationAxis) < 0.001 )
			rotationAxis = glm::cross(glm::vec3(1.0f, 0.0f, 0.0f), start);

		rotationAxis = glm::normalize(rotationAxis);
		return glm::angleAxis(glm::radians(180.0f), rotationAxis);
        
	}

	rotationAxis = glm::cross(start, dest);

	float s = sqrt( (1+cosTheta)*2 );
	float invs = 1 / s;

	return glm::quat(
		s * 0.5f, 
		rotationAxis.x * invs,
		rotationAxis.y * invs,
		rotationAxis.z * invs
	);

}
