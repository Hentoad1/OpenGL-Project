#pragma once

#pragma once

#include "pch.h"
#include "Screen.h"

static constexpr uint8_t AXIS_X = 1;
static constexpr uint8_t AXIS_Y = 2;
static constexpr uint8_t AXIS_Z = 3;

static constexpr uint8_t ROTATE_UP = 1;
static constexpr uint8_t ROTATE_DOWN = 2;
static constexpr uint8_t ROTATE_LEFT = 3;
static constexpr uint8_t ROTATE_RIGHT = 4;

namespace Camera {

	namespace {
		static constexpr glm::vec3 WORLD_ORIGIN = glm::vec3(0.0f, 0.0f, 0.0f);
		static constexpr glm::vec3 FACING = glm::vec3(0.0f, 0.0f, 0.0f);
		static constexpr glm::vec3 TOP = glm::vec3(0.0f, 1.0f, 0.0f);

		static constexpr float FOV = glm::radians(45.0f);

		static constexpr float CLIPPING_MIN = 1.0f;
		static constexpr float CLIPPING_MAX = 1000.0f;


		static constexpr float CAMERA_HEIGHT = 0.4f;

		float CAMERA_DISTANCE = 10.0f;
		static constexpr float CAMERA_MIN_DISTANCE = 3.0f;


		float CAMERA_HORIZONTAL_ROTATION = 0.0f;

		float CAMERA_VERITCAL_ROTATION = 0.0f;
		static constexpr float CAMERA_VERTICAL_MAX = glm::radians(89.9f);

		glm::vec3 position;

		glm::mat4 view;
		glm::mat4 projection;
	}

	void UpdatePosition() {
		float horizontalDistance = cos(CAMERA_VERITCAL_ROTATION) * CAMERA_DISTANCE;
		float cameraY = sin(CAMERA_VERITCAL_ROTATION) * CAMERA_DISTANCE;

		float cameraX = cos(CAMERA_HORIZONTAL_ROTATION) * horizontalDistance;
		float cameraZ = sin(CAMERA_HORIZONTAL_ROTATION) * horizontalDistance;

		glm::vec3 position = WORLD_ORIGIN + glm::vec3(
			cameraX, cameraY, cameraZ
		);

		view = glm::lookAt(position, WORLD_ORIGIN, TOP);
	}

	void Create() {
		projection = glm::perspective(FOV, SCREEN_WIDTH_F / SCREEN_HEIGHT_F, CLIPPING_MIN, CLIPPING_MAX);

		UpdatePosition();
	}


	void Zoom(double amount) {
		CAMERA_DISTANCE = std::max(CAMERA_MIN_DISTANCE, (float)(CAMERA_DISTANCE + amount));

		UpdatePosition();
	}

	void Rotate(bool horizontal, float radians) {

		if (horizontal) {
			CAMERA_HORIZONTAL_ROTATION = (float)std::fmod(CAMERA_HORIZONTAL_ROTATION + radians, 360);
		}
		else {
			CAMERA_VERITCAL_ROTATION += radians;
			CAMERA_VERITCAL_ROTATION = std::min(CAMERA_VERITCAL_ROTATION, CAMERA_VERTICAL_MAX);
			CAMERA_VERITCAL_ROTATION = std::max(CAMERA_VERITCAL_ROTATION, -CAMERA_VERTICAL_MAX);
		}

		UpdatePosition();
	}

	glm::mat4 GetView() {
		return view;
	}

	glm::mat4 GetProjection() {
		return projection;
	}

}