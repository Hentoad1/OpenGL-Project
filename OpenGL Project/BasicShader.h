#pragma once

#include "pch.h"

#include "Shader.h"
#include "Camera.h"

class BasicShader : ShaderProgram {
public:
    BasicShader(Camera* mCam, glm::vec3 center);

    void Update();
private:
    glm::mat4 mModel;

    Camera* mCamera;
};