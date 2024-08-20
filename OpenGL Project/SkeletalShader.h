#pragma once

#include "pch.h"

#include "Shader.h"
#include "Camera.h"
#include "EngineInternal.h"

class SkeletalShader : ShaderProgram {
public:
    SkeletalShader(Camera* mCam);

    void SetPosition(glm::vec3) override;

    void SetPosition(glm::mat4) override;

    void Update() override;
private:
    glm::mat4 sModel;

    Camera* sCamera;
};