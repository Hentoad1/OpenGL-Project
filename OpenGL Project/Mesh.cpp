#include "pch.h"
#include "Mesh.h"

Mesh::Mesh(Camera* mCam, const ModelBuffers* mData, const ComponentMeta& _cMeta) : mCamera(mCam), cMeta(_cMeta) {

	cData = ComponentData{ BoundingBox(mData->min, mData->max), mCamera, glm::vec3(0) };

#ifdef _DEBUG
	cData.bounds.BindGL(mCamera);
#endif

	cRender = cMeta.has(MESH_COMPONENT_RENDER) ? new RenderComponent(&cData , &cMeta, mData) : nullptr;
	cPhysics = cMeta.has(MESH_COMPONENT_PHYSICS) ? new PhysicsComponent(&cData, &cMeta) : nullptr;
	cInput = cMeta.has(MESH_COMPONENT_INPUT) ? new InputComponent(&cData, &cMeta) : nullptr;



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

}

void Mesh::Render() {

	if (cMeta.has(MESH_COMPONENT_RENDER)) {
		cRender->Render();
	}

#ifdef _DEBUG
	cData.bounds.Render();
#endif

}