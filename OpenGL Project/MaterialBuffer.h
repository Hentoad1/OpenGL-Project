#pragma once

#include "pch.h"

#include "Material.h"

class MaterialBuffer {

public:

	MaterialBuffer(const MaterialBuffer& ref) {
		throw;
	}

	MaterialBuffer(const Material* mat);

	~MaterialBuffer();

	std::array<GLint, numTexTypes> GetTextures() const;

	std::array<GLint, numTexTypes> GetTexturesExist() const;

	std::array<Color, numTexTypes> GetColors() const;

private:
	std::array<GLint, numTexTypes> textures;
	std::array<GLint, numTexTypes> loaded;
	std::array<Color, numTexTypes> MaterialColors;
};

