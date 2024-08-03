
#include "pch.h"
#include "RenderComponent.h"

#include "Shader.h"

RenderComponent::RenderComponent(ComponentData* cData, const ComponentMeta* cMeta, Model* _model, const AnimationComponent* anim) : model(_model), animComp(anim) {

	model->Attach();

	auto z = model->GetSBB();

	if (cMeta->has(MESH_SHADERTYPE_BASIC)) {
		shader = (ShaderProgram*)(new BasicShader(cData->camera, model->GetSBB()->center));
	}
	else if (cMeta->has(MESH_SHADERTYPE_SKELETAL)) {
		shader = (ShaderProgram*)(new SkeletalShader(cData->camera, model->GetSBB()->center));
	}


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