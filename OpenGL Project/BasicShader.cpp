#pragma once

#include "pch.h";
#include "BasicShader.h"

#include "Screen.h"

BasicShader::BasicShader(Camera* mCam, glm::vec3 center) : ShaderProgram("./BasicShaderV.glsl", "./BasicShaderF.glsl") {
    mCamera = mCam;

    glm::vec3 offset = center * glm::vec3(-1);

    std::cout << glm::to_string(center) << std::endl;

    mModel = glm::mat4(1.0f);
    mModel = glm::translate(mModel, offset);

    std::cout << glm::to_string(mModel) << std::endl;
}

//Update assumes the shader is in use.
void BasicShader::Update() {

    setMat4("projection", mCamera->GetProjection());

    setMat4("view", mCamera->GetView());

    setMat4("model", mModel);
}