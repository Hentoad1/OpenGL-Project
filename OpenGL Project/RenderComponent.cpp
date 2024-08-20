
#include "pch.h"
#include "RenderComponent.h"

#include "Shader.h"

RenderComponent::RenderComponent(ComponentData* cData, const ComponentMeta* cMeta, Model* _model, ShaderProgram* _shader, const AnimationComponent* anim) : model(_model), animComp(anim), shader(_shader) {
	model->Attach();
}

RenderComponent::~RenderComponent() {

}

void RenderComponent::Render() {

	shader->Use();
	
	//should check shaderType
	if (animComp != nullptr) {
		shader->setMat4s("finalBonesMatrices", MAX_BONES, animComp->GetFinalBoneTransforms().data());
	}

	shader->SetPosition(glm::mat4(1.0f));

	shader->Update();

	model->Render(shader);
}