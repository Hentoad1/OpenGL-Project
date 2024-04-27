
#include "pch.h"
#include "BasicMesh.h"

#include "Vertex.h"
#include "MeshMeta.h"

#define AI_CONFIG_PP_SBP_REMOVE aiPrimitiveType_POINTS|aiPrimitiveType_LINES

Mesh::Mesh(const BoundingBox& _bounds, Camera* cam) : bounds(_bounds), mCamera(cam), shader(nullptr), VertexBuffer(0xffffffff) {}

Mesh::Mesh(const std::string& path, Camera* mCam) : mCamera(mCam) {
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

	std::vector<Vertex> vertices;

	std::vector<unsigned int> indices;

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

	for (int i = 0; i < scene->mNumMaterials; i++) {
		Materials.emplace_back(scene, i, path);
	}

	/* ----------------------------- INITIALIZE CLASS VARIABLES ------------------------------ */

	glm::vec3 max = glm::vec3(-FLT_MAX);
	glm::vec3 min = glm::vec3(FLT_MAX);

	for (int i = 0; i < mesh_data.size(); ++i) {


		min.x = std::min(min.x, mesh_data[i].min.x);
		min.y = std::min(min.y, mesh_data[i].min.y);
		min.z = std::min(min.z, mesh_data[i].min.z);

		max.x = std::max(max.x, mesh_data[i].max.x);
		max.y = std::max(max.y, mesh_data[i].max.y);
		max.z = std::max(max.z, mesh_data[i].max.z);
	}

	bounds = BoundingBox(min, max);

#ifdef _DEBUG
	bounds.BindGL(mCamera);
#endif

	shader = (ShaderProgram*)new BasicShader(mCamera, bounds.Position());

#ifdef _DEBUG
	shader->SetPosition(bounds.Position());
#endif

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

Mesh::~Mesh() {
	delete shader;
}

Camera* Mesh::GetCamera() {
	return mCamera;
}

BoundingBox& Mesh::GetBoundingBox() {
	return bounds;
}

void Mesh::SetPosition(const glm::vec3& p) {
	bounds.SetPosition(p);
}

void Mesh::SetOrientation(const Orientation& o) {
	bounds.SetOrientation(o);
}

void Mesh::Render() {

#ifdef _DEBUG
	bounds.Render();
#endif

	if (VertexBuffer == 0xffffffff) {
		return;
	}

	/* -------------------------------- USE AND UPDATE SHADER -------------------------------- */

	shader->Use();

	shader->Update();
	
	/* ----------------------------------- RENDER BUFFERS ------------------------------------ */
	
	glBindVertexArray(VertexBuffer);

	for (const SubMesh& sub : mesh_data) {
		
		Material mat = Materials[sub.materialIndex];

		shader->setBools("TexturesExist", mat.GetTexturesExist(), numTexTypes);
		shader->setVec4s("Colors", mat.GetColors(), numTexTypes); //6 vec 3 = 18.

		GLint textureIndices[numTexTypes];
		int textureIndex = 0;
		for (int i = 0; i < numTexTypes; i++) {

			textureIndices[i] = textureIndex;

			if (mat.GetTexturesExist()[i]) {
				glActiveTexture(GL_TEXTURE0 + textureIndex++);
				glBindTexture(GL_TEXTURE_2D, mat.GetTextures()[i]);
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

//TODO: basicmesh should have no physics properties or collision.
bool Mesh::CollidesWith(const BoundingBox& other) {
	return bounds.CollidesWith(other);
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