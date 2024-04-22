#include "pch.h"

#include "Camera.h"
#include "Screen.h"

static constexpr glm::vec3 GLOBAL_UP = glm::vec3(0.0f, 1.0f, 0.0f);
//static constexpr glm::vec3 GLOBAL_RIGHT = glm::normalize(glm::cross(GLOBAL_UP, cameraDirection));

//static const glm::quat QUAT_GLOBAL_UP = glm::normalize(glm::quat(glm::vec3(0.0f, 1.0f, 0.0f)));
//static const glm::quat QUAT_GLOBAL_RIGHT = glm::normalize(glm::quat(glm::vec3(1.0f, 0.0f, 0.0f)));

//static const float PI = std::atan(1) * 4;

static constexpr float FOV = glm::radians(70.0f);

static constexpr float CLIPPING_MIN = 0.1f;
static constexpr float CLIPPING_MAX = 1000.0f;

Camera::Camera() {
	projection = glm::perspective(FOV, SCREEN_WIDTH_F / SCREEN_HEIGHT_F, CLIPPING_MIN, CLIPPING_MAX);

	position = glm::vec3(250, 0, 0);
	orientation = glm::vec3(-1, 0 ,0);

	yaw = 180;
	pitch = 0;

	CalculateAxis();
	CalculateView();
}

/*
*/

void Camera::MoveAbsolute(float x, float y, float z) {

	position += glm::vec3(x, y, z);

	CalculateView();
}

void Camera::Move(float x, float y, float z) {

	glm::vec3 deltaPos = 
		(glm::vec3(x) * cameraFront) +
		(glm::vec3(y) * cameraUp) +
		(glm::vec3(z) * cameraRight);

	position += deltaPos;

	CalculateView();
}

void Camera::Rotate(float y, float p) {
	yaw += y;
	pitch += p;

	if (pitch > 89.0f) {
		pitch = 89.0f;
	}else if (pitch < -89.0f) {
		pitch = -89.0f;
	}

	std::cout << "yaw: " << yaw << std::endl;
	std::cout << "pitch: " << pitch << std::endl;

	CalculateAxis();
	CalculateView();
}

void Camera::CalculateAxis() {
	cameraFront = glm::normalize(glm::vec3(
		cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
		sin(glm::radians(pitch)),
		sin(glm::radians(yaw)) * cos(glm::radians(pitch))
	));

	cameraRight = glm::normalize(glm::cross(cameraFront, GLOBAL_UP));
	cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
}

void Camera::CalculateView() {
	view = glm::lookAt(position, position + cameraFront, GLOBAL_UP);

	viewProjection = view * projection;
}

glm::vec3 Camera::GetPosition() const {
	return position;
}

glm::vec3 Camera::GetDirection() const {
	return orientation;
}

glm::mat4 Camera::GetView() const {
	return view;
}

glm::mat4 Camera::GetProjection() const {
	return projection;
}

glm::mat4 Camera::GetViewAndProjection() const {
	return viewProjection;
}