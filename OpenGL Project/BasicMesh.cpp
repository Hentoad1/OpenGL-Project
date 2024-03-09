
#include "pch.h"
#include "BasicMesh.h"

Mesh::Mesh(std::string path) {
	const aiScene* scene = Load(path);

	GenBuffers(scene);
}

const aiScene* Mesh::Load(std::string path) {
	Assimp::Importer importer;

	// And have it read the given file with some example postprocessing
	// Usually - if speed is not the most important aspect for you - you'll
	// probably to request more postprocessing than we do in this example.
	const aiScene* scene = importer.ReadFile(path,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);

	// If the import failed, report it
	if (nullptr == scene) {
		std::cout << importer.GetErrorString() << std::endl;
		throw;
	}

	return scene;
}

void Mesh::GenBuffers(const aiScene* scene) {

	/* ---------------------------------- GENERATE BUFFER DATA ---------------------------------- */

	std::vector<float> positions;
	std::vector<float> textures;
	std::vector<float> normals;

	std::vector<unsigned int> indices;
	
	mesh_widths = std::vector<unsigned int>();

	unsigned int indexOffset = 0;

	const aiVector3D ZeroVector(0.0f, 0.0f, 0.0f);

	for (int meshIndex = 0; meshIndex < scene->mNumMeshes; ++meshIndex) {
		const aiMesh* mesh = scene->mMeshes[meshIndex];

		if (mesh == nullptr) {
			throw;
		}

		const aiMesh cpy = *mesh;

		//create buffers
		for (int i = 0; i < mesh->mNumVertices; ++i) {
			const aiVector3D& pos = mesh->mVertices[i];
			const aiVector3D& normal = mesh->mNormals[i];
			const aiVector3D& tex = mesh->HasTextureCoords(0) ? mesh->mTextureCoords[0][i] : ZeroVector;

			positions.insert(positions.end(), { pos.x, pos.y, pos.z });

			textures.insert(textures.end(), { tex.x, tex.y });

			normals.insert(normals.end(), { pos.x, pos.y, pos.z });

		}

		//create index buffer
		for (int i = 0; i < mesh->mNumFaces; ++i) {
			const aiFace& face = mesh->mFaces[i];

			if (face.mNumIndices != 3) {
				throw;
			}

			indices.insert(indices.end(), { indexOffset + face.mIndices[0], indexOffset + face.mIndices[1], indexOffset + face.mIndices[2] });
		}

		mesh_widths.emplace_back(mesh->mNumFaces);
		indexOffset += mesh->mNumFaces;
	}
	/* ---------------------------------- GENERATE TEXTURES ---------------------------------- */
	//Texture* textures = new Texture[scene->mNumTextures];
	/* ---------------------------------- POPULATE BUFFERS ---------------------------------- */

	GLuint mBuffers[4];

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, mBuffers[POSITION_LOCATION]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions[0]) * positions.size(), &positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(POSITION_LOCATION);
	glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, mBuffers[TEXTURE_LOCATION]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(textures[0]) * textures.size(), &textures[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(TEXTURE_LOCATION);
	glVertexAttribPointer(TEXTURE_LOCATION, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, mBuffers[NORMAL_LOCATION]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normals[0]) * normals.size(), &normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(NORMAL_LOCATION);
	glVertexAttribPointer(NORMAL_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffers[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void Mesh::Render() {
	glBindVertexArray(VAO);

	int indexPosition = 0;

	for (int i = 0; i < mesh_widths.size(); ++i) {
		glDrawElementsBaseVertex(
			GL_TRIANGLES,
			mesh_widths[i],
			GL_UNSIGNED_INT,
			(void*)indexPosition,
			0
		);

		indexPosition += mesh_widths[i];
	}


}