
#include "pch.h"

#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(const Model* m) : skeleton(){
    skeleton = m->GetSkeleton();
}

void AnimationComponent::SetAnimation(Animation* anim) {
    currentAnimation = anim;
}

void AnimationComponent::Update(const FrameData& data) {

    FinalBoneTransforms.fill(glm::mat4(1));

    if (currentAnimation != nullptr) {

        currentAnimation->Update(data);

        CalculateBoneTransform(skeleton->GetRoot(), glm::mat4(1.0f));

        //std::cout << "---------------------------------" << std::endl;

        for (int i = 0; i < MAX_BONES; ++i) {
            //std::cout << i << ": " << glm::to_string(FinalBoneTransforms[i]) << std::endl << std::endl;

            if (FinalBoneTransforms[i] == glm::mat4(0)) {
                //std::cout << i << std::endl;
            }
        }
    }

}

void AnimationComponent::CalculateBoneTransform(Bone* bone, const glm::mat4& parentTransform) {

    const glm::mat4& nodeTransform = bone->localTransform;
    const glm::mat4& offset = bone->offset;

    const glm::mat4 globalTransform = (parentTransform * nodeTransform);

    FinalBoneTransforms[bone->index] = globalTransform * offset;

    for (int i = 0; i < bone->children.size(); ++i) {
        CalculateBoneTransform(bone->children[i], globalTransform);
    }
}

const std::array<glm::mat4, MAX_BONES>& AnimationComponent::GetFinalBoneTransforms() const {
    return FinalBoneTransforms;
}