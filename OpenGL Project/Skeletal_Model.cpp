#include "pch.h"

#include "Skeletal_Model.h"

void Skeletal_Model::Attach() {

    if (!isAttached) {

        GLuint buf[2];

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(2, buf);


        size_t Vertex_Size = sizeof((vertices)[0]);

        glBindBuffer(GL_ARRAY_BUFFER, buf[0]);
        glBufferData(GL_ARRAY_BUFFER, Vertex_Size * vertices.size(), &vertices[0], GL_STATIC_DRAW);

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

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buf[1]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

        glBindVertexArray(0);

        for (int i = 0; i < Materials.size(); ++i) {
            MaterialBuffer* buf = new MaterialBuffer(Materials[i]);

            MBO.push_back(buf);
        }

        isAttached = true;

    }


}

void Skeletal_Model::Detach() {

    if (isAttached) {

        glDeleteVertexArrays(1, &VAO);

        for (int i = 0; i < MBO.size(); ++i) {
            delete MBO[i];
        }

        MBO.empty();

        isAttached = false;

    }

}

void Skeletal_Model::Render(const ShaderProgram* shader) const {

    if (!isAttached) {
        throw;
    }


    glBindVertexArray(VAO);

    for (const SubMesh& sub : mesh_data) {

        const MaterialBuffer* mat = MBO[sub.materialIndex];

        shader->setBools("TexturesExist", &mat->GetTexturesExist()[0], numTexTypes);
        shader->setVec4s("Colors", (float*)&mat->GetColors()[0], numTexTypes); //6 vec 3 = 18.

        GLint textureIndices[numTexTypes];
        int textureIndex = 0;

        for (int i = 0; i < numTexTypes; i++) {

            textureIndices[i] = textureIndex;

            if (mat->GetTexturesExist()[i]) {
                glActiveTexture(GL_TEXTURE0 + textureIndex++);
                glBindTexture(GL_TEXTURE_2D, mat->GetTextures()[i]);
            }
        }

        shader->setTextures("Textures", textureIndices, numTexTypes);

        //Draw
        glDrawElementsBaseVertex(
            GL_TRIANGLES,
            sub.indexCount,
            GL_UNSIGNED_INT,
            (void*)(sizeof(unsigned int) * sub.BaseIndex),
            sub.BaseVertex
        );


    }

    glBindVertexArray(0);
}

Model_Type Skeletal_Model::GetModelType() const {
    return Model_Type_Skeletal;
}

const Skeleton* Skeletal_Model::GetSkeleton() const {
    return skeleton;
}

const std::vector<Animation*>* Skeletal_Model::GetAnimations() const {
    return &animations;
}

const StaticBoundingBox* Skeletal_Model::GetSBB() const {
    return sbb;
}

Skeletal_Model::~Skeletal_Model() {

    Detach();

    for (int i = 0; i < animations.size(); ++i) {
        delete animations[i];
    }

    delete sbb;

    delete skeleton;
}