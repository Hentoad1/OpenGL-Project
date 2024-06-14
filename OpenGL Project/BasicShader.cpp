#pragma once

#include "pch.h"
#include "BasicShader.h"

#include "EngineInternal.h"

BasicShader::BasicShader(Camera* mCam, glm::vec3 pos) : ShaderProgram("./BasicShaderV.glsl", "./BasicShaderF.glsl"), sCamera(mCam) {
    SetPosition(pos);
}

//Update assumes the shader is in use.
void BasicShader::Update() {

    SetLight("sceneLight", Scene::GetSceneLight());

    const glslLightSource* sources = Scene::GetLightSources();

    for (int i = 0; i < NUM_LIGHT_SOURCES; ++i) {
        std::string loc = std::string("LightSources[") + std::to_string(i) + std::string("]");

        SetLight(loc, &sources[i]);
    }

/*#ifdef ENGINE_SETTING_DISPLAY_MODEL
    setVec3("lightPos", sCamera->LightPos);
#else
    setVec3("lightPos", glm::vec3(0, 0, 100));
#endif*/


    setMat4("projection", sCamera->GetProjection());

    setMat4("view", sCamera->GetView());

    setMat4("model", sModel);
}

void BasicShader::SetPosition(glm::vec3 pos){
    sModel = glm::mat4(1.0f);
    sModel = glm::translate(sModel, pos * glm::vec3(-1));
}

void BasicShader::SetPosition(glm::mat4 mod) {
    sModel = mod;
}