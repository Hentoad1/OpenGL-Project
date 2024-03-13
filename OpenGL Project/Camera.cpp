
#include "pch.h"
#include "Camera.h"

#include "Screen.h"

Camera::Camera() {
	projection = glm::perspective(FOV, SCREEN_WIDTH_F / SCREEN_HEIGHT_F, CLIPPING_MIN, CLIPPING_MAX);

	CalculateVectors();
}

void Camera::Zoom(double amount) {
	CAMERA_DISTANCE = std::max(CAMERA_MIN_DISTANCE, (float)(CAMERA_DISTANCE + amount));

	CalculateVectors();
}

void Camera::Rotate(bool horizontal, float radians) {

	if (horizontal) {
		CAMERA_HORIZONTAL_ROTATION = (float)std::fmod(CAMERA_HORIZONTAL_ROTATION + radians, 360);
	}
	else {
		CAMERA_VERITCAL_ROTATION += radians;
		CAMERA_VERITCAL_ROTATION = std::min(CAMERA_VERITCAL_ROTATION, CAMERA_VERTICAL_MAX);
		CAMERA_VERITCAL_ROTATION = std::max(CAMERA_VERITCAL_ROTATION, -CAMERA_VERTICAL_MAX);
	}

	CalculateVectors();
}

void Camera::CalculateVectors() {
	float horizontalDistance = cos(CAMERA_VERITCAL_ROTATION) * CAMERA_DISTANCE;
	float cameraY = sin(CAMERA_VERITCAL_ROTATION) * CAMERA_DISTANCE;

	float cameraX = cos(CAMERA_HORIZONTAL_ROTATION) * horizontalDistance;
	float cameraZ = sin(CAMERA_HORIZONTAL_ROTATION) * horizontalDistance;

	glm::vec3 position = WORLD_ORIGIN + glm::vec3(
		cameraX, cameraY, cameraZ
	);

	view = glm::lookAt(position, WORLD_ORIGIN, TOP);
	viewProjection = view * projection;
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