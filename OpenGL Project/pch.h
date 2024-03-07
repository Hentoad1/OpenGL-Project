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