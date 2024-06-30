#pragma once

#include "pch.h"

#include "Definitions.h"

#include "Skeleton.h"
#include "Animation.h"
#include "BoundingBox.h"

struct Model {

	std::vector<Vertex> Vertices;

	std::vector<uint32_t> Indices;

	std::vector<Mesh> Meshes;

	std::vector<Material> Materials;

	BoundingBox Bounds;
};