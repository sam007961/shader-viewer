//#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"
#include "Constants.h"

Camera::Camera() : projMatrix(1) {}

void Camera::lookAt(glm::vec3 at) {
	const glm::vec3 zaxis(0, 0, 1); // z axis
	const glm::vec3 yaxis(0, 1, 0); // y axis
	
	glm::vec3 forward = glm::normalize(rbt.translation - at); // forward vector
	float dot = glm::dot(zaxis, forward);

	if (dot <= -1 + EPS) 
		rbt.rotation = glm::angleAxis(PI, yaxis); // 180 degree rotaion

	rbt.rotation = glm::normalize(glm::quat(1 + dot, glm::cross(zaxis, forward))); // halfway quat
}

void Camera::lookAt(float x, float y, float z) { lookAt(glm::vec3(x, y, z)); }

void Camera::perspective(float yfov, float aspect, float znear, float zfar) {
	projMatrix = glm::perspective(yfov, aspect, znear, zfar);
}

void Camera::orthogonal(float left, float right, float bottom, float top, float znear, float zfar) {
	projMatrix = glm::ortho(left, right, bottom, top, znear, zfar);
}

glm::mat4 Camera::makeViewMatrix() const {
	return glm::inverse(rbt.toMat4());
}

glm::mat4 Camera::makeProjMatrix() const {
	return projMatrix;
}
