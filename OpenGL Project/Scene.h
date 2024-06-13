#pragma once

#include "pch.h"

struct SceneLight {
    glm::vec3 direction;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

#define NUM_LIGHT_SOURCES 10

struct LightSource {
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
    const SceneLight* GetSceneLight();
    const LightSource* GetLightSources();

    void AddLight(const LightSource&);
}