#pragma once

#include "pch.h"

static constexpr unsigned int numTexTypes = 3;

class Material {

public:
	
	Material(const aiScene*, const int, const std::string&);

	GLint* GetTextures() const;

	GLint* GetTexturesExist() const;

	float* GetColors() const;

private:
	GLint textures[numTexTypes];
	GLint loaded[numTexTypes];
	float MaterialColors[numTexTypes * 4];
};

