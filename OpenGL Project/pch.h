#pragma once

#include "pch.h"

#include <string>
#include <iostream>
#include <windows.h>
#include <thread>
#include <list>
#include <vector>
#include <array>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <math.h>
#include <numbers>
#include <any>
#include <variant>
#include <unordered_map>
#include <unordered_set>
#include <filesystem>
#include <functional>
#include <array>
#include <bitset>

#include <assimp/config.h>

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags


#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <glm/gtx/string_cast.hpp> // glm::to_string
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp> 

constexpr glm::mat4 aiMatrix4x4ToGlm(const aiMatrix4x4& from)
{
	glm::mat4 to;

	to[0][0] = (GLfloat)from.a1; to[0][1] = (GLfloat)from.b1;  to[0][2] = (GLfloat)from.c1; to[0][3] = (GLfloat)from.d1;
	to[1][0] = (GLfloat)from.a2; to[1][1] = (GLfloat)from.b2;  to[1][2] = (GLfloat)from.c2; to[1][3] = (GLfloat)from.d2;
	to[2][0] = (GLfloat)from.a3; to[2][1] = (GLfloat)from.b3;  to[2][2] = (GLfloat)from.c3; to[2][3] = (GLfloat)from.d3;
	to[3][0] = (GLfloat)from.a4; to[3][1] = (GLfloat)from.b4;  to[3][2] = (GLfloat)from.c4; to[3][3] = (GLfloat)from.d4;

	return to;
}

constexpr glm::vec3 aiVector3DToGlm(const aiVector3D& from)
{
	return glm::vec3(from.x, from.y, from.z);
}

constexpr glm::quat aiQuatToGlm(const aiQuaternion& pOrientation)
{
	return glm::quat(pOrientation.w, pOrientation.x, pOrientation.y, pOrientation.z);
}

#ifdef _DEBUG
#include "Debug.h"
#endif
