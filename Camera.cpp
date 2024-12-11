#include "Camera.h"

Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraFront, glm::vec3 cameraUp, float yaw, float pitch, float fov) {
	this->cameraPosition = cameraPosition;
	this->cameraFront = cameraFront;
	this->cameraUp = cameraUp;
	this->yaw = yaw;
	this->pitch = pitch;
	this->fov = fov;
	this->viewMatrix = glm::mat4(1.0f);
	this->viewMatrix = glm::mat4(1.0f);
}

void Camera::moveFowrard(float cameraSpeed) {
	this->cameraPosition += cameraSpeed * this->cameraFront;
}
void Camera::moveBackward(float cameraSpeed) {
	this->cameraPosition -= cameraSpeed * this->cameraFront;
}
void Camera::moveLeft(float cameraSpeed) {
	this->cameraPosition -= glm::normalize(glm::cross(this->cameraFront, this->cameraUp)) * cameraSpeed;
}
void Camera::moveRight(float cameraSpeed) {
	this->cameraPosition += glm::normalize(glm::cross(this->cameraFront, this->cameraUp)) * cameraSpeed;
}
void Camera::moveMousePosition(glm::vec3 front) {
	this->cameraFront = glm::normalize(front);
}

glm::mat4 Camera::getCamera(void) const {
	return this->viewMatrix;
}

glm::mat4 Camera::getProjection(void) const {
	return this->projectionMatrix;
}

glm::vec3 Camera::getCameraFront(void) const {
	return this->cameraFront;
}

void Camera::updateViewMatrix() {
	this->viewMatrix = glm::lookAt(this->cameraPosition, this->cameraPosition + this->cameraFront, this->cameraUp);

	this->notify(EventType::Camera, this);
}

void Camera::updateProjectionMatrix(GLFWwindow* window) {
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);

	this->projectionMatrix = glm::perspective(glm::radians(this->fov), ratio, 0.1f, 200.0f);

	this->notify(EventType::Camera, this);
}














