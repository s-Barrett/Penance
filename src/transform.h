#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/mat4x4.hpp>

class Transform {
public:
  Transform();

  void setPosition(const glm::vec3 &position);
  void translate(const glm::vec3 &delta);
  const glm::vec3 &getPosition() const;

  void setRotation(const glm::quat &rotation);
  void rotate(const glm::quat &delta);
  const glm::quat &getRotation() const;

  void setScale(const glm::vec3 &scale);
  const glm::vec3 &getScale() const;

  const glm::mat4 &getModelMatrix() const;

private:
  glm::vec3 m_Position{0.0f};
  glm::vec3 m_Scale{1.0f};
  glm::quat m_Rotation{1.0f, 0.0f, 0.0f, 0.0f};

  mutable glm::mat4 m_ModelMatrix{1.0f};
  mutable bool m_Dirty = true;
};
