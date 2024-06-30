#include "pch.h"

#include "Animation.h"


KeyFrame::KeyFrame(const KeyFrame& ref) {
	//throw;

	bone = ref.bone;


	numPositionFrames = ref.numPositionFrames;
	positionFrames = new PositionKeyFrame[numPositionFrames]();

	for (int i = 0; i < numPositionFrames; ++i) {
		positionFrames[i] = PositionKeyFrame(ref.positionFrames[i]);
	}


	numOrientationFrames = ref.numOrientationFrames;
	orientationFrames = new OrientationKeyFrame[numOrientationFrames]();

	for (int i = 0; i < numOrientationFrames; ++i) {
		orientationFrames[i] = OrientationKeyFrame(ref.orientationFrames[i]);
	}


	numScaleFrames = ref.numScaleFrames;
	scaleFrames = new ScaleKeyFrame[numScaleFrames]();

	for (int i = 0; i < numScaleFrames; ++i) {
		scaleFrames[i] = ScaleKeyFrame(ref.scaleFrames[i]);
	}

	throw;
}

KeyFrame::~KeyFrame() {
	delete[] positionFrames;
	delete[] orientationFrames;
	delete[] scaleFrames;
}

KeyFrame::KeyFrame(const aiNodeAnim* channel, Bone* b) : 
	bone(b), 
	numPositionFrames(channel->mNumPositionKeys),
	numOrientationFrames(channel->mNumRotationKeys),
	numScaleFrames(channel->mNumScalingKeys)
{
	positionFrames = new PositionKeyFrame[numPositionFrames]();
	orientationFrames = new OrientationKeyFrame[numOrientationFrames]();
	scaleFrames = new ScaleKeyFrame[numScaleFrames]();

	for (int i = 0; i < numPositionFrames; ++i) {
		positionFrames[i] = PositionKeyFrame{ aiVector3DToGlm(channel->mPositionKeys[i].mValue), channel->mPositionKeys[i].mTime };
	}

	for (int i = 0; i < numOrientationFrames; ++i) {
		orientationFrames[i] = OrientationKeyFrame{ aiQuatToGlm(channel->mRotationKeys[i].mValue), channel->mRotationKeys[i].mTime};
	}

	for (int i = 0; i < numScaleFrames; ++i) {
		scaleFrames[i] = ScaleKeyFrame{ aiVector3DToGlm(channel->mScalingKeys[i].mValue), channel->mScalingKeys[i].mTime};
	}
}

KeyFrame::KeyFrame(
	Bone* _bone,
	int _numPositionFrames,
	PositionKeyFrame* _positionFrames,
	int _numOrientationFrames,
	OrientationKeyFrame* _orientationFrames,
	int _numScaleFrames,
	ScaleKeyFrame* _scaleFrames
) : 
	bone(_bone),
	numPositionFrames(_numPositionFrames),
	positionFrames(_positionFrames),
	numOrientationFrames(_numOrientationFrames),
	orientationFrames(_orientationFrames),
	numScaleFrames(_numScaleFrames),
	scaleFrames(_scaleFrames)
{};

Animation::Animation(const aiAnimation* anim, Skeleton* _skeleton) : skeleton(_skeleton), duration(anim->mDuration), duration_played(0) {
	
	KeyFrames.reserve(anim->mNumChannels);

	for (int i = 0; i < anim->mNumChannels; ++i) {
		const aiNodeAnim* channel = anim->mChannels[i];

		Bone* bone = skeleton->GetBone(channel->mNodeName);

		if (bone != nullptr) {
			KeyFrames.emplace_back(channel, bone);
		}
	}

	
}

Animation::Animation(double _duration, double _duration_played, int _ticksPerSecond, Skeleton* _skeleton, const std::vector<KeyFrame>& _keyframes) : 
	duration(_duration),
	duration_played(_duration_played),
	ticksPerSecond(_ticksPerSecond),
	skeleton(_skeleton),
	KeyFrames(_keyframes)
{}

static float GetScaleFactor(float lastTimeStamp, float nextTimeStamp, float animationTime)
{
	float scaleFactor = 0.0f;
	float midWayLength = animationTime - lastTimeStamp;
	float framesDiff = nextTimeStamp - lastTimeStamp;
	scaleFactor = midWayLength / framesDiff;
	return scaleFactor;
}


void Animation::Update(const FrameData& fData) {
	
	duration_played += fData.DeltaTime * 200;

	if (duration_played > duration) {

		duration_played = std::fmod(duration_played, duration);

		std::cout << "looped!" << std::endl;
	}

	for (int i = 0; i < KeyFrames.size(); ++i) {
		KeyFrame& frame = KeyFrames[i];

		glm::mat4 translation;
		glm::mat4 rotation;
		glm::mat4 scale;

		/* ---------------------------- INTERPOLATE POSITION ---------------------------- */

		if (frame.numPositionFrames == 1) {
			translation = glm::translate(glm::mat4(1.0f), frame.positionFrames[0].position);
		}
		else {

			int keyframeIndex = -1;

			for (int i = 0; i < frame.numPositionFrames - 1; ++i) {
				if (duration_played < frame.positionFrames[i + 1].time) {
					keyframeIndex = i;
					break;
				}
			}

			if (keyframeIndex != -1) {
				float scaleFactor = GetScaleFactor(frame.positionFrames[keyframeIndex].time, frame.positionFrames[keyframeIndex + 1].time, duration_played);


				glm::vec3 finalPosition = glm::mix(frame.positionFrames[keyframeIndex].position, frame.positionFrames[keyframeIndex + 1].position, scaleFactor);


				translation = glm::translate(glm::mat4(1.0f), finalPosition);
			}
		}

		/* ---------------------------- INTERPOLATE ORIENTATION ---------------------------- */

		if (frame.numOrientationFrames == 1) {
			translation = mat4_cast(glm::normalize(frame.orientationFrames[0].orientation));
		}
		else {

			int keyframeIndex = -1;

			for (int i = 0; i < frame.numOrientationFrames - 1; ++i) {
				if (duration_played < frame.orientationFrames[i + 1].time) {
					keyframeIndex = i;
					break;
				}
			}

			if (keyframeIndex != -1) {
				float scaleFactor = GetScaleFactor(frame.orientationFrames[keyframeIndex].time, frame.orientationFrames[keyframeIndex + 1].time, duration_played);

				glm::quat finalRotation = glm::slerp(frame.orientationFrames[keyframeIndex].orientation, frame.orientationFrames[keyframeIndex + 1].orientation, scaleFactor);


				finalRotation = glm::normalize(finalRotation);

				rotation = glm::mat4_cast(finalRotation);
			}
		}

		/* ---------------------------- INTERPOLATE SCALE ---------------------------- */

		if (frame.numScaleFrames == 1) {
			translation = glm::translate(glm::mat4(1.0f), frame.scaleFrames[0].scale);
		}
		else {

			int keyframeIndex = -1;

			for (int i = 0; i < frame.numScaleFrames - 1; ++i) {
				if (duration_played < frame.scaleFrames[i + 1].time) {
					keyframeIndex = i;
					break;
				}
			}

			if (keyframeIndex != -1) {
				float scaleFactor = GetScaleFactor(frame.scaleFrames[keyframeIndex].time, frame.scaleFrames[keyframeIndex + 1].time, duration_played);


				glm::vec3 finalPosition = glm::mix(frame.scaleFrames[keyframeIndex].scale, frame.scaleFrames[keyframeIndex + 1].scale, scaleFactor);


				scale = glm::translate(glm::mat4(1.0f), finalPosition);
			}
		}

		frame.bone->localTransform = translation * rotation * scale;
	}

	/*
	write this

	keyframes is a vector that has all the keyframe data with associated bones

	just have to calculate the transform matrices and shit
	
	*/

}