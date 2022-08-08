#pragma once
#include "glm/glm.hpp"
class Camera {
  public:
	Camera();
	Camera(const glm::vec3 &at, const glm::vec3 &to, const glm::vec3 &up);
	glm::vec3 at, to, up;
	glm::mat4 look();
};
