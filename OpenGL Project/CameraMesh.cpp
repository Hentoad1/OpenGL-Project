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

void CameraMesh::Update(const FrameData& input) {


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

	/* --------------------------------- PROCESS USER INPUT ---------------------------------- */

	if (input.JUMP == GLFW_PRESS || input.JUMP == GLFW_REPEAT) {
		velocity += glm::vec3(0, 1, 0);
	}

	if (input.CROUCH == GLFW_PRESS || input.CROUCH == GLFW_REPEAT) {
#ifdef ENGINE_SETTING_DISPLAY_MODEL
		velocity += glm::vec3(0, -1, 0);
#endif
	}

	if (input.WALK_FORWARD == GLFW_PRESS || input.WALK_FORWARD == GLFW_REPEAT) {
		glm::vec3 abs = bounds.ConvertAbsolute(glm::vec3(1, 0, 0));
		abs.y = 0;

		velocity += glm::normalize(abs);
	}
	else if (input.WALK_BACKWARD == GLFW_PRESS || input.WALK_BACKWARD == GLFW_REPEAT) {
		glm::vec3 abs = bounds.ConvertAbsolute(glm::vec3(-1, 0, 0));
		abs.y = 0;

		velocity += glm::normalize(abs);
	}

	if (input.WALK_LEFT == GLFW_PRESS || input.WALK_LEFT == GLFW_REPEAT) {
		glm::vec3 abs = bounds.ConvertAbsolute(glm::vec3(0, 0, -1));
		abs.y = 0;

		velocity += glm::normalize(abs);
	}
	else if (input.WALK_RIGHT == GLFW_PRESS || input.WALK_RIGHT == GLFW_REPEAT) {
		glm::vec3 abs = bounds.ConvertAbsolute(glm::vec3(0, 0, 1));
		abs.y = 0;

		velocity += glm::normalize(abs);
	}

	if (input.INTERACT == GLFW_PRESS || input.INTERACT == GLFW_REPEAT) {
#ifdef ENGINE_SETTING_DISPLAY_MODEL
		GetCamera()->LightPos = bounds.Position();
#endif
	}

	PhysicsMesh::Update(input);

	/* ------------------------------- UPDATE ATTACHED CAMERA -------------------------------- */

	Camera* cam = GetCamera();
	const AxisVectors& axis = bounds.GetOrientation().GetAxis();

	const glm::vec3 ModelCenter = bounds.Center();
	const glm::vec3 CameraOffset = axis.Front * -10.0f; //50 units away from player.


	cam->SetPosition(ModelCenter + CameraOffset);
	cam->SetOrientation(bounds.GetOrientation());

}

Camera* CameraMesh::GetCamera() {
	return PhysicsMesh::GetCamera();
}