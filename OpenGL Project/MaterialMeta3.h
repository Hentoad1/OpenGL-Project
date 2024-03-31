#pragma once

#include "pch.h"

enum MatMetaProperty : uint8_t{
	NAME = 0,
	COLOR_DIFFUSE = 1,
	COLOR_SPECULAR = 2,
	COLOR_AMBIENT = 3,
	COLOR_EMISSIVE = 4,
	COLOR_TRANSPARENT = 5,
	COLOR_REFLECTIVE = 6,
	WIREFRAME = 7,
	TWOSIDED = 8,
	SHADING_MODEL = 9,
	BLEND_FUNC = 10,
	OPACITY = 11,
	SHININESS = 12,
	SHININESS_STRENGTH = 13,
	REFRACTI = 14,
	PATH = 15,
	TEXBLEND = 16,
	TEXOP = 17,
	MAPPING = 18,
	UVWSRC = 19,
	MAPPINGMODE_U = 20,
	MAPPINGMODE_V = 21,
	TEXMAP_AXIS = 22,
	TEXFLAGS = 23,
	BUMPSCALING = 24,
	BACKGROUND_IMAGE = 25,
	REFLECTIVITY = 26,
	UVTRANSFORM = 27
};

struct MatProp {
	MatProp(aiString t) {
		ptr = new aiString(t);
	}

	MatProp(aiColor3D t) {
		ptr = new aiColor3D(t);
	}

	MatProp(aiVector3D t) {
		ptr = new aiVector3D(t);
	}

	MatProp(aiUVTransform t) {
		ptr = new aiUVTransform(t);
	}

	MatProp(int t) {
		ptr = new int(t);
	}

	MatProp(float t) {
		ptr = new float(t);
	}

	~MatProp() {
		delete ptr;
	}

	operator aiString() {
		return aiString(*((aiString*)ptr));
	}

	operator aiColor3D() {
		return aiColor3D(*((aiColor3D*)ptr));
	}

	operator aiVector3D() {
		return aiVector3D(*((aiVector3D*)ptr));
	}

	operator aiUVTransform() {
		return aiUVTransform(*((aiUVTransform*)ptr));
	}

	operator int() {
		return int(*((int*)ptr));
	}

	operator float() {
		return float(*((float*)ptr));
	}

	void* ptr;
};

class MaterialMeta{

public:
	MaterialMeta(const aiMaterial*);

	MaterialMeta(const aiMaterial*, const aiTextureType&);

	bool PropertyIsInitalized(const MatMetaProperty&) const;

	MatProp GetProperty(const MatMetaProperty&) const;
	
	void LogProperties();

private:

	/* ------------------------------------ MATERIAL DATA ------------------------------------ */

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
	float _TEXBLEND = -FLT_MAX;
	int _TEXOP = INT_MIN;
	int _MAPPING = INT_MIN;
	int _UVWSRC = INT_MIN;
	int _MAPPINGMODE_U = INT_MIN;
	int _MAPPINGMODE_V = INT_MIN;
	aiVector3D _TEXMAP_AXIS;
	int _TEXFLAGS;
	int _BUMPSCALING;
	int _BACKGROUND_IMAGE;
	int _REFLECTIVITY;
	aiUVTransform _UVTRANSFORM;

	/* -------------------------------------- META DATA -------------------------------------- */

	bool VarsInitalized[28]; //array of bools corresponding to each variable has been initalized from a MAT_KEY. (not default value)
};