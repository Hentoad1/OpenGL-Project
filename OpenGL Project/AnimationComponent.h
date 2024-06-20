#pragma once

#include "pch.h"

#include "EngineInternal.h"

#include "Skeleton.h"
#include "Animation.h"

#include "Shader.h"

#include "ModelData.h"


class AnimationComponent {
public:
	AnimationComponent(const ModelBuffers*);

	void Update(const FrameData&);

	void SetAnimation(Animation*);

	const std::array<glm::mat4, MAX_BONES>& GetFinalBoneTransforms() const;

private:

	void CalculateBoneTransform(Bone*, const glm::mat4&);

	std::array<glm::mat4, MAX_BONES> FinalBoneTransforms;

	Animation* currentAnimation;
	Skeleton* skeleton;
};