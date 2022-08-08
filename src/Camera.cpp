#include "Camera.hpp"
#include "glm/gtc/matrix_transform.hpp"
Camera::Camera() {
	Camera(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f),
	       glm::vec3(0.0f, 1.0f, 0.0f));
}
Camera::Camera(const glm::vec3 &at, const glm::vec3 &to, const glm::vec3 &up)
    : at(at), to(to), up(up) {}

glm::mat4 Camera::look() { return glm::lookAt(at, to, up); }
