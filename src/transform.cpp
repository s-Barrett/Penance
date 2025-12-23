#include "transform.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

Transform::Transform() { m_Dirty = true; }

void Transform::setPosition(const glm::vec3 &position) {
  m_Position = position;
  m_Dirty = true;
}

void Transform::translate(const glm::vec3 &delta) {
  m_Position += delta;
  m_Dirty = true;
}

const glm::vec3 &Transform::getPosition() const { return m_Position; }

void Transform::setRotation(const glm::quat &rotation) {
  m_Rotation = rotation;
  m_Dirty = true;
}

void Transform::rotate(const glm::quat &delta) {
  m_Rotation = delta * m_Rotation; // proper quaternion multiplication
  m_Dirty = true;
}

const glm::quat &Transform::getRotation() const { return m_Rotation; }
