#include "pch.h"

#include "Model.h"
#include "Basic_Model.h"

Model* Model::CreateEmptyModel(StaticBoundingBox* sbb) {
	return (Model*)(new Basic_Model(std::vector<Vertex>(), std::vector<unsigned int>(), std::vector<SubMesh>(), std::vector<Material*>(), sbb));
}