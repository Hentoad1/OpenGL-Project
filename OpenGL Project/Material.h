#pragma once

#include "pch.h";

static constexpr unsigned int numTexTypes = 12;

class Material {

public:
	
	Material(const aiScene*, const int, const std::string&);

	GLuint Get(aiTextureType) const;

	bool Has(aiTextureType) const;

private:

	GLuint textures[numTexTypes];
	bool loaded[numTexTypes];
};