#include "pch.h"
#include "Mesh.h"

Mesh::Mesh(const Mesh& ref) : cMeta(ref.cMeta) {

	throw;
}

Mesh::Mesh(Camera* mCam, Model* model, const ComponentMeta& _cMeta, ShaderProgram* shader) : mCamera(mCam), cMeta(_cMeta) {

	cData = ComponentData{ BoundingBox(model->GetSBB()), mCamera, glm::vec3(0)};

#ifdef _DEBUG
	cData.bounds.BindGL(mCamera);
#endif

	cAnim = cMeta.has(MESH_COMPONENT_ANIMATION) ? new AnimationComponent(model) : nullptr;
	cRender = cMeta.has(MESH_COMPONENT_RENDER) ? new RenderComponent(&cData, &cMeta, model, shader, cAnim) : nullptr;
	cPhysics = cMeta.has(MESH_COMPONENT_PHYSICS) ? new PhysicsComponent(&cData, &cMeta) : nullptr;
	cInput = cMeta.has(MESH_COMPONENT_INPUT) ? new InputComponent(&cData, &cMeta) : nullptr;

	if (cMeta.has(MESH_COMPONENT_ANIMATION)) {
		cAnim->SetAnimation((Animation*)(*model->GetAnimations())[0]);
	}

}

Mesh::~Mesh() {

	if (cMeta.has(MESH_COMPONENT_RENDER)) {
		delete cRender;
	}

	if (cMeta.has(MESH_COMPONENT_PHYSICS)) {
		delete cPhysics;
	}

	if (cMeta.has(MESH_COMPONENT_INPUT)) {
		delete cInput;
	}

	if (cMeta.has(MESH_COMPONENT_ANIMATION)) {
		delete cAnim;
	}
}

void Mesh::SetBoundingBox(const BoundingBox& b) {
	cData.bounds = b;
}

BoundingBox& Mesh::GetBoundingBox() {
	return cData.bounds;
}

void Mesh::Update(const FrameData& fData) {

	if (cMeta.has(MESH_COMPONENT_INPUT)) {
		cInput->Update(fData);
	}

	if (cMeta.has(MESH_COMPONENT_PHYSICS)) {
		cPhysics->Update(fData);
	}

	if (cMeta.has(MESH_COMPONENT_ANIMATION)) {
		cAnim->Update(fData);
	}
}

void Mesh::Render() {

	if (cMeta.has(MESH_COMPONENT_RENDER)) {
		cRender->Render();
	}

#ifdef _DEBUG
	cData.bounds.Render();
#endif

}