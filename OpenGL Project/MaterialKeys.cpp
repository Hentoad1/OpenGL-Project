#include "pch.h"

#include "MaterialKeys.h"

static constexpr bool defaultInitalized[28] = {
	false,
	true,
	true,
	true,
	true,
	true,
	true,
	true,
	true,
	true,
	true,
	true,
	true,
	true,
	true,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false
};

MaterialMeta::MaterialMeta(const aiMaterial* mat, const aiTextureType& type) {
	int index = 0;

	VarsInitalized[index++] = AI_SUCCESS == mat->Get(AI_MATKEY_NAME, _NAME);

	VarsInitalized[index++] = AI_SUCCESS == mat->Get(AI_MATKEY_COLOR_DIFFUSE, _COLOR_DIFFUSE);
	VarsInitalized[index++] = AI_SUCCESS == mat->Get(AI_MATKEY_COLOR_SPECULAR, _COLOR_SPECULAR);
	VarsInitalized[index++] = AI_SUCCESS == mat->Get(AI_MATKEY_COLOR_AMBIENT, _COLOR_AMBIENT);
	VarsInitalized[index++] = AI_SUCCESS == mat->Get(AI_MATKEY_COLOR_EMISSIVE, _COLOR_EMISSIVE);
	VarsInitalized[index++] = AI_SUCCESS == mat->Get(AI_MATKEY_COLOR_TRANSPARENT, _COLOR_TRANSPARENT);
	VarsInitalized[index++] = AI_SUCCESS == mat->Get(AI_MATKEY_COLOR_REFLECTIVE, _COLOR_REFLECTIVE);

	VarsInitalized[index++] = AI_SUCCESS == mat->Get(AI_MATKEY_ENABLE_WIREFRAME, _WIREFRAME);
	VarsInitalized[index++] = AI_SUCCESS == mat->Get(AI_MATKEY_TWOSIDED, _TWOSIDED);
	VarsInitalized[index++] = AI_SUCCESS == mat->Get(AI_MATKEY_SHADING_MODEL, _SHADING_MODEL);
	VarsInitalized[index++] = AI_SUCCESS == mat->Get(AI_MATKEY_BLEND_FUNC, _BLEND_FUNC);

	VarsInitalized[index++] = AI_SUCCESS == mat->Get(AI_MATKEY_OPACITY, _OPACITY);
	VarsInitalized[index++] = AI_SUCCESS == mat->Get(AI_MATKEY_SHININESS, _SHININESS);
	VarsInitalized[index++] = AI_SUCCESS == mat->Get(AI_MATKEY_SHININESS_STRENGTH, _SHININESS_STRENGTH);
	VarsInitalized[index++] = AI_SUCCESS == mat->Get(AI_MATKEY_REFRACTI, _REFRACTI);

	VarsInitalized[index++] = AI_SUCCESS == mat->Get(AI_MATKEY_TEXTURE(aiTextureType_DIFFUSE, 0), _PATH);
	VarsInitalized[index++] = AI_SUCCESS == mat->Get(AI_MATKEY_TEXBLEND(aiTextureType_DIFFUSE, 0), _TEXBLEND);
	VarsInitalized[index++] = AI_SUCCESS == mat->Get(AI_MATKEY_TEXOP(aiTextureType_DIFFUSE, 0), _TEXOP);

	VarsInitalized[index++] = AI_SUCCESS == mat->Get(AI_MATKEY_MAPPING(aiTextureType_DIFFUSE, 0), _MAPPING);
	VarsInitalized[index++] = AI_SUCCESS == mat->Get(AI_MATKEY_UVWSRC(aiTextureType_DIFFUSE, 0), _UVWSRC);
	VarsInitalized[index++] = AI_SUCCESS == mat->Get(AI_MATKEY_MAPPINGMODE_U(aiTextureType_DIFFUSE, 0), _MAPPINGMODE_U);
	VarsInitalized[index++] = AI_SUCCESS == mat->Get(AI_MATKEY_MAPPINGMODE_V(aiTextureType_DIFFUSE, 0), _MAPPINGMODE_V);
	VarsInitalized[index++] = AI_SUCCESS == mat->Get(AI_MATKEY_TEXMAP_AXIS(aiTextureType_DIFFUSE, 0), _TEXMAP_AXIS);
	VarsInitalized[index++] = AI_SUCCESS == mat->Get(AI_MATKEY_TEXFLAGS(aiTextureType_DIFFUSE, 0), _TEXFLAGS);

	VarsInitalized[index++] = AI_SUCCESS == mat->Get(AI_MATKEY_BUMPSCALING, _BUMPSCALING);
	VarsInitalized[index++] = AI_SUCCESS == mat->Get(AI_MATKEY_GLOBAL_BACKGROUND_IMAGE, _BACKGROUND_IMAGE);
	VarsInitalized[index++] = AI_SUCCESS == mat->Get(AI_MATKEY_REFLECTIVITY, _REFLECTIVITY);
	VarsInitalized[index++] = AI_SUCCESS == mat->Get(AI_MATKEY_UVTRANSFORM(aiTextureType_DIFFUSE, 0), _UVTRANSFORM);
}

bool MaterialMeta::PropertyIsInitalized(const MatMetaProperty& prop) const {
	return VarsInitalized[prop];
}

MatProp MaterialMeta::GetProperty(const MatMetaProperty& prop) const {
	switch (prop) {
	case(NAME):
		return MatProp(_NAME);
	case(COLOR_DIFFUSE):
		return MatProp(_COLOR_DIFFUSE);
	case(COLOR_AMBIENT):
		return MatProp(_COLOR_AMBIENT);
	case(COLOR_EMISSIVE):
		return MatProp(_COLOR_EMISSIVE);
	case(COLOR_TRANSPARENT):
		return MatProp(_COLOR_TRANSPARENT);
	case(COLOR_REFLECTIVE):
		return MatProp(_COLOR_REFLECTIVE);
	case(WIREFRAME):
		return MatProp(_WIREFRAME);
	case(TWOSIDED):
		return MatProp(_TWOSIDED);
	case(SHADING_MODEL):
		return MatProp(_SHADING_MODEL);
	case(BLEND_FUNC):
		return MatProp(_BLEND_FUNC);
	case(OPACITY):
		return MatProp(_OPACITY);
	case(SHININESS):
		return MatProp(_SHININESS);
	case(SHININESS_STRENGTH):
		return MatProp(_SHININESS_STRENGTH);
	case(REFRACTI):
		return MatProp(_REFRACTI);
	case(PATH):
		return MatProp(_PATH);
	case(TEXBLEND):
		return MatProp(_TEXBLEND);
	case(TEXOP):
		return MatProp(_TEXOP);
	case(MAPPING):
		return MatProp(_MAPPING);
	case(UVWSRC):
		return MatProp(_UVWSRC);
	case(MAPPINGMODE_U):
		return MatProp(_MAPPINGMODE_U);
	case(MAPPINGMODE_V):
		return MatProp(_MAPPINGMODE_V);
	case(TEXMAP_AXIS):
		return MatProp(_TEXMAP_AXIS);
	case(TEXFLAGS):
		return MatProp(_TEXFLAGS);
	case(BUMPSCALING):
		return MatProp(_BUMPSCALING);
	case(BACKGROUND_IMAGE):
		return MatProp(_BACKGROUND_IMAGE);
	case(REFLECTIVITY):
		return MatProp(_REFLECTIVITY);
	case(UVTRANSFORM):
		return MatProp(_UVTRANSFORM);
	default:
		throw;
	}
}

static std::string logInitalized(int index, bool* initVars) {

	if (initVars[index]){
		return "INITIALIZED";
	}

	if (defaultInitalized[index]) {
		return "DEFAULT    ";
	}

	return "GARBAGE    ";
}

void MaterialMeta::LogProperties() {
	int i = 0;

	std::cout << "---------------------------------------------------------------------" << std::endl;

	std::cout << logInitalized(i++, VarsInitalized) << " " << "AI_MATKEY_NAME: " << _NAME.C_Str() << std::endl;

	std::cout << logInitalized(i++, VarsInitalized) << " " << "AI_MATKEY_COLOR_DIFFUSE: " << "color(" << _COLOR_DIFFUSE.r << ", " << _COLOR_DIFFUSE.g << ", " << _COLOR_DIFFUSE.b << ")" << std::endl;
	std::cout << logInitalized(i++, VarsInitalized) << " " << "AI_MATKEY_COLOR_SPECULAR: " << "color(" << _COLOR_SPECULAR.r << ", " << _COLOR_SPECULAR.g << ", " << _COLOR_SPECULAR.b << ")" << std::endl;
	std::cout << logInitalized(i++, VarsInitalized) << " " << "AI_MATKEY_COLOR_AMBIENT: " << "color(" << _COLOR_AMBIENT.r << ", " << _COLOR_AMBIENT.g << ", " << _COLOR_AMBIENT.b << ")" << std::endl;
	std::cout << logInitalized(i++, VarsInitalized) << " " << "AI_MATKEY_COLOR_EMISSIVE: " << "color(" << _COLOR_EMISSIVE.r << ", " << _COLOR_EMISSIVE.g << ", " << _COLOR_EMISSIVE.b << ")" << std::endl;
	std::cout << logInitalized(i++, VarsInitalized) << " " << "AI_MATKEY_COLOR_TRANSPARENT: " << "color(" << _COLOR_TRANSPARENT.r << ", " << _COLOR_TRANSPARENT.g << ", " << _COLOR_TRANSPARENT.b << ")" << std::endl;
	std::cout << logInitalized(i++, VarsInitalized) << " " << "AI_MATKEY_COLOR_REFLECTIVE: " << "color(" << _COLOR_REFLECTIVE.r << ", " << _COLOR_REFLECTIVE.g << ", " << _COLOR_REFLECTIVE.b << ")" << std::endl;

	std::cout << logInitalized(i++, VarsInitalized) << " " << "AI_MATKEY_ENABLE_WIREFRAME: " << _WIREFRAME << std::endl;
	std::cout << logInitalized(i++, VarsInitalized) << " " << "AI_MATKEY_TWOSIDED: " << _TWOSIDED << std::endl;
	std::cout << logInitalized(i++, VarsInitalized) << " " << "AI_MATKEY_SHADING_MODEL: " << _SHADING_MODEL << std::endl;
	std::cout << logInitalized(i++, VarsInitalized) << " " << "AI_MATKEY_BLEND_FUNC: " << _BLEND_FUNC << std::endl;

	std::cout << logInitalized(i++, VarsInitalized) << " " << "AI_MATKEY_OPACITY: " << _OPACITY << std::endl;
	std::cout << logInitalized(i++, VarsInitalized) << " " << "AI_MATKEY_SHININESS: " << _SHININESS << std::endl;
	std::cout << logInitalized(i++, VarsInitalized) << " " << "AI_MATKEY_SHININESS_STRENGTH: " << _SHININESS_STRENGTH << std::endl;
	std::cout << logInitalized(i++, VarsInitalized) << " " << "AI_MATKEY_REFRACTI: " << _REFRACTI << std::endl;

	std::cout << logInitalized(i++, VarsInitalized) << " " << "AI_MATKEY_TEXTURE: " << _PATH.C_Str() << std::endl;
	std::cout << logInitalized(i++, VarsInitalized) << " " << "AI_MATKEY_TEXBLEND: " << _TEXBLEND << std::endl;
	std::cout << logInitalized(i++, VarsInitalized) << " " << "AI_MATKEY_TEXOP: " << _TEXOP << std::endl;

	std::cout << logInitalized(i++, VarsInitalized) << " " << "AI_MATKEY_MAPPING: " << _MAPPING << std::endl;
	std::cout << logInitalized(i++, VarsInitalized) << " " << "AI_MATKEY_UVWSRC: " << _UVWSRC << std::endl;
	std::cout << logInitalized(i++, VarsInitalized) << " " << "AI_MATKEY_MAPPINGMODE_U: " << _MAPPINGMODE_U << std::endl;
	std::cout << logInitalized(i++, VarsInitalized) << " " << "AI_MATKEY_MAPPINGMODE_V: " << _MAPPINGMODE_V << std::endl;
	std::cout << logInitalized(i++, VarsInitalized) << " " << "AI_MATKEY_TEXMAP_AXIS: " << "vector3(" << _TEXMAP_AXIS.x << ", " << _TEXMAP_AXIS.y << ", " << _TEXMAP_AXIS.z << ")" << std::endl;
	std::cout << logInitalized(i++, VarsInitalized) << " " << "AI_MATKEY_TEXFLAGS: " << _TEXFLAGS << std::endl;

	std::cout << logInitalized(i++, VarsInitalized) << " " << "AI_MATKEY_BUMPSCALING: " << _BUMPSCALING << std::endl;
	std::cout << logInitalized(i++, VarsInitalized) << " " << "AI_MATKEY_GLOBAL_BACKGROUND_IMAGE: " << _BACKGROUND_IMAGE << std::endl;
	std::cout << logInitalized(i++, VarsInitalized) << " " << "AI_MATKEY_REFLECTIVITY: " << _REFLECTIVITY << std::endl;

	std::cout << logInitalized(i++, VarsInitalized) << " " << "AI_MATKEY_UVTRANSFORM: " << std::endl;
	std::cout << "    mRotation: " << _UVTRANSFORM.mRotation << std::endl;
	std::cout << "    mScaling: " << "vector2(" << _UVTRANSFORM.mScaling.x << ", " << _UVTRANSFORM.mScaling.y << ")" << std::endl;
	std::cout << "    mTranslation: " << "vector2(" << _UVTRANSFORM.mTranslation.x << ", " << _UVTRANSFORM.mTranslation.y << ")" << std::endl;

	std::cout << "--------------------------------------------------------------------------" << std::endl;
}