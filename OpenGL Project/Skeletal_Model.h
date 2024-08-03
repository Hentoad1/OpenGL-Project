#pragma once

#include "pch.h"

#include "Model.h"

#include "Vertex.h"
#include "Material.h"
#include "MaterialBuffer.h"
#include "Skeleton.h"
#include "Animation.h"
#include "BoundingBox.h"

class Skeletal_Model : Model {

public:
	Skeletal_Model(const std::vector<sVertex>& _vertices, const std::vector<unsigned int>& _indices, const std::vector<SubMesh>& _mesh_data, const std::vector<Material*>& _Materials, Skeleton* _skeleton, std::vector<Animation*> _animations, StaticBoundingBox* _sbb) :
		vertices(_vertices),
		indices(_indices),
		mesh_data(_mesh_data),
		Materials(_Materials),
		skeleton(_skeleton),
		animations(_animations),
		sbb(_sbb)
	{}

	~Skeletal_Model();

	static Skeletal_Model* ImportModel(Buffer& b);

	void AddToBuffer(Buffer&) const override;

	void Attach() override;

	void Detach() override;

	void Render(const ShaderProgram* shader) const override;

	Model_Type GetModelType() const override;

	const StaticBoundingBox* GetSBB() const override;

	const Skeleton* GetSkeleton() const override;

	const std::vector<Animation*>* GetAnimations() const override;

protected:

	static Skeletal_Model* ImportModel(const std::function<void(void*, size_t)>& Read);

private:

	/*      Model Data       */

	std::vector<sVertex> vertices;

	std::vector<unsigned int> indices;

	std::vector<SubMesh> mesh_data;

	std::vector<Material*> Materials;

	Skeleton* skeleton;
	std::vector<Animation*> animations;

	StaticBoundingBox* sbb;


	/*      Buffer Data      */

	bool isAttached = false;

	GLuint VAO = -1;

	std::vector<MaterialBuffer*> MBO;
};