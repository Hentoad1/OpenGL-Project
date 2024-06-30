#pragma once

#include "pch.h"

#include "Skeleton.h"
#include "Animation.h"
#include "BoundingBox.h"

struct Skeletal_Model {

	std::vector<bVertex> Vertices;

	std::vector<uint32_t> Indices;

	std::vector<Mesh> Meshes;

	std::vector<Material> Materials;

	Skeleton Skeleton;

	std::vector<Animation> Animations;

	BoundingBox Bounds;
};