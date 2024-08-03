#include "pch.h"

#include "AssetManager.h"

#include "MemoryMapper.h"

AssetManager::~AssetManager() {
    for (auto& [key, value] : models) {
        if (value.isLoaded) {
            delete value.model;
        }
    }
}

static std::vector<std::filesystem::path> GetDirFiles(const std::string& path) {
    std::vector<std::filesystem::path> files;


    for (const auto& entry : std::filesystem::directory_iterator(path)) {

        std::cout << entry.path() << std::endl;

        files.push_back(std::string(entry.path().generic_string()));
    }

    return files;
}

void BuildModels() {
    const std::vector<std::filesystem::path>& files = GetDirFiles(SOURCE_ASSET_FILE_DIR);

    for (int i = 0; i < files.size(); ++i) {

        const std::filesystem::path& readLoc = files[i].generic_string();

        //obv dont load folder as a model
        if (std::filesystem::is_directory(readLoc)) {
            continue;
        }

        std::filesystem::path writeLoc = std::filesystem::path(BUILD_ASSET_FILE_DIR);
        writeLoc /= std::filesystem::path(files[i]).replace_extension(".binary").filename();

        SourceToBuild(readLoc.generic_string(), writeLoc.generic_string());
    }
}

AssetManager::AssetManager() {

    const std::vector<std::filesystem::path>& files = GetDirFiles(BUILD_ASSET_FILE_DIR);

    for (int i = 0; i < files.size(); ++i) {


        const std::string& filepath = std::filesystem::absolute(files[i]).generic_string();

        const std::string& name = std::filesystem::path(files[i]).replace_extension("").filename().generic_string();

        models.emplace(name, ModelLoaderInfo{ false, filepath, nullptr });
    }
}

Model* AssetManager::LoadModel(const std::string& name) {
    std::unordered_map<std::string, ModelLoaderInfo>::iterator it = models.find(name);

    if (it == models.end()) {
        throw;
    }

    ModelLoaderInfo* info = &(*it).second;

    if (info->isLoaded) {
        return info->model;
    }

    info->isLoaded = true;
    info->model = LoadBinaryFile(info->path);
    
    return info->model;
}