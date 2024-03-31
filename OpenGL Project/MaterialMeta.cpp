#include "pch.h"

#include "MaterialMeta.h"

MatMeta::MatMeta(const aiMaterial* mat, const aiTextureType type) {

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

	mat->Get(AI_MATKEY_NAME, _NAME);
	properties[MATMETA_NAME] = MatMetaProperty(&_NAME, MatMetaType_aiString);

	mat->Get(AI_MATKEY_COLOR_DIFFUSE, _COLOR_DIFFUSE);
	properties[MATMETA_COLOR_DIFFUSE] = MatMetaProperty(&_COLOR_DIFFUSE, MatMetaType_aiColor3D);

	mat->Get(AI_MATKEY_COLOR_SPECULAR, _COLOR_SPECULAR);
	properties[MATMETA_COLOR_SPECULAR] = MatMetaProperty(&_COLOR_SPECULAR, MatMetaType_aiColor3D);

	mat->Get(AI_MATKEY_COLOR_AMBIENT, _COLOR_AMBIENT);
	properties[MATMETA_COLOR_AMBIENT] = MatMetaProperty(&_COLOR_AMBIENT, MatMetaType_aiColor3D);

	mat->Get(AI_MATKEY_COLOR_EMISSIVE, _COLOR_EMISSIVE);
	properties[MATMETA_COLOR_EMISSIVE] = MatMetaProperty(&_COLOR_EMISSIVE, MatMetaType_aiColor3D);

	mat->Get(AI_MATKEY_COLOR_TRANSPARENT, _COLOR_TRANSPARENT);
	properties[MATMETA_COLOR_TRANSPARENT] = MatMetaProperty(&_COLOR_TRANSPARENT, MatMetaType_aiColor3D);

	mat->Get(AI_MATKEY_COLOR_REFLECTIVE, _COLOR_REFLECTIVE);
	properties[MATMETA_COLOR_REFLECTIVE] = MatMetaProperty(&_COLOR_REFLECTIVE, MatMetaType_aiColor3D);

	mat->Get(AI_MATKEY_ENABLE_WIREFRAME, _WIREFRAME);
	properties[MATMETA_WIREFRAME] = MatMetaProperty(&_WIREFRAME, MatMetaType_int);

	mat->Get(AI_MATKEY_TWOSIDED, _TWOSIDED);
	properties[MATMETA_TWOSIDED] = MatMetaProperty(&_TWOSIDED, MatMetaType_int);

	mat->Get(AI_MATKEY_SHADING_MODEL, _SHADING_MODEL);
	properties[MATMETA_SHADING_MODEL] = MatMetaProperty(&_SHADING_MODEL, MatMetaType_int);

	mat->Get(AI_MATKEY_BLEND_FUNC, _BLEND_FUNC);
	properties[MATMETA_BLEND_FUNC] = MatMetaProperty(&_BLEND_FUNC, MatMetaType_int);

	mat->Get(AI_MATKEY_OPACITY, _OPACITY);
	properties[MATMETA_OPACITY] = MatMetaProperty(&_OPACITY, MatMetaType_float);

	mat->Get(AI_MATKEY_SHININESS, _SHININESS);
	properties[MATMETA_SHININESS] = MatMetaProperty(&_SHININESS, MatMetaType_float);

	mat->Get(AI_MATKEY_SHININESS_STRENGTH, _SHININESS_STRENGTH);
	properties[MATMETA_SHININESS_STRENGTH] = MatMetaProperty(&_SHININESS_STRENGTH, MatMetaType_float);

	mat->Get(AI_MATKEY_REFRACTI, _REFRACTI);
	properties[MATMETA_REFRACTI] = MatMetaProperty(&_REFRACTI, MatMetaType_float);



	//properties without default values

	if (AI_SUCCESS == mat->Get(AI_MATKEY_BUMPSCALING, _BUMPSCALING)) {
		properties[MATMETA_BUMPSCALING] = MatMetaProperty(&_BUMPSCALING, MatMetaType_int);
	}

	if (AI_SUCCESS == mat->Get(AI_MATKEY_GLOBAL_BACKGROUND_IMAGE, _BACKGROUND_IMAGE)) {
		properties[MATMETA_BACKGROUND_IMAGE] = MatMetaProperty(&_BACKGROUND_IMAGE, MatMetaType_int);
	}

	if (AI_SUCCESS == mat->Get(AI_MATKEY_REFLECTIVITY, _REFLECTIVITY)) {
		properties[MATMETA_REFLECTIVITY] = MatMetaProperty(&_REFLECTIVITY, MatMetaType_int);
	}

	//texture type specific attributes
	if (type != -1) {
		if (AI_SUCCESS == mat->Get(AI_MATKEY_TEXTURE(type, 0), _PATH)) {
			properties[MATMETA_PATH] = MatMetaProperty(&_PATH, MatMetaType_aiString);
		}

		if (AI_SUCCESS == mat->Get(AI_MATKEY_TEXBLEND(type, 0), _TEXBLEND)) {
			properties[MATMETA_TEXBLEND] = MatMetaProperty(&_TEXBLEND, MatMetaType_float);
		}

		if (AI_SUCCESS == mat->Get(AI_MATKEY_TEXOP(type, 0), _TEXOP)) {
			properties[MATMETA_TEXOP] = MatMetaProperty(&_TEXOP, MatMetaType_int);
		}


		if (AI_SUCCESS == mat->Get(AI_MATKEY_MAPPING(type, 0), _MAPPING)) {
			properties[MATMETA_MAPPING] = MatMetaProperty(&_MAPPING, MatMetaType_int);
		}

		if (AI_SUCCESS == mat->Get(AI_MATKEY_UVWSRC(type, 0), _UVWSRC)) {
			properties[MATMETA_UVWSRC] = MatMetaProperty(&_UVWSRC, MatMetaType_int);
		}

		if (AI_SUCCESS == mat->Get(AI_MATKEY_MAPPINGMODE_U(type, 0), _MAPPINGMODE_U)) {
			properties[MATMETA_MAPPINGMODE_U] = MatMetaProperty(&_MAPPINGMODE_U, MatMetaType_int);
		}

		if (AI_SUCCESS == mat->Get(AI_MATKEY_MAPPINGMODE_V(type, 0), _MAPPINGMODE_V)) {
			properties[MATMETA_MAPPINGMODE_V] = MatMetaProperty(&_MAPPINGMODE_V, MatMetaType_int);
		}

		if (AI_SUCCESS == mat->Get(AI_MATKEY_TEXMAP_AXIS(type, 0), _TEXMAP_AXIS)) {
			properties[MATMETA_TEXMAP_AXIS] = MatMetaProperty(&_TEXMAP_AXIS, MatMetaType_aiVector3D);
		}

		if (AI_SUCCESS == mat->Get(AI_MATKEY_TEXFLAGS(type, 0), _TEXFLAGS)) {
			properties[MATMETA_TEXFLAGS] = MatMetaProperty(&_TEXFLAGS, MatMetaType_int);
		}


		if (AI_SUCCESS == mat->Get(AI_MATKEY_UVTRANSFORM(type, 0), _UVTRANSFORM)) {
			properties[MATMETA_UVTRANSFORM] = MatMetaProperty(&_UVTRANSFORM, MatMetaType_aiUVTransform);
		}

	}
}

void MatMeta::LogProperties() {
	for (auto& [key, value] : properties) {

		switch (key) {

		case (MatMetaType_aiString): {
			aiString v = value;

			std::cout << "aiString" << v.C_Str() << std::endl;
			break;
		}

		case (MatMetaType_aiColor3D): {
			aiColor3D v = value;

			std::cout << "aiColor3D (" << v.r << ", " << v.g << ", " << v.b << ")" << std::endl;
			break;
		}

		case (MatMetaType_int): {
			int v = value;

			std::cout << "int" << v << std::endl;
			break;
		}

		case (MatMetaType_float): {
			float v = value;

			std::cout << "float" << v << std::endl;
			break;
		}

		case (MatMetaType_aiVector3D): {
			aiVector3D v = value;

			std::cout << "aiVector3D (" << v.x << ", " << v.y << ", " << v.z << ")" << std::endl;
			break;
		}

		case (MatMetaType_aiUVTransform): {
			aiUVTransform v = value;

			std::cout << "aiUVTransform:" << std::endl;
			std::cout << "    mRotation" << v.mRotation << std::endl;
			std::cout << "    mScaling (" << v.mScaling.x << ", " << v.mScaling.y << ")" << std::endl;
			std::cout << "    mTranslation (" << v.mTranslation.x << ", " << v.mTranslation.y << ")" << std::endl;
			break;
		}

		//default: 
			//break;

		}
	}
}


//honestly just delete all of this, make a file to print all attributes and document the functions and then everything else can be used through normal API.

//prob dont need to make heap memory
MatMetaProperty::~MatMetaProperty() {
	delete entry;
}

//prob dont need this shit either.
MatMetaProperty::MatMetaProperty(const MatMetaProperty& ref) {
	type = ref.type;
	size = ref.size;

	entry = malloc(100);


	
	memcpy(entry, ref.entry, size);
}

MatMetaProperty::MatMetaProperty(void* e, MatMetaType t) {
	

	//prob dont  need to check each enum
	switch (t) {

	case (MatMetaType_aiString): {
		entry = new aiString();
		size = sizeof(aiString);
		memcpy(entry, e, size);
		break;
	}

	case (MatMetaType_aiColor3D): {
		entry = new aiColor3D();
		size = sizeof(aiColor3D);
		memcpy(entry, e, size);
		break;
	}

	case (MatMetaType_int): {
		entry = new int();
		size = sizeof(int);
		memcpy(entry, e, size);
		break;
	}

	case (MatMetaType_float): {
		entry = new float();
		size = sizeof(float);
		memcpy(entry, e, size);
		break;
	}

	case (MatMetaType_aiVector3D): {
		entry = new aiVector3D();
		size = sizeof(aiVector3D);
		memcpy(entry, e, size);
		break;
	}

	case (MatMetaType_aiUVTransform): {
		entry = new aiUVTransform();
		size = sizeof(aiUVTransform);
		memcpy(entry, e, size);
		break;
	}

	default:
		break;

	}

	type = t;
}

MatMetaProperty::operator aiColor3D() {
	if (type != MatMetaType_aiColor3D) {
		throw;
	}

	aiColor3D out;

	memcpy(&out, entry, sizeof(out));

	return out;
}

MatMetaProperty::operator aiString() {
	if (type != MatMetaType_aiString) {
		throw;
	}

	aiString out;

	memcpy(&out, entry, sizeof(out));

	return out;
}

MatMetaProperty::operator int() {
	if (type != MatMetaType_int) {
		throw;
	}



	int out;

	memcpy(&out, entry, sizeof(out));
	
	return out;
}

MatMetaProperty::operator float() {
	if (type != MatMetaType_float) {
		throw;
	}

	float out;

	memcpy(&out, entry, sizeof(out));

	return out;
}

MatMetaProperty::operator aiVector3D() {
	if (type != MatMetaType_aiVector3D) {
		throw;
	}

	aiVector3D out;

	memcpy(&out, entry, sizeof(out));

	return out;
}

MatMetaProperty::operator aiUVTransform() {
	if (type != MatMetaType_aiUVTransform) {
		throw;
	}

	aiUVTransform out;

	memcpy(&out, entry, sizeof(out));

	return out;
}