#pragma once

#include "pch.h"
#include "Scene.h"

struct ShaderTexture {
    GLuint image;
    bool useImage;
    glm::vec4 color;
};

static std::string ReadFile(const std::string& path) {

    std::ifstream file;

    try {
        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        file.open(path);

        if (!file.is_open()) {
            throw;
        }
    }
    catch (std::exception e) { //file does not exist
        std::string errmsg = "Unable to open file at path: " + path;

        std::cout << errmsg << std::endl;

        throw new std::exception(errmsg.c_str());
    }


    std::string contents;
    try {
        contents = std::string{ std::istreambuf_iterator<char>{file}, {} };
    }
    catch (const std::ifstream::failure& e) {

        std::cout << path << std::endl;
        std::cout << e.what() << std::endl;

        throw e;
    }

    return contents;
}

class ShaderProgram {
public:
    GLuint ID;

    ShaderProgram(const char* vertexPath, const char* fragmentPath) {

        //Load code from file
        std::string v = ReadFile(vertexPath);
        const char* vShaderCode = v.c_str();

        std::string f = ReadFile(fragmentPath);
        const char* fShaderCode = f.c_str();



        //Compile Vertex Shader
        GLuint vertex;
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);

        if (!ShaderCompiled(vertex)) {
            std::cout << "Failed to compile vertex shader" << std::endl;
            std::cout << vShaderCode << std::endl;

            throw new std::exception("Failed to compile vertex shader");
        }

        //Compile Fragment Shader
        GLuint fragment;
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);

        if (!ShaderCompiled(fragment)) {
            std::cout << "Failed to compile fragment shader" << std::endl;
            std::cout << fShaderCode << std::endl;

            throw new std::exception("Failed to compile fragment shader");
        }

        //Create & Link Shader Program
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);

        if (!ProgramLinked(ID)) {
            std::cout << "Failed to link program" << std::endl;

            throw new std::exception("Failed to link program");
        }

        //Delete Shaders
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    ~ShaderProgram() {
        glDeleteProgram(ID);
    }

    void Use() {
        glUseProgram(ID);
    }

    virtual void Update() = 0;

    virtual void SetPosition(glm::vec3) = 0;

    virtual void SetPosition(glm::mat4) = 0;

    void setBool(const std::string& name, bool value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }

    void setBools(const std::string& name, int* value, int count) const {
        glUniform1iv(glGetUniformLocation(ID, name.c_str()), count, &value[0]);
    }

    void setInt(const std::string& name, int value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }

    void setFloat(const std::string& name, float value) const {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }

    void setVec2(const std::string& name, const glm::vec2& value) const {
        glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value));
    }

    void setVec3(const std::string& name, const glm::vec3& value) const {
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value));
    }

    void setVec3s(const std::string& name, const GLfloat* value, int count) const {
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), count * 3, value);
    }

    void setVec4(const std::string& name, const glm::vec4& value) const {
        glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value));
    }

    void setVec4s(const std::string& name, const GLfloat* value, int count) const {
        glUniform4fv(glGetUniformLocation(ID, name.c_str()), count * 4, value);
    }

    void setMat2(const std::string& name, const glm::mat2& mat) const {
        glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
    }

    void setMat3(const std::string& name, const glm::mat3& mat) const {
        glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
    }

    void setMat4(const std::string& name, const glm::mat4& mat) const {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
    }
    void setMat4s(const std::string& name, int count, const glm::mat4* mat) {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), count, GL_FALSE, (float*)mat);
    }


    void setMat4(const std::string& name, const aiMatrix4x4& mat) const {
        throw;
        //might have wrong column row order for aiMatrix
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void setTexture(const std::string& name, const GLint tex) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), tex);
    }

    void setTextures(const std::string& name, const GLint* tex, int count) const {
        glUniform1iv(glGetUniformLocation(ID, name.c_str()), count, tex);
    }

    void SetLight(const std::string& name, const glslSceneLight* light) const {
        glUniform3fv(glGetUniformLocation(ID, (name + ".direction").c_str()), 1, glm::value_ptr(light->direction));
        glUniform3fv(glGetUniformLocation(ID, (name + ".ambient").c_str()), 1, glm::value_ptr(light->ambient));
        glUniform3fv(glGetUniformLocation(ID, (name + ".diffuse").c_str()), 1, glm::value_ptr(light->diffuse));
        glUniform3fv(glGetUniformLocation(ID, (name + ".specular").c_str()), 1, glm::value_ptr(light->specular));
    }

    void SetLight(const std::string& name, const glslLightSource* light) const {
        glUniform1f(glGetUniformLocation(ID, (name + ".loaded").c_str()), light->loaded);


        glUniform3fv(glGetUniformLocation(ID, (name + ".position").c_str()), 1, glm::value_ptr(light->position));

        glUniform1f(glGetUniformLocation(ID, (name + ".strength").c_str()), light->strength);

        glUniform1f(glGetUniformLocation(ID, (name + ".linear").c_str()), light->linear);
        glUniform1f(glGetUniformLocation(ID, (name + ".quadratic").c_str()), light->quadratic);


        glUniform3fv(glGetUniformLocation(ID, (name + ".ambient").c_str()), 1, glm::value_ptr(light->ambient));
        glUniform3fv(glGetUniformLocation(ID, (name + ".diffuse").c_str()), 1, glm::value_ptr(light->diffuse));
        glUniform3fv(glGetUniformLocation(ID, (name + ".specular").c_str()), 1, glm::value_ptr(light->specular));
    }

private:
    bool ShaderCompiled(GLuint obj) {
        GLint status;
        glGetShaderiv(obj, GL_COMPILE_STATUS, &status);
        return status == GL_TRUE;
    }

    bool ProgramLinked(GLuint obj) {
        GLint status;
        glGetProgramiv(obj, GL_LINK_STATUS, &status);
        return status == GL_TRUE;
    }
};