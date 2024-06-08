
#include "pch.h"
#include "InputComponent.h"

InputComponent::InputComponent(ComponentData* _cData, const ComponentMeta* _cMeta) : cData(_cData) {}

void InputComponent::Update(const FrameData& input) {
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
		cData->camera->LightPos = cData->bounds.Position();
#endif
	}
}