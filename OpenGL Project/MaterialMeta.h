#pragma once

#include "pch.h"

enum MatMetaEntry : uint8_t {
	MATMETA_NAME = 0,
	MATMETA_COLOR_DIFFUSE = 1,
	MATMETA_COLOR_SPECULAR = 2,
	MATMETA_COLOR_AMBIENT = 3,
	MATMETA_COLOR_EMISSIVE = 4,
	MATMETA_COLOR_TRANSPARENT = 5,
	MATMETA_COLOR_REFLECTIVE = 6,
	MATMETA_WIREFRAME = 7,
	MATMETA_TWOSIDED = 8,
	MATMETA_SHADING_MODEL = 9,
	MATMETA_BLEND_FUNC = 10,
	MATMETA_OPACITY = 11,
	MATMETA_SHININESS = 12,
	MATMETA_SHININESS_STRENGTH = 13,
	MATMETA_REFRACTI = 14,
	MATMETA_PATH = 15,
	MATMETA_TEXBLEND = 16,
	MATMETA_TEXOP = 17,
	MATMETA_MAPPING = 18,
	MATMETA_UVWSRC = 19,
	MATMETA_MAPPINGMODE_U = 20,
	MATMETA_MAPPINGMODE_V = 21,
	MATMETA_TEXMAP_AXIS = 22,
	MATMETA_TEXFLAGS = 23,
	MATMETA_BUMPSCALING = 24,
	MATMETA_BACKGROUND_IMAGE = 25,
	MATMETA_REFLECTIVITY = 26,
	MATMETA_UVTRANSFORM = 27
};

enum MatMetaType : uint8_t {
	MatMetaType_aiString = 0,
	MatMetaType_aiColor3D = 1,
	MatMetaType_int = 2,
	MatMetaType_float = 3,
	MatMetaType_aiVector3D = 4,
	MatMetaType_aiUVTransform = 5
};

class MatMetaProperty {
public:
	MatMetaProperty(const MatMetaProperty&);

	MatMetaProperty() {};

	MatMetaProperty(void*, MatMetaType);

	~MatMetaProperty();

	operator aiString();
	operator aiColor3D();
	operator int();
	operator float();
	operator aiVector3D();
	operator aiUVTransform();

	operator std::string();

private:
	void* entry = nullptr;
	MatMetaType type = (MatMetaType)-1;
	unsigned int size = 0;
};



class MatMeta {

public:
	MatMeta(const aiMaterial*, const aiTextureType = (aiTextureType)-1);

	MatMeta Get(const MatMetaEntry key);

	void LogProperties();

private:
	std::unordered_map<MatMetaEntry, MatMetaProperty> properties;
};