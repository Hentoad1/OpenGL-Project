#pragma once

#include "Screen.h"
#include "Shader.h"

#include "Camera.h"

class BasicShader : ShaderProgram {
public:
    BasicShader(Camera* mCam, aiMatrix4x4 translation) : ShaderProgram("./BasicShaderV.glsl", "./BasicShaderF.glsl") {
        mCamera = mCam;
        
        mModel = aiMatrix4x4ToGlm(translation);
    }

    //Update assumes the shader is in use.
    void Update() {


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

        setMat4("model", mModel);//this could be not be model and just some random ass translation 4x4


    }

private:
    glm::mat4 mModel;

    Camera* mCamera;
};