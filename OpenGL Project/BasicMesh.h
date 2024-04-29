#pragma once

#include "BasicShader.h"

#include "Vertex.h"
#include "Material.h"

#include "BoundingBox.h"

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
	Mesh(const std::string&, Camera*);

	Mesh(const BoundingBox&, Camera*);

	virtual ~Mesh();

	//function does nothing, but it not pure virtual.
	virtual void Update(const FrameData&) {};

	void Render();

	bool CollidesWith(const BoundingBox& other);
	CollisionInfo CollidesWith(const BoundingBox&, const glm::vec3&);

	void SetPosition(const glm::vec3&);
	void SetOrientation(const Orientation&);

protected:
	virtual BoundingBox& GetBoundingBox();

	virtual Camera* GetCamera();
private:
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
	BoundingBox bounds;

	//Camera
	Camera* mCamera;

	//Shader
	ShaderProgram* shader;

	//Submesh Metadata
	std::vector<SubMesh> mesh_data;
	
	//OpenGL Buffers
	GLuint VertexBuffer;
	std::vector<Material> Materials;
};