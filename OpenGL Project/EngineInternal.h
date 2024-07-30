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

enum CollisionType : uint8_t {
	//Axis normal where abs(y) < 0.05
	COLLISIONTYPE_WALL = 0,

	//Axis normal where y < -0.95
	COLLISIONTYPE_CEILING = 1,

	//Axis normal where y > 0.95
	COLLISIONTYPE_FLOOR = 2,

	//Axis normal where that meets none of the above
	COLLISIONTYPE_SLANTED_FLOOR = 3, //might end up being bouncy or something else
};

struct CollisionInfo {

	//If the collision happened.
	bool collided;

	//The position that the object should be moved to
	glm::vec3 newPosition;

	//The type of surface hit
	CollisionType collisionType;
};