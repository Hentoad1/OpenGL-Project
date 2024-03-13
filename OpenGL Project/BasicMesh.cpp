
#include "pch.h"
#include "BasicMesh.h"


	/* ---------------------------------- COPY CONSTRUCTOR ----------------------------------- */

/*Mesh::Mesh(const Mesh& ref) {

}*/

	/* -------------------------------- DEFAULT CONSTRUCTORS --------------------------------- */

Mesh::Mesh(const std::string path, Camera* mCam) {
	mCamera = mCam;
	
	Load(path);
}

	/* ------------------------------------ DECONSTRUCTOR ------------------------------------ */

Mesh::~Mesh() {
	delete shader;
}



void Mesh::Load(const std::string path) {

	/* ------------------------------------ IMPORT SCENE ------------------------------------- */

	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(path,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType
	);

	if (nullptr == scene) {
		std::cout << importer.GetErrorString() << std::endl;
		throw;
	}

	/* ----------------------------- INITIALIZE CLASS VARIABLES ------------------------------ */

	shader = (ShaderProgram*)new BasicShader(mCamera, scene->mRootNode->mTransformation);

	/* --------------------------------- CREATE BUFFER DATA ---------------------------------- */

	/*std::vector<float> positions;
	std::vector<float> textures;
	std::vector<float> normals;

	std::vector<unsigned int> indices;*/
	
	const aiVector3D ZeroVector(0.0f, 0.0f, 0.0f);


	mesh_indices = std::vector<std::pair<unsigned int, unsigned int>>(scene->mNumMeshes);

	unsigned int currentIndex = 0;

	for (int meshIndex = 0; meshIndex < scene->mNumMeshes; ++meshIndex) {
		const aiMesh* mesh = scene->mMeshes[meshIndex];

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

			indices.insert(indices.end(), { face.mIndices[0], face.mIndices[1], face.mIndices[2] });
		}
		
		mesh_indices.emplace_back(std::pair(mesh->mNumFaces, currentIndex));

		currentIndex += mesh->mNumFaces;
	}

	/* ----------------------------------- IMPORT TEXTURES ----------------------------------- */
	
	//Texture* textures = new Texture[scene->mNumTextures];
	
	/* ---------------------------------- POPULATE BUFFERS ----------------------------------- */

	GLuint mBuffers[4];

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(4, mBuffers);

	glBindBuffer(GL_ARRAY_BUFFER, mBuffers[POSITION_LOCATION]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions[0]) * positions.size(), &positions[0], GL_STATIC_DRAW);
	glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(POSITION_LOCATION);

	glBindBuffer(GL_ARRAY_BUFFER, mBuffers[TEXTURE_LOCATION]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(textures[0]) * textures.size(), &textures[0], GL_STATIC_DRAW);
	glVertexAttribPointer(TEXTURE_LOCATION, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(TEXTURE_LOCATION);

	glBindBuffer(GL_ARRAY_BUFFER, mBuffers[NORMAL_LOCATION]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normals[0]) * normals.size(), &normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(NORMAL_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(NORMAL_LOCATION);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffers[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);


	std::cout << positions.size() << std::endl;
	std::cout << textures.size() << std::endl;
	std::cout << normals.size() << std::endl;
	std::cout << indices.size() << std::endl;
}

void Mesh::Render() {

	/* -------------------------------- USE AND UPDATE SHADER -------------------------------- */
	
	shader->Use();

	shader->Update();
	
	/* ----------------------------------- RENDER BUFFERS ------------------------------------ */
	
	glBindVertexArray(VAO);

	for (auto& [width, baseIndex] : mesh_indices) {
		glDrawElementsBaseVertex(
			GL_TRIANGLES,
			width,
			GL_UNSIGNED_INT,
			0,
			baseIndex
		);

		
		//checkGLErrors();
	}


	glBindVertexArray(0);
}