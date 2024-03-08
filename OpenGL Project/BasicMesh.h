#pragma once

#include "pch.h"

class Mesh {
	
public:
	Mesh(std::string path);

	~Mesh();

private:
	aiScene* Load(std::string path);

};