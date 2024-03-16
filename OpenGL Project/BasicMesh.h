#pragma once

#include "BasicShader.h"

#define POSITION_LOCATION 0
#define TEXTURE_LOCATION 1
#define NORMAL_LOCATION 2

enum TextureType : uint8_t{
	TextureType_DIFFUSE = 0,
	TextureType_SPECULAR = 0,
	TextureType_AMBIENT = 0,
};

class Mesh {
	
public:
	Mesh(const std::string, Camera*);

	~Mesh();

	void Render();

private:
	void Load(const std::string);

	struct MeshMeta {
		MeshMeta(unsigned int, unsigned int, unsigned int, glm::vec3, glm::vec3);

		unsigned int baseIndex;
		unsigned int indexCount;

		unsigned int materialIndex;

		glm::vec3 min;
		glm::vec3 max;

		glm::vec3 center;
	};

	struct MatBuffer {

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

		GLuint buffers[3]{};
		bool bufLoaded[3] = { false, false, false };
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
	std::vector<MeshMeta> mesh_data;
	
	//OpenGL Buffers
	GLuint VertexBuffer;
	MatBuffer* MaterialBuffer;
};