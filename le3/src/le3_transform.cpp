#include "le3_transform.h"
using namespace le3;

#include <glm/gtc/quaternion.hpp>
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

glm::vec3 LE3Transform::getPosition() const {
    return m_position;
}
glm::quat LE3Transform::getRotation() const {
    return m_rotation;
}
glm::vec3 LE3Transform::getScale() const {
    return m_scale;
}

glm::vec3 LE3Transform::getForward() const {
    return m_rotation * glm::vec3(0.f, 0.f, -1.f);
}
glm::vec3 LE3Transform::getRight() const {
    return m_rotation * glm::vec3(1.f, 0.f, 0.f);
}
glm::vec3 LE3Transform::getUp() const {
    return m_rotation * glm::vec3(0.f, 1.f, 0.f);
}

void LE3Transform::setPosition(glm::vec3 position) {
    m_position = position;
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

void LE3Transform::setRotationRPY(float roll, float pitch, float yaw) {
    m_rotation = glm::quat(glm::vec3(pitch, yaw, roll));
}
void LE3Transform::addRotationRPY(float roll, float pitch, float yaw) {
    glm::vec3 angles = glm::vec3(pitch, yaw, roll) + glm::eulerAngles(m_rotation);
    if (angles.x > glm::radians(89.9f)) angles.x = glm::radians(89.9f);
    if (angles.x < glm::radians(-89.9f)) angles.x = glm::radians(-89.9f);
    if (angles.y > glm::radians(181.f)) angles.y = glm::radians(-179.f);
    if (angles.y < glm::radians(-181.f)) angles.y = glm::radians(179.f);
    // angles.z = 0.f;

    m_rotation = glm::quat(angles);

    if (glm::eulerAngles(m_rotation).z > 0.5f) {
        int i = 0;
    }
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
