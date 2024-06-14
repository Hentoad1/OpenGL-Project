#pragma once

#include "pch.h"

struct glslSceneLight {
    glm::vec3 direction;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

#define NUM_LIGHT_SOURCES 10

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