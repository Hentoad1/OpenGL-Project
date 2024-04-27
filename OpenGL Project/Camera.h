#pragma once

#include "pch.h"
#include "EngineInternal.h"
#include "Orientation.h"

class Camera {

public:
	Camera();

	void Move(const glm::vec3&);
	void MoveAbsolute(const glm::vec3&);
	void SetPosition(const glm::vec3&);
	void Rotate(const glm::vec3&);
	void SetOrientation(const Orientation&);

	const glm::mat4& GetView() const;
	const glm::mat4& GetProjection() const;
	const glm::mat4& GetViewAndProjection() const;
	const glm::vec3& GetPosition() const;
	const Orientation& GetOrientation() const;

#ifdef ENGINE_SETTING_DISPLAY_MODEL
	//Light position for view mesh
	glm::vec3 LightPos = glm::vec3(0, 0, 100);
#endif

private:
	void CalculateView();

	Orientation orientation;
	AxisVectors RelativeAxis;

	glm::vec3 position;

	//mat4x4 for shaders
	glm::mat4 view;
	glm::mat4 projection;

	glm::mat4 viewProjection;
};