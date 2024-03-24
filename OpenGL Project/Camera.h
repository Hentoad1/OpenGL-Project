#pragma once

class Camera {

public:
	Camera();

	void Zoom(double amount);

	void Rotate(bool horizontal, float radians);

	glm::mat4 GetView() const;

	glm::mat4 GetProjection() const;

	glm::mat4 GetViewAndProjection() const;

private:
	void CalculateVectors();

	float CAMERA_DISTANCE = 50.0f;

	float CAMERA_HORIZONTAL_ROTATION = 0.0f;
	float CAMERA_VERITCAL_ROTATION = 0.0f;

	glm::vec3 position;

	glm::mat4 view;
	glm::mat4 projection;

	glm::mat4 viewProjection;
};