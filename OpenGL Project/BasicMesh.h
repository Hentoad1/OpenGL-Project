#pragma once

#include "BasicShader.h"

#include "Vertex.h"

#define AI_CONFIG_PP_SBP_REMOVE aiPrimitiveType_LINE | aiPrimitiveType_POINT

constexpr int POSITION_LOCATION = 0;
constexpr int TEXTURE_LOCATION = 1;
constexpr int NORMAL_LOCATION = 2;

static constexpr int UNIQUE_TEXTURE_TYPES = 3;

enum TextureType : uint8_t {
	TextureType_DIFFUSE = 0,
	TextureType_SPECULAR = 1,
	TextureType_AMBIENT = 2,
};

class Mesh {
	
public:
	Mesh(const std::string, Camera*);

	~Mesh();

	void Render();

protected:
	class SubMesh {
	public:
		SubMesh(unsigned int, unsigned int, unsigned int, unsigned int, glm::vec3, glm::vec3);

		unsigned int indexCount;

		unsigned int BaseVertex;
		unsigned int BaseIndex;

		unsigned int materialIndex;

		glm::vec3 min;
		glm::vec3 max;

		glm::vec3 center;
	};
private:
	void Load(const std::string);

	class MatBuffer {

	public:
		GLuint Get(TextureType type) const {
			return buffers[type];
		}

		bool Has(TextureType type) const {
			return bufLoaded[type];
		}

		void Set(TextureType type, GLuint ID) {
			if (bufLoaded[type]) {
				glDeleteTextures(1, &buffers[type]);
			}

			buffers[type] = ID;
		}

	private:
		GLuint buffers[UNIQUE_TEXTURE_TYPES]{};
		bool bufLoaded[UNIQUE_TEXTURE_TYPES] = { false, false, false };
	};

	//Bounding Box
	glm::vec3 min;
	glm::vec3 max;
	glm::vec3 center;

	//Camera
	Camera* mCamera;

	//Shader
	ShaderProgram* shader;

	//Submesh Metadata
	std::vector<SubMesh> mesh_data;
	
	//OpenGL Buffers
	GLuint VertexBuffer;
	MatBuffer* MaterialBuffer;

	//indices
	std::vector<unsigned int> indices;

	std::vector<Vertex> vertices;
};