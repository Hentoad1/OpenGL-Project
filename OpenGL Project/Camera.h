#pragma once

#include "pch.h"
#include "Config.h"

class Camera {

public:
	Camera();

	void Move(float, float, float);

	void Rotate(float, float);

	glm::mat4 GetView() const;

	glm::mat4 GetProjection() const;

	glm::mat4 GetViewAndProjection() const;

	glm::vec3 GetPosition() const;
	glm::vec3 GetDirection() const;

#ifdef ENGINE_SETTING_DISPLAY_MODEL
	//Light position for view mesh
	glm::vec3 LightPos = glm::vec3(0, 0, 100);
#endif

private:
	void CalculateView();

	void CalculateAxis();

	float yaw;
	float pitch;

	//data about camera position
	glm::vec3 orientation;
	glm::vec3 position;

	glm::vec3 cameraUp;
	glm::vec3 cameraRight;
	glm::vec3 cameraFront;

	//mat4x4 for shaders
	glm::mat4 view;
	glm::mat4 projection;

	glm::mat4 viewProjection;
};