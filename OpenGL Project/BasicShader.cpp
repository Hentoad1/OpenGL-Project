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
    /*glm::vec3 position = glm::vec3(5, 1, 0);
    glm::mat4 view = glm::lookAt(position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 projection = glm::perspective(glm::radians(70.0f), SCREEN_WIDTH_F / SCREEN_HEIGHT_F, 1.0f, 1000.0f);

    std::cout << "--------------------------------------" << std::endl;
    std::cout << glm::to_string(position) << std::endl;
    std::cout << glm::to_string(view) << std::endl;
    std::cout << glm::to_string(modelMatrix) << std::endl;
    std::cout << "--------------------------------------" << std::endl;*/

    setMat4("projection", mCamera->GetProjection());

    setMat4("view", mCamera->GetView());

    setMat4("model", mModel);
}