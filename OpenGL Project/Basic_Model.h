#pragma once

#include "pch.h"

#include "Model.h"

#include "Vertex.h"
#include "Material.h"
#include "MaterialBuffer.h"
#include "BoundingBox.h"

class Basic_Model : Model {

public:

	Basic_Model(const std::vector<Vertex>& _vertices, const std::vector<unsigned int>& _indices, const std::vector<SubMesh>& _mesh_data, const std::vector<Material*>& _Materials, StaticBoundingBox* _sbb) :
		vertices(_vertices),
		indices(_indices),
		mesh_data(_mesh_data),
		Materials(_Materials),
		sbb(_sbb)
	{}

	~Basic_Model();

	void AddToBuffer(Buffer&) const override;

	void Attach() override;

	void Detach() override;

	void Render(const ShaderProgram* shader) const override;

	Model_Type GetModelType() const override;

	const StaticBoundingBox* GetSBB() const override;

protected:

private:

	/*      Model Data       */

	std::vector<Vertex> vertices;

	std::vector<unsigned int> indices;

	std::vector<SubMesh> mesh_data;

	std::vector<Material*> Materials;

	StaticBoundingBox* sbb;


	/*      Buffer Data      */

	bool isAttached = false;

	GLuint VAO = -1;

	std::vector<MaterialBuffer*> MBO;

};