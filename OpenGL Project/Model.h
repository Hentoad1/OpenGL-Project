#pragma once

#include "pch.h"

#include "Shader.h"

#include "Buffer.h"

#include "BoundingBox.h"
#include "Skeleton.h"
#include "Animation.h"

#define POSITION_LOCATION 0
#define TEXTURE_LOCATION 1
#define NORMAL_LOCATION 2
#define BONE_INDEX_LOCATION 3
#define BONE_WEIGHT_LOCATION 4

#define UNIQUE_TEXTURE_TYPES 3

enum Model_Type : uint8_t {
	Model_Type_Basic = 0,
	Model_Type_Skeletal = 1
};

class Model {

public:

	static Model* CreateEmptyModel(StaticBoundingBox*);

	static Model* ImportModel(Buffer& b);

	static Model* ImportModel(const std::string&);

	virtual void AddToBuffer(Buffer&) const = 0;

	virtual void Attach() = 0;

	virtual void Detach() = 0;

	virtual void Render(const ShaderProgram* shader) const = 0;

	virtual Model_Type GetModelType() const = 0;

	virtual const StaticBoundingBox* GetSBB() const = 0;

	virtual const Skeleton* GetSkeleton() const { return nullptr; }

	virtual const std::vector<Animation*>* GetAnimations() const { return nullptr; }

protected:
	struct SubMesh;
};

struct Model::SubMesh {
	unsigned int indexCount;

	unsigned int BaseVertex;
	unsigned int BaseIndex;

	unsigned int materialIndex;

	glm::vec3 min;
	glm::vec3 max;
};
