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

	KeyFrame() { }

	KeyFrame(const aiNodeAnim*, Bone*);

	KeyFrame(Bone*, int, PositionKeyFrame*, int, OrientationKeyFrame*, int, ScaleKeyFrame*);

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

public:

	double duration;
	double duration_played;

	int ticksPerSecond;

	Skeleton* skeleton;

	std::vector<KeyFrame> KeyFrames;



	Animation(const aiAnimation* anim, Skeleton* skeleton);
	Animation(double, double, int, Skeleton*, const std::vector<KeyFrame>&);

	void Update(const FrameData&);

};