#include "pch.h"

#include "Camera.h"
#include "EngineInternal.h"

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

	orientation.SetYaw(180);
	orientation.SetPitch(0);

	RelativeAxis = orientation.GetAxis();
	CalculateView();
}

/*
*/

void Camera::Move(const glm::vec3& delta) {

	glm::vec3 front = glm::normalize(glm::vec3(RelativeAxis.Front.x, 0, RelativeAxis.Front.z));
	glm::vec3 right = glm::normalize(glm::vec3(RelativeAxis.Right.x, 0, RelativeAxis.Right.z));

	glm::vec3 deltaPos = 
		(glm::vec3(delta.x) * front) +
		(glm::vec3(delta.z) * right);

	deltaPos.y = 0;

	position += deltaPos;

	CalculateView();
}

void Camera::MoveAbsolute(const glm::vec3& delta) {
	position += delta;

	CalculateView();
}

void Camera::SetPosition(const glm::vec3& pos) {
	position = pos;
}

void Camera::Rotate(const glm::vec3& rot) {
	float yaw = orientation.GetYaw();
	float pitch = orientation.GetPitch();
	
	yaw += rot.x;
	pitch += rot.y;

	if (pitch > 89.0f) {
		pitch = 89.0f;
	}else if (pitch < -89.0f) {
		pitch = -89.0f;
	}

	orientation.SetYaw(yaw);
	orientation.SetPitch(pitch);

	RelativeAxis = orientation.GetAxis();
	CalculateView();
}

void Camera::SetOrientation(const Orientation& other) {
	orientation = other;

	RelativeAxis = orientation.GetAxis();
	CalculateView();
}

void Camera::CalculateView() {
	view = glm::lookAt(position, position + RelativeAxis.Front, GLOBAL_UP);

	viewProjection = view * projection;
}

const glm::vec3& Camera::GetPosition() const {
	return position;
}

const Orientation& Camera::GetOrientation() const {
	return orientation;
}

const glm::mat4& Camera::GetView() const {
	return view;
}

const glm::mat4& Camera::GetProjection() const {
	return projection;
}

const glm::mat4& Camera::GetViewAndProjection() const {
	return viewProjection;
}
