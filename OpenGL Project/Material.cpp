#include "pch.h"

#include "Material.h"
#include "MaterialKeys.h"

#include "Texture.h"
#include "Path.h"

static constexpr aiTextureType texTypes[numTexTypes] = {
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

Material::Material(const aiScene* scene, const int index, const std::string& root) {
	for (int i = 0; i < numTexTypes; i++) {
		loaded[i] = false;
	}

	for (int i = 0; i < numTexTypes; i++) {

		aiMaterial* mat = scene->mMaterials[index];

		aiTextureType type = texTypes[i];
		int index = aiTexureTypeToIndex(type);

		if (index == -1) {
			std::cout << "Texture is unknown or not an enumerable value" << std::endl;
			throw;
		}


		unsigned int TexCount = mat->GetTextureCount(type);

		//this for loop is a glorified if statement, if 2 or more textures exist they are not layered.
		for (unsigned int j = 0; j < TexCount; j++) {
			aiString texturePath;

			mat->Get(AI_MATKEY_TEXTURE(type, 0), texturePath);

			const aiTexture* embedded = scene->GetEmbeddedTexture(texturePath.C_Str());

			if (embedded == nullptr) {

				std::string result = CalculatePath(root, texturePath.C_Str());

				GLuint glTexture = LoadTexture(result);

				if (Has(type)) {
					std::cout << "need to layer textures. not prepared for this." << std::endl;
					//throw;
				}

				textures[index] = glTexture;
				loaded[index] = true;
			}
			else {
				//embedded texture

				GLuint glTexture = LoadTexture(embedded);

				if (Has(type)) {
					std::cout << "need to layer textures. not prepared for this." << std::endl;
					//throw;
				}


				textures[index] = glTexture;
				loaded[index] = true;
			}
		}
	}
}