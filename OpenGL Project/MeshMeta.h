#pragma once

#include "pch.h"

class MeshMetaProperty {
public:
	MeshMetaProperty() {};

	MeshMetaProperty(aiMetadataEntry*);

	operator bool();
	operator int32_t();
	operator uint32_t();
	operator int64_t();
	operator uint64_t();
	operator float();
	operator double();
	operator aiString();
	operator aiVector3D();
	operator aiMetadata();

	operator std::string();

private:
	aiMetadataEntry* entry = nullptr;
};

class MeshMeta {

public:

	MeshMeta(aiMetadata*);

	MeshMetaProperty Get(const std::string& key);

	void LogProperties();

private:
	std::unordered_map<std::string, MeshMetaProperty> properties;
};



/*
		AI_BOOL = 0,
		AI_INT32 = 1,
		AI_UINT64 = 2,
		AI_FLOAT = 3,
		AI_DOUBLE = 4,
		AI_AISTRING = 5,
		AI_AIVECTOR3D = 6,
		AI_AIMETADATA = 7,
		AI_INT64 = 8,
		AI_UINT32 = 9,
		AI_META_MAX = 10,
	*/