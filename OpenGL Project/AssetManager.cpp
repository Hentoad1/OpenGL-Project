#include "pch.h"

#include "AssetManager.h"

#include "MemoryMapper.h"

AssetManager::~AssetManager() {
    for (auto& [key, value] : models) {
        if (value.isLoaded) {
            delete value.model;
            delete value.attached;
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

        models.emplace(name, ModelLoaderInfo{ false, filepath, nullptr, nullptr });
    }
}

ModelData* AssetManager::LoadModel(const std::string& name) {
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


ModelBuffers* AssetManager::Attach(ModelData* md){

    ModelLoaderInfo* info = nullptr;

    for (auto& [key, pair] : models) {
        if (pair.model == md) {
            info = &pair;
        }
    }

    if (info->attached != nullptr) {
        return info->attached;
    }

    //populate VAO

    GLuint VAO;

    GLuint buf[2];

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(2, buf);

    if (md->vType == VERTEX_TYPE_BASIC) {

        const std::vector<Vertex>* vertices = static_cast<std::vector<Vertex>*>(md->vertices);

        size_t Vertex_Size = sizeof((*vertices)[0]);

        glBindBuffer(GL_ARRAY_BUFFER, buf[0]);
        glBufferData(GL_ARRAY_BUFFER, Vertex_Size * vertices->size(), &(*vertices)[0], GL_STATIC_DRAW);

        glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, Vertex_Size, 0);
        glEnableVertexAttribArray(POSITION_LOCATION);

        glVertexAttribPointer(TEXTURE_LOCATION, 2, GL_FLOAT, GL_FALSE, Vertex_Size, (void*)12);
        glEnableVertexAttribArray(TEXTURE_LOCATION);

        glVertexAttribPointer(NORMAL_LOCATION, 3, GL_FLOAT, GL_FALSE, Vertex_Size, (void*)20);
        glEnableVertexAttribArray(NORMAL_LOCATION);

    }
    else if (md->vType == VERTEX_TYPE_SKELETAL) {

        const std::vector<sVertex>* vertices = static_cast<std::vector<sVertex>*>(md->vertices);

        size_t Vertex_Size = sizeof((*vertices)[0]);

        glBindBuffer(GL_ARRAY_BUFFER, buf[0]);
        glBufferData(GL_ARRAY_BUFFER, Vertex_Size * vertices->size(), &(*vertices)[0], GL_STATIC_DRAW);

        glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, Vertex_Size, 0);
        glEnableVertexAttribArray(POSITION_LOCATION);

        glVertexAttribPointer(TEXTURE_LOCATION, 2, GL_FLOAT, GL_FALSE, Vertex_Size, (void*)12);
        glEnableVertexAttribArray(TEXTURE_LOCATION);

        glVertexAttribPointer(NORMAL_LOCATION, 3, GL_FLOAT, GL_FALSE, Vertex_Size, (void*)20);
        glEnableVertexAttribArray(NORMAL_LOCATION);

        glVertexAttribIPointer(BONE_INDEX_LOCATION, 4, GL_INT, Vertex_Size, (void*)32);
        glEnableVertexAttribArray(BONE_INDEX_LOCATION);

        glVertexAttribPointer(BONE_WEIGHT_LOCATION, 4, GL_FLOAT, GL_FALSE, Vertex_Size, (void*)48);
        glEnableVertexAttribArray(BONE_WEIGHT_LOCATION);
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buf[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(md->indices[0])* md->indices.size(), &md->indices[0], GL_STATIC_DRAW);

    glBindVertexArray(0);

    std::vector<MaterialBuffer*> MBO = std::vector<MaterialBuffer*>();

    for (int i = 0; i < md->Materials.size(); ++i) {
        MaterialBuffer* buf = new MaterialBuffer(md->Materials[i]);

        MBO.push_back(buf);
    }

    ModelBuffers* CreatedData = new ModelBuffers{ VAO, MBO, md->mesh_data, md->skeleton, md->animations, md->sbb, md->min, md->max };

    info->attached = CreatedData;

    return CreatedData;
}