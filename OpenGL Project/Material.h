#pragma once

#include "pch.h";



class Material {

public:
	
	Material(const aiMaterial*);

	GLuint Get(aiTextureType) const;

	bool Has(aiTextureType) const ;

private:

	GLuint textures[12];
	bool loaded[12];
};