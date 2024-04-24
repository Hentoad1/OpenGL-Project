#pragma once

#include "pch.h"
#include "DebugShader.h"

#include "Screen.h"

DebugShader::DebugShader(Camera* sCam, glm::vec3 pos) : ShaderProgram("./DebugShaderV.glsl", "./DebugShaderF.glsl"), sCamera(sCam), sColor(glm::vec4(0, 191, 255, 0.5)) {
    SetPosition(pos);
}

DebugShader::DebugShader(Camera* sCam, glm::vec3 pos, glm::vec4 color) : ShaderProgram("./DebugShaderV.glsl", "./DebugShaderF.glsl"), sCamera(sCam), sColor(color) {
    SetPosition(pos);
}

//Update assumes the shader is in use.
void DebugShader::Update() {
    setVec4("color", sColor);

    setMat4("projection", sCamera->GetProjection());

    setMat4("view", sCamera->GetView());

    setMat4("model", sModel);
}

void DebugShader::SetPosition(glm::vec3 pos) {
    sModel = glm::mat4(1.0f);
    sModel = glm::translate(sModel, pos);
}

void DebugShader::SetPosition(glm::mat4 mod) {
    sModel = mod;
}

