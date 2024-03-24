
#include "pch.h"
#include "BasicMesh.h"

#include "Texture.h"
#include "Vertex.h"
#include "Path.h"
#include "Material.h"
#include "MeshMeta.h"

#define AI_CONFIG_PP_SBP_REMOVE aiPrimitiveType_POINTS|aiPrimitiveType_LINES


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
	delete[] MaterialBuffer;
}



void Mesh::Load(const std::string path) {

	/* ------------------------------------ IMPORT SCENE ------------------------------------- */

	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(path,

		//required: only want triangles
		aiProcess_Triangulate | \

		//required: want to re-use indices
		aiProcess_JoinIdenticalVertices | \

		//required: creates sub-meshes
		aiProcess_SortByPType | \
		
		//reiquired: otherwise meshes will not align properly
		aiProcess_PreTransformVertices | \

		//does fix current issue but is good nonetheless
		aiProcess_GenUVCoords | \

		//sometimes this fixes something, sometimes it doesn't
		//aiProcess_FlipUVs | \


		//can be useful later for lighting
		//aiProcess_CalcTangentSpace | \

		//find degenerates
		//aiProcess_FindDegenerates | \

		//takes a lot of import time, but improves optimizations; useful when memory mapping.
		//aiProcess_ImproveCacheLocality | \

		//removes unnecessary texures
		//aiProcess_RemoveRedundantMaterials | \

		//more optimizations
		//aiProcess_OptimizeMeshes | \
		//aiProcess_OptimizeGraph | \

		//infacing normals will be flipped.
		//aiProcess_FixInfacingNormals | \

		//useful for fixing errors, removing bad normals and such
		//aiProcess_FindInvalidData | \

		//Smooth normal will be generated on top of any bad normals
		//aiProcess_GenSmoothNormals | \
		
		0
	);

	if (nullptr == scene) {
		std::cout << importer.GetErrorString() << std::endl;
		throw;
	}

	/* --------------------------------- CREATE BUFFER DATA ---------------------------------- */

	auto& z = scene->mMetaData;

	for (int i = 0; i < z->mNumProperties; i++) {
		std::cout << "---------------" << std::endl;
		std::cout << z->mKeys[i].C_Str() << std::endl;
		std::cout << "(" << z->mValues[i].mType << ")" << z->mValues[i].mData << std::endl;
		std::cout << "---------------" << std::endl;
	}
	
	MeshMeta g = MeshMeta(scene->mMetaData);

	g.LogProperties();

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

	/* --------------------------------- CREATE BUFFER DATA ---------------------------------- */

	//std::vector<Vertex> vertices;

	//std::vector<unsigned int> indices;

	const aiVector3D ZeroVector(0.0f, 0.0f, 0.0f);


	mesh_data = std::vector<SubMesh>();

	unsigned int BaseVertex = 0;
	unsigned int BaseIndex = 0;

	for (unsigned int meshIndex = 0; meshIndex < scene->mNumMeshes; ++meshIndex) {
		const aiMesh* mesh = scene->mMeshes[meshIndex];

		glm::vec3 max = glm::vec3(-FLT_MAX);
		glm::vec3 min = glm::vec3(FLT_MAX);

		//create buffers
		for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
			const aiVector3D& pos = mesh->mVertices[i];
			const aiVector3D& normal = mesh->mNormals[i];
			const aiVector3D& tex = mesh->HasTextureCoords(0) ? mesh->mTextureCoords[0][i] : ZeroVector;


			vertices.emplace_back(pos, tex, normal);

			min.x = std::min(min.x, pos.x);
			min.y = std::min(min.y, pos.y);
			min.z = std::min(min.z, pos.z);

			max.x = std::max(max.x, pos.x);
			max.y = std::max(max.y, pos.y);
			max.z = std::max(max.z, pos.z);
		}

		unsigned int maxIndex = 0;

		//create index buffer
		for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
			const aiFace& face = mesh->mFaces[i];

			if (face.mNumIndices != 3) {
				throw;
			}

			maxIndex = std::max(maxIndex, face.mIndices[0]);
			maxIndex = std::max(maxIndex, face.mIndices[1]);
			maxIndex = std::max(maxIndex, face.mIndices[2]);

			indices.insert(indices.end(), { face.mIndices[0] , face.mIndices[1] , face.mIndices[2] });
		}

		const unsigned int mNumIndices = mesh->mNumFaces * 3;

		mesh_data.push_back(SubMesh(BaseVertex, BaseIndex, mNumIndices, mesh->mMaterialIndex, min, max));

		BaseIndex += mesh->mNumFaces * 3;
		BaseVertex += mesh->mNumVertices;
	}

	/* ----------------------------------- IMPORT TEXTURES ----------------------------------- */


	MaterialBuffer = new MatBuffer[scene->mNumMaterials];

	std::cout << "mNumMaterials: " << scene->mNumMaterials << std::endl;

	for (unsigned int i = 0; i < scene->mNumMaterials; i++) {
		aiMaterial* mat = scene->mMaterials[i];

		unsigned int TexCount = mat->GetTextureCount(aiTextureType_DIFFUSE);

		Material m = Material(mat);

		//really this for loop should only exist if im rendering multiple textures, but whatevre
		for (unsigned int j = 0; j < TexCount; j++) {
			aiString texturePath;

			//aiTextureMapping mappingType;
			//unsigned int uvIndex;
			//float blend;
			//aiTextureOp textureOP;
			//aiTextureMapMode mapMode[3];

			mat->Get(AI_MATKEY_TEXTURE(aiTextureType_DIFFUSE, 0), texturePath);

			//mat->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath, &mappingType, &uvIndex, &blend, &textureOP, mapMode);

			//std::cout << mappingType << std::endl;
			//std::cout << uvIndex << std::endl;
			//std::cout << blend << std::endl;
			//std::cout << (int)textureOP << std::endl;
			//std::cout << (int)mapMode[0] << ", " << (int)mapMode[1] << ", " << (int)mapMode[2] << ", " << std::endl;

			int z = aiTextureMapMode_Wrap | aiTextureMapMode_Clamp | aiTextureMapMode_Decal | aiTextureMapMode_Mirror;

			const aiTexture* texture = scene->GetEmbeddedTexture(texturePath.C_Str());

			if (texture == nullptr) {
				//regular texture, in external file

				std::cout << "normal" << std::endl;
				std::cout << texturePath.C_Str() << std::endl;

				std::string result = CalculatePath(path, texturePath.C_Str());


				std::cout << "path: " << path << std::endl;
				std::cout << "texpath: " << texturePath.C_Str() << std::endl;
				std::cout << "res: " << result << std::endl;


				/*std::string a = texturePath.C_Str();

				if (a.find("jpg") != -1) {
					continue;
				}*/


				GLuint glTexture = LoadTexture(result);

				if (!MaterialBuffer[i].Has(TextureType_DIFFUSE)) {
					std::cout << "setting texture: " << glTexture << std::endl;
					MaterialBuffer[i].Set(TextureType_DIFFUSE, glTexture);
				}
			}
			else {
				//embedded texture

				GLuint glTexture = LoadTexture(texture);

				if (!MaterialBuffer[i].Has(TextureType_DIFFUSE)) {
					std::cout << "setting texture: " << glTexture << std::endl;
					MaterialBuffer[i].Set(TextureType_DIFFUSE, glTexture);
				}

				std::cout << "embedded" << std::endl;
				std::cout << texturePath.C_Str() << std::endl;
			}
		}

		//aiTexture* tex = scene->mTextures[0];






	}

	/* ----------------------------- INITIALIZE CLASS VARIABLES ------------------------------ */

	this->max = glm::vec3(-FLT_MAX);
	this->min = glm::vec3(FLT_MAX);

	for (int i = 0; i < mesh_data.size(); ++i) {
		this->min.x = std::min(this->min.x, mesh_data[i].min.x);
		this->min.y = std::min(this->min.y, mesh_data[i].min.y);
		this->min.z = std::min(this->min.z, mesh_data[i].min.z);

		this->max.x = std::max(this->max.x, mesh_data[i].max.x);
		this->max.y = std::max(this->max.y, mesh_data[i].max.y);
		this->max.z = std::max(this->max.z, mesh_data[i].max.z);
	}

	this->center = (this->min + this->max) * glm::vec3(0.5f);

	shader = (ShaderProgram*)new BasicShader(mCamera, this->center);

	/* ---------------------------------- POPULATE BUFFERS ----------------------------------- */

	GLuint mBuffers[2];

	glGenVertexArrays(1, &VertexBuffer);
	glBindVertexArray(VertexBuffer);

	glGenBuffers(2, mBuffers);

	size_t Vertex_Size = sizeof(vertices[0]);

	glBindBuffer(GL_ARRAY_BUFFER, mBuffers[0]);
	glBufferData(GL_ARRAY_BUFFER, Vertex_Size * vertices.size(), &vertices[0], GL_STATIC_DRAW);
	
	glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, Vertex_Size, 0);
	glEnableVertexAttribArray(POSITION_LOCATION);

	glVertexAttribPointer(TEXTURE_LOCATION, 2, GL_FLOAT, GL_FALSE, Vertex_Size, (void*)12);
	glEnableVertexAttribArray(TEXTURE_LOCATION);

	glVertexAttribPointer(NORMAL_LOCATION, 3, GL_FLOAT, GL_FALSE, Vertex_Size, (void*)20);
	glEnableVertexAttribArray(NORMAL_LOCATION);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffers[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);

	std::cout << "vertices size: " << vertices.size() << std::endl;
	std::cout << "indices size: " << indices.size() << std::endl;
}

void Mesh::Render() {

	/* -------------------------------- USE AND UPDATE SHADER -------------------------------- */
	
	shader->Use();

	shader->Update();
	
	/* ----------------------------------- RENDER BUFFERS ------------------------------------ */
	
	glBindVertexArray(VertexBuffer);

	for (const SubMesh& sub : mesh_data) {

		GLuint tex = MaterialBuffer[sub.materialIndex].Get(TextureType_DIFFUSE);

		//std::cout << sub.materialIndex << std::endl;

		glBindTexture(GL_TEXTURE_2D, tex);

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

Mesh::SubMesh::SubMesh(unsigned int _BaseVertex, unsigned int _BaseIndex, unsigned int count, unsigned int matIndex, glm::vec3 _min, glm::vec3 _max) {
	
	BaseVertex = _BaseVertex;
	BaseIndex = _BaseIndex;

	indexCount = count;

	materialIndex = matIndex;

	min = _min;
	max = _max;

	center = (min + max) * glm::vec3(0.5f);

}



/*
NumIndices = mNumFaces * 3;
BaseVertex = NumVertices;
BaseIndex = NumIndices;

NumVertices += mNumVertices;
NumIndices += NumIndices;

glDrawElementsBaseVertex(
	GL_LINES,
	NumIndices,
	GL_UNSIGNED_INT,
	(void*)(sizeof(unsigned int) * BaseIndex),
	BaseVertex
);

*/