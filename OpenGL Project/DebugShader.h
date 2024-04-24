#pragma once

#include "pch.h"

#include "Shader.h"
#include "Camera.h"
#include "Config.h"

class DebugShader : ShaderProgram {
public:
    DebugShader(Camera* mCam, glm::vec3 center);

    DebugShader(Camera* mCam, glm::vec3 center, glm::vec4 color);

    void SetPosition(glm::vec3);

    void SetPosition(glm::mat4);

    void Update();
private:
    glm::mat4 sModel;

    Camera* sCamera;

    glm::vec4 sColor;
};