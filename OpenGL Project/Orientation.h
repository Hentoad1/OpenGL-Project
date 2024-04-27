#pragma once

#include "pch.h"

struct AxisVectors {
	AxisVectors() {}

	AxisVectors(const glm::vec3& _Front, const glm::vec3& _Right, const glm::vec3& _Up) : Front(_Front), Right(_Right), Up(_Up) {}

	glm::vec3 Front;
	glm::vec3 Right;
	glm::vec3 Up;
};

class Orientation {

public:
	Orientation();

	Orientation(const glm::vec3&);

	Orientation(float, float, float);

	const glm::vec3& YawPitchRoll() const;

	const AxisVectors& GetAxis() const;

	void SetYaw(float);
	float GetYaw() const;

	void SetPitch(float);
	float GetPitch() const;

	void SetRoll(float);
	float GetRoll() const;

	//use this to create trnsofrmation matrices
	//https://msl.cs.uiuc.edu/planning/node102.html

private:
	float yaw;
	float pitch;
	float roll;
};