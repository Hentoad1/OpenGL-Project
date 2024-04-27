#pragma once

#include "pch.h"

#include "Shader.h"
#include "Camera.h"
#include "EngineInternal.h"

class BasicShader : ShaderProgram {
public:
    BasicShader(Camera* mCam, glm::vec3 center);

    void SetPosition(glm::vec3);

    void SetPosition(glm::mat4);

    void Update();
private:
    glm::mat4 sModel;

    Camera* sCamera;
};