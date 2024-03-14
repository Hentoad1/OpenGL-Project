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

	static constexpr glm::vec3 WORLD_ORIGIN = glm::vec3(0.0f, 0.0f, 0.0f);
	static constexpr glm::vec3 FACING = glm::vec3(0.0f, 0.0f, 0.0f);
	static constexpr glm::vec3 TOP = glm::vec3(0.0f, 1.0f, 0.0f);

	static constexpr float FOV = glm::radians(70.0f);

	static constexpr float CLIPPING_MIN = 1.0f;
	static constexpr float CLIPPING_MAX = 1000.0f;


	static constexpr float CAMERA_HEIGHT = 0.5f;

	static constexpr float CAMERA_MIN_DISTANCE = 1.0f;

	static constexpr float CAMERA_VERTICAL_MAX = glm::radians(89.9f);


	float CAMERA_DISTANCE = 50.0f;

	float CAMERA_HORIZONTAL_ROTATION = 0.0f;
	float CAMERA_VERITCAL_ROTATION = 0.0f;

	glm::vec3 position;

	glm::mat4 view;
	glm::mat4 projection;

	glm::mat4 viewProjection;
};