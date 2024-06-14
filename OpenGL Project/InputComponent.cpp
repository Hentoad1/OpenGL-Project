
#include "pch.h"
#include "InputComponent.h"

InputComponent::InputComponent(ComponentData* _cData, const ComponentMeta* _cMeta) : cData(_cData) {}

void InputComponent::Update(const FrameData& input) {
	/* --------------------------------- PROCESS MOUSE INPUT --------------------------------- */

	const Orientation& InitialOrientation = cData->bounds.GetOrientation();

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

	cData->bounds.SetOrientation(Orientation(yaw, pitch, roll));

	/* --------------------------------- PROCESS USER INPUT ---------------------------------- */

	if (input.JUMP == GLFW_PRESS || input.JUMP == GLFW_REPEAT) {
		cData->velocity += glm::vec3(0, 1, 0);
	}

	if (input.CROUCH == GLFW_PRESS || input.CROUCH == GLFW_REPEAT) {
#ifdef ENGINE_SETTING_DISPLAY_MODEL
		cData->velocity += glm::vec3(0, -1, 0);
#endif
	}

	if (input.WALK_FORWARD == GLFW_PRESS || input.WALK_FORWARD == GLFW_REPEAT) {
		glm::vec3 abs = cData->bounds.ConvertAbsolute(glm::vec3(1, 0, 0));
		abs.y = 0;

		cData->velocity += glm::normalize(abs);
	}
	else if (input.WALK_BACKWARD == GLFW_PRESS || input.WALK_BACKWARD == GLFW_REPEAT) {
		glm::vec3 abs = cData->bounds.ConvertAbsolute(glm::vec3(-1, 0, 0));
		abs.y = 0;

		cData->velocity += glm::normalize(abs);
	}

	if (input.WALK_LEFT == GLFW_PRESS || input.WALK_LEFT == GLFW_REPEAT) {
		glm::vec3 abs = cData->bounds.ConvertAbsolute(glm::vec3(0, 0, -1));
		abs.y = 0;

		cData->velocity += glm::normalize(abs);
	}
	else if (input.WALK_RIGHT == GLFW_PRESS || input.WALK_RIGHT == GLFW_REPEAT) {
		glm::vec3 abs = cData->bounds.ConvertAbsolute(glm::vec3(0, 0, 1));
		abs.y = 0;

		cData->velocity += glm::normalize(abs);
	}

	if (input.INTERACT == GLFW_PRESS || input.INTERACT == GLFW_REPEAT) {

#ifdef ENGINE_SETTING_DISPLAY_MODEL

		Scene::AddLight(glslLightSource{ true, cData->camera->GetPosition(), 100.0f, 0, 0.01, glm::vec3(1), glm::vec3(0.1), glm::vec3(1) });

#endif
	}
}