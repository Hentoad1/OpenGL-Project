#pragma once

#include "pch.h"

#define ENGINE_SETTING_DISPLAY_MODEL

//#define ENGINE_SETTING_MAIN

//defaults to display model.
#ifdef ENGINE_SETTING_DISPLAY_MODEL
#undef ENGINE_SETTING_MAIN
#endif

struct FrameData {
	int8_t WALK_FORWARD = GLFW_KEY_UNKNOWN;
	int8_t WALK_BACKWARD = GLFW_KEY_UNKNOWN;
	int8_t WALK_LEFT = GLFW_KEY_UNKNOWN;
	int8_t WALK_RIGHT = GLFW_KEY_UNKNOWN;
	int8_t JUMP = GLFW_KEY_UNKNOWN;
	int8_t CROUCH = GLFW_KEY_UNKNOWN;
	int8_t INTERACT = GLFW_KEY_UNKNOWN;
	glm::dvec2 CURSOR_POSITION = glm::dvec2(0);
	glm::dvec2 DELTA_CURSOR_POSITION = glm::dvec2(0);
	glm::dvec2 ADJUSTED_DELTA_CURSOR_POSITION = glm::dvec2(0);
	double DeltaTime;
};


constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;

constexpr float SCREEN_WIDTH_F = 800.0f;
constexpr float SCREEN_HEIGHT_F = 600.0f;

struct CollisionInfo {

	//If the collision happened.
	bool collided;

	//The coefficient to applied to the axis to move an object back to where it collided.
	float overlapAmount;

	//The velocity resulting from the collision.
	glm::vec3 collisionVelocity;
};