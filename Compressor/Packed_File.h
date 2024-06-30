#pragma once

#include "pch.h"

#include "Model.h"
#include "SkeletalModel.h"


struct Model_Location{
	//Model Name
	std::string name;

	//Offset from the base pointer to the model data.
	uint32_t offset;
};

struct Packed_File{

	std::vector<Model_Location> LookupTable;

	std::vector<Texture> Textures;

	std::vector<Material> Materials;

	std::vector<Model> Models;

	std::vector<Skeletal_Model> sModels;

};