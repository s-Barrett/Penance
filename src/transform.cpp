#include "transform.h"
#include <glm/fwd.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

Transform::Transform()
    : m_Position(0.0f, 0.0f, 0.0f), m_Rotation(glm::identity<glm::quat>()),
      m_Scale(1.0f, 1.0f, 1.0f), m_ModelMatrix(1.0f), m_Dirty(true) {}

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

void Transform::setScale(const glm::vec3 &scale) {
  m_Scale = scale;
  m_Dirty = true;
}

const glm::vec3 &Transform::getScale() const { return m_Scale; }

const glm::mat4 &Transform::getModelMatrix() {
  if (m_Dirty) {
    glm::mat4 T = glm::translate(glm::mat4(1.0f), m_Position);
    glm::mat4 R = glm::toMat4(m_Rotation);
    glm::mat4 S = glm::scale(glm::mat4(1.0f), m_Scale);

    m_ModelMatrix = T * R * S;
    m_Dirty = false;
  }

  return m_ModelMatrix;
}
