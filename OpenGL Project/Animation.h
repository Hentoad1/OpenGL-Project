#pragma once

#include "pch.h"

#include "Skeleton.h"
#include "EngineInternal.h"

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

	KeyFrame(const KeyFrame& ref);

	~KeyFrame();

	KeyFrame(const aiNodeAnim*, Bone*);

	Bone* bone;

	int numPositionFrames;
	PositionKeyFrame* positionFrames;

	int numOrientationFrames;
	OrientationKeyFrame* orientationFrames;

	int numScaleFrames;
	ScaleKeyFrame* scaleFrames;

};

class Animation {
private:

	double duration;
	double duration_played;

	int ticksPerSecond;

	glm::mat4 globalInverse;
	
	Skeleton* skeleton;

	std::vector<KeyFrame> KeyFrames;

public:

	Animation(const aiAnimation* anim, Skeleton* skeleton);

	void Update(const FrameData&);

};