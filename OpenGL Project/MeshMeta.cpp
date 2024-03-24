#include "pch.h"

#include "MeshMeta.h"

MeshMeta::MeshMeta(aiMetadata* data) {
	for (int i = 0; i < data->mNumProperties; i++) {
		properties[data->mKeys[i].C_Str()] = MeshMetaProperty(&data->mValues[i]);
	}
}

void MeshMeta::LogProperties() {
	for (const auto& pair : properties) {

		std::cout << pair.first << "  ";
		std::cout << (std::string)((MeshMetaProperty)pair.second);
		std::cout << std::endl;
	}
}

MeshMetaProperty MeshMeta::Get(const std::string& key) {
	return properties[key];
}

MeshMetaProperty::MeshMetaProperty(aiMetadataEntry* e) {
	entry = e;
}

MeshMetaProperty::operator bool() {
	if (entry->mType != AI_BOOL) {
		throw;
	}

	bool out;

	memcpy(&out, entry->mData, sizeof(out));

	return out;
}

MeshMetaProperty::operator int32_t() {
	if (entry->mType != AI_INT32) {
		throw;
	}

	int32_t out;

	memcpy(&out, entry->mData, sizeof(out));

	return out;
}

MeshMetaProperty::operator uint32_t() {
	if (entry->mType != AI_UINT32) {
		throw;
	}

	uint32_t out;

	memcpy(&out, entry->mData, sizeof(out));

	return out;
}

MeshMetaProperty::operator int64_t() {
	if (entry->mType != AI_INT64) {
		throw;
	}

	int64_t out;

	memcpy(&out, entry->mData, sizeof(out));

	return out;
}

MeshMetaProperty::operator uint64_t() {
	if (entry->mType != AI_UINT64) {
		throw;
	}

	uint64_t out;

	memcpy(&out, entry->mData, sizeof(out));

	return out;
}

MeshMetaProperty::operator float() {
	if (entry->mType != AI_FLOAT) {
		throw;
	}

	float out;

	memcpy(&out, entry->mData, sizeof(out));

	return out;
}

MeshMetaProperty::operator double() {
	if (entry->mType != AI_DOUBLE) {
		throw;
	}

	double out;

	memcpy(&out, entry->mData, sizeof(out));

	return out;
}

MeshMetaProperty::operator aiString() {
	if (entry->mType != AI_AISTRING) {
		throw;
	}

	aiString out;

	memcpy(&out, entry->mData, sizeof(out));

	return out;
}

MeshMetaProperty::operator aiVector3D() {
	if (entry->mType != AI_AIVECTOR3D) {
		throw;
	}

	aiVector3D out;

	memcpy(&out, entry->mData, sizeof(out));

	return out;
}

MeshMetaProperty::operator aiMetadata() {
	if (entry->mType != AI_AIMETADATA) {
		throw;
	}

	aiMetadata out;

	memcpy(&out, entry->mData, sizeof(out));

	return out;
}

MeshMetaProperty::operator std::string() {
	std::string out;

	switch (entry->mType) {

	case(AI_BOOL):{
		out = "AI_BOOL";
		out += "  ";
		bool d1 = *this;
		out += d1 ? "TRUE" : "FALSE";
		break;
	}

	case(AI_INT32): {
		out = "AI_INT32";
		out += "  ";
		int32_t d2 = *this;
		out += std::to_string(d2);
		break;
	}
		
	case(AI_UINT32): {
		out = "AI_UINT32";
		out += "  ";
		uint32_t d3 = *this;
		out += std::to_string(d3);
		break;
	}
		
	case(AI_INT64): {
		out = "AI_INT64";
		out += "  ";
		int64_t d4 = *this;
		out += std::to_string(d4);
		break;
	}
		
	case(AI_UINT64): {
		out = "AI_UINT64";
		out += "  ";
		uint64_t d5 = *this;
		out += std::to_string(d5);
		break;
	}
		
	case(AI_FLOAT): {
		out = "AI_FLOAT";
		out += "  ";
		float d6 = *this;
		out += std::to_string(d6);
		break;
	}
		
	case(AI_DOUBLE): {
		out = "AI_DOUBLE";
		out += "  ";
		double d7 = *this;
		out += std::to_string(d7);
		break;
	}

	case(AI_AISTRING): {
		out = "AI_AISTRING";
		out += "  ";
		aiString d8 = *this;
		out += d8.C_Str();
		break;
	}
		
	case(AI_AIVECTOR3D): {
		out = "AI_AIVECTOR3D";
		out += "  ";
		aiVector3D d9 = *this;
		out += "(" + std::to_string(d9.x) + ", " + std::to_string(d9.y) + ", " + std::to_string(d9.z) + ")";
		break;
	}
		
	case(AI_AIMETADATA): {
		out = "AI_AIMETADATA";
		out += "  ";
		//aiMetadata d10 = *this;
		out += "too lazy to display"; //reinterpret_cast<char*>(&d111);
		break;
	}

	}

	return out;
}