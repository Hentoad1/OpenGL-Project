#pragma once

#include "pch.h"
#include "SkeletalShader.h"

#include "EngineInternal.h"

SkeletalShader::SkeletalShader(Camera* mCam, glm::vec3 pos) : ShaderProgram("./SkeletalShaderV.glsl", "./SkeletalShaderF.glsl"), sCamera(mCam) {
    SetPosition(pos);
}

//Update assumes the shader is in use.
void SkeletalShader::Update() {

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

void SkeletalShader::SetPosition(glm::vec3 pos) {
    sModel = glm::mat4(1.0f);
    sModel = glm::translate(sModel, pos * glm::vec3(-1));
}

void SkeletalShader::SetPosition(glm::mat4 mod) {
    sModel = mod;
}