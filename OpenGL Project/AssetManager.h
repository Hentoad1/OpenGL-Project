#pragma once

#include "pch.h"

#include "Model.h"

static constexpr const char* BUILD_ASSET_FILE_DIR = "Assets/Build";
static constexpr const char* SOURCE_ASSET_FILE_DIR = "Assets/Source";

struct ModelLoaderInfo {
	bool isLoaded;
	std::string path;

	Model* model;
};

class AssetManager {

private:
	std::unordered_map<std::string, ModelLoaderInfo> models;

public:
	AssetManager();

	~AssetManager();

	Model* LoadModel(const std::string& name);
};

void BuildModels();