#pragma once

#include "pch.h"

#include "ModelData.h"

static constexpr const char* BUILD_ASSET_FILE_DIR = "Assets/Build";
static constexpr const char* SOURCE_ASSET_FILE_DIR = "Assets/Source";

struct ModelLoaderInfo {
	bool isLoaded;
	std::string path;

	ModelData* model;
	ModelBuffers* attached;
};

class AssetManager {

private:
	std::unordered_map<std::string, ModelLoaderInfo> models;

public:
	AssetManager();

	ModelData* LoadModel(const std::string& name);

	ModelBuffers* Attach(ModelData*);
};

void BuildModels();