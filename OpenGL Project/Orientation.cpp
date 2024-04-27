#include "pch.h"

#include "Orientation.h"

static constexpr glm::vec3 GLOBAL_UP = glm::vec3(0, 1, 0);

Orientation::Orientation() : yaw(0), pitch(0), roll(0) { }

Orientation::Orientation(float _yaw, float _pitch, float _roll) : yaw(_yaw), pitch(_pitch), roll(_roll) { }

Orientation::Orientation(const glm::vec3& YawPitchRoll) : yaw(YawPitchRoll.x), pitch(YawPitchRoll.y), roll(YawPitchRoll.z) { }

const glm::vec3& Orientation::YawPitchRoll() const {
	return glm::vec3(yaw, pitch, roll);
}

const AxisVectors& Orientation::GetAxis() const {
	glm::vec3 FrontVector = glm::normalize(glm::vec3(
		cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
		sin(glm::radians(pitch)),
		sin(glm::radians(yaw)) * cos(glm::radians(pitch))
	));

	glm::vec3 RightVector = glm::normalize(glm::cross(FrontVector, GLOBAL_UP));
	glm::vec3 UpVector = glm::normalize(glm::cross(RightVector, FrontVector));

	return AxisVectors(FrontVector, RightVector, UpVector);
}

float Orientation::GetYaw() const {
	return yaw;
}

float Orientation::GetPitch() const {
	return pitch;
}

float Orientation::GetRoll() const {
	return roll;
}

void Orientation::SetYaw(float value) {
	yaw = value;
}

void Orientation::SetPitch(float value) {
	pitch = value;
}

void Orientation::SetRoll(float value) {
	roll = value;
}