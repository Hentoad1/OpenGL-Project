#include "pch.h"

#include "Material.h"

#include "Texture.h"
#include "Path.h"

static void LogMetaData(const aiMaterial* mat, const aiTextureType type = (aiTextureType)(-1)) {
	aiString _NAME;
	aiColor3D _COLOR_DIFFUSE = aiColor3D(0);
	aiColor3D _COLOR_SPECULAR = aiColor3D(0);
	aiColor3D _COLOR_AMBIENT = aiColor3D(0);
	aiColor3D _COLOR_EMISSIVE = aiColor3D(0);
	aiColor3D _COLOR_TRANSPARENT = aiColor3D(0);
	aiColor3D _COLOR_REFLECTIVE = aiColor3D(0);
	int _WIREFRAME = false;
	int _TWOSIDED = false;
	int _SHADING_MODEL = aiShadingMode_Gouraud;
	int _BLEND_FUNC = aiBlendMode_Default;
	float _OPACITY = 1.0f;
	float _SHININESS = 0.0f;
	float _SHININESS_STRENGTH = 1.0f;
	float _REFRACTI = 1.0f;
	aiString _PATH;
	float _TEXBLEND;
	int _TEXOP;
	int _MAPPING;
	int _UVWSRC;
	int _MAPPINGMODE_U;
	int _MAPPINGMODE_V;
	aiVector3D _TEXMAP_AXIS;
	int _TEXFLAGS;
	int _BUMPSCALING;
	int _BACKGROUND_IMAGE;
	int _REFLECTIVITY;
	aiUVTransform _UVTRANSFORM;

	//properties with default values
	

	std::cout << 
		"---------------------------------------------------------------" << std::endl <<
		"                      METADATA PROPERTIES                      " << std::endl <<
		"---------------------------------------------------------------" << std::endl;

	std::cout << std::left;

	const int firstColumnWidth = 30;
	const int secondColumnWidth = 15;

	mat->Get(AI_MATKEY_NAME, _NAME);
	std::cout << 
		std::setw(firstColumnWidth) << "AI_MATKEY_NAME" <<
		std::setw(secondColumnWidth) << "STRING" <<
		_NAME.C_Str() << std::endl;

	mat->Get(AI_MATKEY_COLOR_DIFFUSE, _COLOR_DIFFUSE);
	std::cout <<
		std::setw(firstColumnWidth) << "AI_MATKEY_COLOR_DIFFUSE" <<
		std::setw(secondColumnWidth) << "AICOLOR3D" <<
		"(" << _COLOR_DIFFUSE.r << ", " << _COLOR_DIFFUSE.g << ", " << _COLOR_DIFFUSE.b << ")" << std::endl;

	mat->Get(AI_MATKEY_COLOR_SPECULAR, _COLOR_SPECULAR);
	std::cout <<
		std::setw(firstColumnWidth) << "AI_MATKEY_COLOR_SPECULAR" <<
		std::setw(secondColumnWidth) << "AICOLOR3D" <<
		"(" << _COLOR_SPECULAR.r << ", " << _COLOR_SPECULAR.g << ", " << _COLOR_SPECULAR.b << ")" << std::endl;

	mat->Get(AI_MATKEY_COLOR_AMBIENT, _COLOR_AMBIENT);
	std::cout <<
		std::setw(firstColumnWidth) << "AI_MATKEY_COLOR_AMBIENT" <<
		std::setw(secondColumnWidth) << "AICOLOR3D" <<
		"(" << _COLOR_AMBIENT.r << ", " << _COLOR_AMBIENT.g << ", " << _COLOR_AMBIENT.b << ")" << std::endl;

	mat->Get(AI_MATKEY_COLOR_EMISSIVE, _COLOR_EMISSIVE);
	std::cout <<
		std::setw(firstColumnWidth) << "AI_MATKEY_COLOR_EMISSIVE" <<
		std::setw(secondColumnWidth) << "AICOLOR3D" <<
		"(" << _COLOR_EMISSIVE.r << ", " << _COLOR_EMISSIVE.g << ", " << _COLOR_EMISSIVE.b << ")" << std::endl;

	mat->Get(AI_MATKEY_COLOR_TRANSPARENT, _COLOR_TRANSPARENT);
	std::cout <<
		std::setw(firstColumnWidth) << "AI_MATKEY_COLOR_TRANSPARENT" <<
		std::setw(secondColumnWidth) << "AICOLOR3D" <<
		"(" << _COLOR_TRANSPARENT.r << ", " << _COLOR_TRANSPARENT.g << ", " << _COLOR_TRANSPARENT.b << ")" << std::endl;

	mat->Get(AI_MATKEY_COLOR_REFLECTIVE, _COLOR_REFLECTIVE);
	std::cout <<
		std::setw(firstColumnWidth) << "AI_MATKEY_COLOR_REFLECTIVE" <<
		std::setw(secondColumnWidth) << "AICOLOR3D" <<
		"(" << _COLOR_REFLECTIVE.r << ", " << _COLOR_REFLECTIVE.g << ", " << _COLOR_REFLECTIVE.b << ")" << std::endl;

	mat->Get(AI_MATKEY_ENABLE_WIREFRAME, _WIREFRAME);
	std::cout <<
		std::setw(firstColumnWidth) << "AI_MATKEY_ENABLE_WIREFRAME" <<
		std::setw(secondColumnWidth) << "INT" <<
		_WIREFRAME << std::endl;

	mat->Get(AI_MATKEY_TWOSIDED, _TWOSIDED);
	std::cout <<
		std::setw(firstColumnWidth) << "AI_MATKEY_TWOSIDED" <<
		std::setw(secondColumnWidth) << "INT" <<
		_TWOSIDED << std::endl;

	mat->Get(AI_MATKEY_SHADING_MODEL, _SHADING_MODEL);
	std::cout <<
		std::setw(firstColumnWidth) << "AI_MATKEY_SHADING_MODEL" <<
		std::setw(secondColumnWidth) << "INT" <<
		_SHADING_MODEL << std::endl;

	mat->Get(AI_MATKEY_BLEND_FUNC, _BLEND_FUNC);
	std::cout <<
		std::setw(firstColumnWidth) << "AI_MATKEY_BLEND_FUNC" <<
		std::setw(secondColumnWidth) << "INT" <<
		_BLEND_FUNC << std::endl;

	mat->Get(AI_MATKEY_OPACITY, _OPACITY);
	std::cout <<
		std::setw(firstColumnWidth) << "AI_MATKEY_OPACITY" <<
		std::setw(secondColumnWidth) << "FLOAT" <<
		_OPACITY << std::endl;

	mat->Get(AI_MATKEY_SHININESS, _SHININESS);
	std::cout <<
		std::setw(firstColumnWidth) << "AI_MATKEY_SHININESS" <<
		std::setw(secondColumnWidth) << "FLOAT" <<
		_SHININESS << std::endl;

	mat->Get(AI_MATKEY_SHININESS_STRENGTH, _SHININESS_STRENGTH);
	std::cout <<
		std::setw(firstColumnWidth) << "AI_MATKEY_SHININESS_STRENGTH" <<
		std::setw(secondColumnWidth) << "FLOAT" <<
		_SHININESS_STRENGTH << std::endl;

	mat->Get(AI_MATKEY_REFRACTI, _REFRACTI);
	std::cout <<
		std::setw(firstColumnWidth) << "AI_MATKEY_REFRACTI" <<
		std::setw(secondColumnWidth) << "FLOAT" <<
		_REFRACTI << std::endl;

	//properties without default values

	if (AI_SUCCESS == mat->Get(AI_MATKEY_BUMPSCALING, _BUMPSCALING)) {
		std::cout <<
			std::setw(firstColumnWidth) << "AI_MATKEY_BUMPSCALING" <<
			std::setw(secondColumnWidth) << "INT" <<
			_BUMPSCALING << std::endl;
	}

	if (AI_SUCCESS == mat->Get(AI_MATKEY_GLOBAL_BACKGROUND_IMAGE, _BACKGROUND_IMAGE)) {
		std::cout <<
			std::setw(firstColumnWidth) << "AI_MATKEY_GLOBAL_BACKGROUND_IMAGE" <<
			std::setw(secondColumnWidth) << "INT" <<
			_BACKGROUND_IMAGE << std::endl;
	}

	if (AI_SUCCESS == mat->Get(AI_MATKEY_REFLECTIVITY, _REFLECTIVITY)) {
		std::cout <<
			std::setw(firstColumnWidth) << "AI_MATKEY_REFLECTIVITY" <<
			std::setw(secondColumnWidth) << "INT" <<
			_REFLECTIVITY << std::endl;
	}

	//texture type specific attributes
	if (type != -1) {
		if (AI_SUCCESS == mat->Get(AI_MATKEY_TEXTURE(type, 0), _PATH)) {
			std::cout <<
				std::setw(firstColumnWidth) << "AI_MATKEY_TEXTURE" <<
				std::setw(secondColumnWidth) << "AISTRING" <<
				_PATH.C_Str() << std::endl;
		}

		if (AI_SUCCESS == mat->Get(AI_MATKEY_TEXBLEND(type, 0), _TEXBLEND)) {
			std::cout <<
				std::setw(firstColumnWidth) << "AI_MATKEY_TEXBLEND" <<
				std::setw(secondColumnWidth) << "FLOAT" <<
				_TEXBLEND << std::endl;
		}

		if (AI_SUCCESS == mat->Get(AI_MATKEY_TEXOP(type, 0), _TEXOP)) {
			std::cout <<
				std::setw(firstColumnWidth) << "AI_MATKEY_TEXOP" <<
				std::setw(secondColumnWidth) << "INT" <<
				_TEXOP << std::endl;
		}


		if (AI_SUCCESS == mat->Get(AI_MATKEY_MAPPING(type, 0), _MAPPING)) {
			std::cout <<
				std::setw(firstColumnWidth) << "AI_MATKEY_MAPPING" <<
				std::setw(secondColumnWidth) << "INT" <<
				_MAPPING << std::endl;
		}

		if (AI_SUCCESS == mat->Get(AI_MATKEY_UVWSRC(type, 0), _UVWSRC)) {
			std::cout <<
				std::setw(firstColumnWidth) << "AI_MATKEY_UVWSRC" <<
				std::setw(secondColumnWidth) << "INT" <<
				_UVWSRC << std::endl;
		}

		if (AI_SUCCESS == mat->Get(AI_MATKEY_MAPPINGMODE_U(type, 0), _MAPPINGMODE_U)) {
			std::cout <<
				std::setw(firstColumnWidth) << "AI_MATKEY_MAPPINGMODE_U" <<
				std::setw(secondColumnWidth) << "INT" <<
				_MAPPINGMODE_U << std::endl;
		}

		if (AI_SUCCESS == mat->Get(AI_MATKEY_MAPPINGMODE_V(type, 0), _MAPPINGMODE_V)) {
			std::cout <<
				std::setw(firstColumnWidth) << "AI_MATKEY_MAPPINGMODE_V" <<
				std::setw(secondColumnWidth) << "INT" <<
				_MAPPINGMODE_V << std::endl;
		}

		if (AI_SUCCESS == mat->Get(AI_MATKEY_TEXMAP_AXIS(type, 0), _TEXMAP_AXIS)) {
			std::cout <<
				std::setw(firstColumnWidth) << "AI_MATKEY_TEXMAP_AXIS" <<
				std::setw(secondColumnWidth) << "AIVECTOR3D" <<
				"(" << _TEXMAP_AXIS.x << ", " << _TEXMAP_AXIS.y << ", " << _TEXMAP_AXIS.z << ")" << std::endl;
		}

		if (AI_SUCCESS == mat->Get(AI_MATKEY_TEXFLAGS(type, 0), _TEXFLAGS)) {
			std::cout <<
				std::setw(firstColumnWidth) << "AI_MATKEY_TEXFLAGS" <<
				std::setw(secondColumnWidth) << "INT" <<
				_TEXFLAGS << std::endl;
		}


		if (AI_SUCCESS == mat->Get(AI_MATKEY_UVTRANSFORM(type, 0), _UVTRANSFORM)) {
			std::cout <<
				std::setw(firstColumnWidth) << "AI_MATKEY_UVTRANSFORM" <<
				std::setw(secondColumnWidth) << "AIUVTRANSFORM" << std::endl <<

				std::setw(firstColumnWidth) << "    mRotation" <<
				std::setw(secondColumnWidth) << "FLOAT" <<
				_UVTRANSFORM.mRotation << std::endl <<

				std::setw(firstColumnWidth) << "    mScaling" <<
				std::setw(secondColumnWidth) << "AIVECTOR2D" <<
				"(" << _UVTRANSFORM.mScaling.x << ", " << _UVTRANSFORM.mScaling.y << ")" << std::endl <<

				std::setw(firstColumnWidth) << "    mTranslation" <<
				std::setw(secondColumnWidth) << "AIVECTOR2D" <<
				"(" << _UVTRANSFORM.mTranslation.x << ", " << _UVTRANSFORM.mTranslation.y << ")" << std::endl;
		}
	}

	std::cout << "---------------------------------------------------------------" << std::endl;
}


static constexpr aiTextureType texTypes[12] = {
	aiTextureType_DIFFUSE,
	aiTextureType_SPECULAR,
	aiTextureType_AMBIENT
	//aiTextureType_EMISSIVE,
	//aiTextureType_HEIGHT,
	//aiTextureType_NORMALS,
	//aiTextureType_SHININESS,
	//aiTextureType_OPACITY,
	//aiTextureType_DISPLACEMENT,
	//aiTextureType_LIGHTMAP,
	//aiTextureType_REFLECTION,
	//aiTextureType_NONE
};

static constexpr int aiTexureTypeToIndex(aiTextureType type) {
	switch (type) {
	case(aiTextureType_NONE):
		return -1;
	case(aiTextureType_DIFFUSE):
		return 0;
	case(aiTextureType_SPECULAR):
		return 1;
	case(aiTextureType_AMBIENT):
		return 2;
	case(aiTextureType_EMISSIVE):
		return -1;
	case(aiTextureType_HEIGHT):
		return -1;
	case(aiTextureType_NORMALS):
		return -1;
	case(aiTextureType_SHININESS):
		return -1;
	case(aiTextureType_OPACITY):
		return -1;
	case(aiTextureType_DISPLACEMENT):
		return -1;
	case(aiTextureType_LIGHTMAP):
		return -1;
	case(aiTextureType_REFLECTION):
		return -1;
	case(aiTextureType_UNKNOWN):
		return -1;
	default:
		return -1;
	}
}

GLint* Material::GetTextures() const {
	return (GLint*)textures;
}

GLint* Material::GetTexturesExist() const {
	return (GLint*)loaded;
}

float* Material::GetColors() const {
	return (float*)MaterialColors;
}

Material::Material(const aiScene* scene, const int index, const std::string& root) {

	aiMaterial* mat = scene->mMaterials[index];

	std::fill(loaded, loaded + numTexTypes, false);
	std::fill(textures, textures + numTexTypes, 0);

	aiColor3D clrs[numTexTypes];

	std::fill(clrs, clrs + numTexTypes, aiColor3D(0));

	mat->Get(AI_MATKEY_COLOR_DIFFUSE, clrs[0]);
	mat->Get(AI_MATKEY_COLOR_SPECULAR, clrs[1]);
	mat->Get(AI_MATKEY_COLOR_AMBIENT, clrs[2]);
	//mat->Get(AI_MATKEY_COLOR_EMISSIVE, clrs[3]);
	//mat->Get(AI_MATKEY_COLOR_TRANSPARENT, clrs[4]);
	//mat->Get(AI_MATKEY_COLOR_REFLECTIVE, clrs[5]);

	for (int i = 0; i < numTexTypes; i++) {
		int index = i * 4;
		
		MaterialColors[index] = clrs[i].r;
		MaterialColors[index + 1] = clrs[i].g;
		MaterialColors[index + 2] = clrs[i].b;
		MaterialColors[index + 3] = 1; // "a" value of 1
	}

	//memcpy(MaterialColors, clrs, sizeof(float) * numTexTypes * 3);

	for (int i = 0; i < numTexTypes; i++) {

		aiTextureType type = texTypes[i];
		int index = aiTexureTypeToIndex(type);

		if (index == -1) {
			std::cout << "Texture is unknown or not an enumerable value" << std::endl;
			throw;
		}


		unsigned int TexCount = mat->GetTextureCount(type);

		//this for loop is a glorified if statement, if 2 or more textures exist they are not layered. (this needs to be implemented)
		for (unsigned int j = 0; j < TexCount; j++) {
			aiString texturePath;

			mat->Get(AI_MATKEY_TEXTURE(type, 0), texturePath);

			const aiTexture* embedded = scene->GetEmbeddedTexture(texturePath.C_Str());

			if (embedded == nullptr) {

				std::string result = CalculatePath(root, texturePath.C_Str());

				GLuint glTexture = LoadTexture(result);

				if (TexCount > 1) {
					std::cout << "need to layer textures. not prepared for this." << std::endl;
					throw;
				}

				textures[index] = glTexture;
				loaded[index] = true;
			}
			else {
				//embedded texture

				GLuint glTexture = LoadTexture(embedded);

				if (TexCount > 1) {
					std::cout << "need to layer textures. not prepared for this." << std::endl;
					throw;
				}


				textures[index] = glTexture;
				loaded[index] = true;
			}
		}
	}
}