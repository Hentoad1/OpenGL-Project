#include "pch.h"

#include "Material.h"
#include "MaterialKeys.h"

static constexpr aiTextureType texTypes[12] = {
	aiTextureType_NONE,
	aiTextureType_DIFFUSE,
	aiTextureType_SPECULAR,
	aiTextureType_AMBIENT,
	aiTextureType_EMISSIVE,
	aiTextureType_HEIGHT,
	aiTextureType_NORMALS,
	aiTextureType_SHININESS,
	aiTextureType_OPACITY,
	aiTextureType_DISPLACEMENT,
	aiTextureType_LIGHTMAP,
	aiTextureType_REFLECTION
};

static constexpr int aiTexureTypeToIndex(aiTextureType type) {
	switch (type) {
	case(aiTextureType_NONE):
		return 0;
	case(aiTextureType_DIFFUSE):
		return 1;
	case(aiTextureType_SPECULAR):
		return 2;
	case(aiTextureType_AMBIENT):
		return 3;
	case(aiTextureType_EMISSIVE):
		return 4;
	case(aiTextureType_HEIGHT):
		return 5;
	case(aiTextureType_NORMALS):
		return 6;
	case(aiTextureType_SHININESS):
		return 7;
	case(aiTextureType_OPACITY):
		return 8;
	case(aiTextureType_DISPLACEMENT):
		return 9;
	case(aiTextureType_LIGHTMAP):
		return 10;
	case(aiTextureType_REFLECTION):
		return 11;
	case(aiTextureType_UNKNOWN):
		return -1;
	default:
		return -1;
	}
}

GLuint Material::Get(aiTextureType type) const {
	return textures[aiTexureTypeToIndex(type)];
}

bool Material::Has(aiTextureType type) const {
	return loaded[aiTexureTypeToIndex(type)];
}

Material::Material(const aiMaterial* mat) {
	
	MaterialMeta meta = MaterialMeta(mat, aiTextureType_DIFFUSE);

	meta.LogProperties();
	

}