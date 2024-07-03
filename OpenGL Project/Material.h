#pragma once

#include "pch.h"

static constexpr unsigned int numTexTypes = 3;

struct Texture {

	Texture(Texture& ref) {
		throw;
	}

	Texture(const std::string&);
	Texture(const aiTexture*);
	Texture(int, int, int, void*);

	~Texture();

	int width = 0;
	int height = 0;
	int bits_per_pixel = -1;
	void* data = nullptr;


	bool useSTBIdel = false;
};

struct Color {
	Color() : r(0), g(0), b(0), a(0){}
	Color(float, float, float, float);
	Color(const aiColor3D&);

	float r;
	float g;
	float b;
	float a;
};

class Material {

public:

	Material(const Material& ref) {
		throw;
	}

	~Material();

	Material(const aiScene*, const int, const std::string&);

	Material(const std::array<Texture*, numTexTypes>&, const std::array<Color, numTexTypes>&);

	const std::array<Texture*, numTexTypes>& GetTextures() const;

	const std::array<Color, numTexTypes>& GetColors() const;

private:
	std::array<Texture*, numTexTypes> Textures;
	std::array<Color, numTexTypes> Colors;
};