#pragma once

#include "pch.h"

struct PositionKeyFrame {
	glm::vec3 position;
	double time;
};

struct OrientationKeyFrame {
	glm::quat orientation;
	double time;
};

struct ScaleKeyFrame {
	glm::vec3 scale;
	double time;
};

struct KeyFrame {

	uint32_t boneIndex;

	std::vector<PositionKeyFrame> positionFrames;

	std::vector<OrientationKeyFrame> orientationFrames;

	std::vector<ScaleKeyFrame> scaleFrames;

};

struct Animation {
	double duration;
	double duration_played;

	uint32_t ticksPerSecond;

	std::vector<KeyFrame> KeyFrames;
};