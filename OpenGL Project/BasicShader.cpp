#pragma once

#include "pch.h"
#include "BasicShader.h"

#include "Screen.h"

BasicShader::BasicShader(Camera* mCam, glm::vec3 center) : ShaderProgram("./BasicShaderV.glsl", "./BasicShaderF.glsl") {
    mCamera = mCam;

    glm::vec3 offset = center * glm::vec3(-1);

    mModel = glm::mat4(1.0f);
    mModel = glm::translate(mModel, offset);

    setBool("useTexture", true);
}

//Update assumes the shader is in use.
void BasicShader::Update() {
    setVec3("lightPos", glm::vec3(0, 0, 100));

    setMat4("projection", mCamera->GetProjection());

    setMat4("view", mCamera->GetView());

    setMat4("model", mModel);
}