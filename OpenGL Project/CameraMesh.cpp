#include "pch.h"

#include "CameraMesh.h"

CameraMesh::CameraMesh(const std::string& file, Camera* mCam) : PhysicsMesh(file, mCam) {}

CameraMesh::CameraMesh(const BoundingBox& _bounds, Camera* mCam) : PhysicsMesh(_bounds, mCam) {
#ifdef _DEBUG
	GetBoundingBox().BindGL(mCam);
#endif
}

CameraMesh::~CameraMesh() {
	PhysicsMesh::~PhysicsMesh();
}

void CameraMesh::Update(const InputState& input) {


	BoundingBox& bounds = GetBoundingBox();

	/* --------------------------------- PROCESS MOUSE INPUT --------------------------------- */

	const Orientation& InitialOrientation = bounds.GetOrientation();

	float yaw = InitialOrientation.GetYaw();
	float pitch = InitialOrientation.GetPitch();
	float roll = InitialOrientation.GetRoll();

	yaw += input.ADJUSTED_DELTA_CURSOR_POSITION.x;
	pitch += input.ADJUSTED_DELTA_CURSOR_POSITION.y;

	if (pitch > 89.0f) {
		pitch = 89.0f;
	}
	else if (pitch < -89.0f) {
		pitch = -89.0f;
	}

	bounds.SetOrientation(Orientation(yaw, pitch, roll));

	//Has to be recalculated after orientation changes.
	const AxisVectors& axis = bounds.GetOrientation().GetAxis();

	/* --------------------------------- PROCESS USER INPUT ---------------------------------- */

	if (input.JUMP) {
		bounds.MoveAbsolute(glm::vec3(0, 1, 0));
	}

	if (input.WALK_FORWARD) {
		bounds.MoveRelative(glm::vec3(1,0,0));
	}
	else if (input.WALK_BACKWARD) {
		bounds.MoveRelative(glm::vec3(-1, 0, 0));
	}

	if (input.WALK_LEFT) {
		bounds.MoveRelative(glm::vec3(0, 0, -1));
	}
	else if (input.WALK_RIGHT) {
		bounds.MoveRelative(glm::vec3(0, 0, 1));
	}

	if (input.INTERACT) {
#ifdef ENGINE_SETTING_DISPLAY_MODEL
		GetCamera()->LightPos = bounds.Position();
#endif
	}

	if (input.CROUCH) {
#ifdef ENGINE_SETTING_DISPLAY_MODEL
	bounds.MoveAbsolute(glm::vec3(0, -1, 0));
#endif
	}

	/* ------------------------------- UPDATE ATTACHED CAMERA -------------------------------- */

	Camera* cam = GetCamera();

	const glm::vec3 ModelCenter = bounds.Center();
	const glm::vec3 CameraOffset = axis.Front * -50.0f; //50 units away from player.


	cam->SetPosition(ModelCenter + CameraOffset);
	cam->SetOrientation(bounds.GetOrientation());
}

Camera* CameraMesh::GetCamera() {
	return PhysicsMesh::GetCamera();
}