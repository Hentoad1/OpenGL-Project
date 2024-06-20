#pragma once

#include "pch.h"


#define NUM_LIGHT_SOURCES 10

#define MAX_BONE_INFLUENCE 4
#define MAX_BONES 100

struct glslSceneLight {
    glm::vec3 direction;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

struct glslLightSource {
    bool loaded = false;

    glm::vec3 position;

    float strength;

    float linear;
    float quadratic;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

namespace Scene {
    const glslSceneLight* GetSceneLight();
    const glslLightSource* GetLightSources();

    void AddLight(const glslLightSource&);
}