
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
		
		//required: only want triangles
		aiProcess_Triangulate |

		//required: want to re-use indices
		aiProcess_JoinIdenticalVertices |

		//reuqired: creates sub-meshes
		aiProcess_SortByPType |

		//can be useful later for lighting
		aiProcess_CalcTangentSpace |

		//takes a lot of import time, but improves optimizations; useful though when memory mapping.
		//aiProcess_ImproveCacheLocality |

		//more optimizations
		aiProcess_OptimizeMeshes |
		aiProcess_OptimizeGraph |

		//infacing normals will be flipped.
		aiProcess_FixInfacingNormals |

		//useful for fixing errors, removing bad normals and such
		aiProcess_FindInvalidData | 

		//Smooth normal will be generated on top of any bad normals
		aiProcess_GenSmoothNormals
		
	);

	if (nullptr == scene) {
		std::cout << importer.GetErrorString() << std::endl;
		throw;
	}

	/* --------------------------------- CREATE BUFFER DATA ---------------------------------- */

	std::vector<float> positions;
	std::vector<float> textures;
	std::vector<float> normals;

	std::vector<unsigned int> indices;
	
	const aiVector3D ZeroVector(0.0f, 0.0f, 0.0f);


	mesh_data = std::vector<MeshMeta>();

	unsigned int currentIndex = 0;

	

	for (unsigned int meshIndex = 0; meshIndex < scene->mNumMeshes; ++meshIndex) {
		const aiMesh* mesh = scene->mMeshes[meshIndex];

		glm::vec3 max = glm::vec3(-FLT_MAX);
		glm::vec3 min = glm::vec3(FLT_MAX);

		std::cout << meshIndex << std::endl;
		std::cout << scene->mNumMeshes << std::endl;

		//create buffers
		for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
			const aiVector3D& pos = mesh->mVertices[i];
			const aiVector3D& normal = mesh->mNormals[i];
			const aiVector3D& tex = mesh->HasTextureCoords(0) ? mesh->mTextureCoords[0][i] : ZeroVector;

			positions.insert(positions.end(), { pos.x, pos.y, pos.z });

			textures.insert(textures.end(), { tex.x, tex.y });

			normals.insert(normals.end(), { normal.x, normal.y, normal.z });

			min.x = std::min(min.x, pos.x);
			min.y = std::min(min.y, pos.y);
			min.z = std::min(min.z, pos.z);

			max.x = std::max(max.x, pos.x);
			max.y = std::max(max.y, pos.y);
			max.z = std::max(max.z, pos.z);
		}

		//create index buffer
		for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
			const aiFace& face = mesh->mFaces[i];

			if (face.mNumIndices != 3) {
				throw;
			}

			indices.insert(indices.end(), { face.mIndices[0], face.mIndices[1], face.mIndices[2] });
		}
		
		const unsigned int mNumIndices = mesh->mNumFaces * 3;

		mesh_data.emplace_back(MeshMeta(currentIndex, mNumIndices, min, max));

		currentIndex += mNumIndices;
	}

	/* ----------------------------------- IMPORT TEXTURES ----------------------------------- */
	
	//Texture* textures = new Texture[scene->mNumTextures];
	
	/* ----------------------------- INITIALIZE CLASS VARIABLES ------------------------------ */

	this->max = glm::vec3(-FLT_MAX);
	this->min = glm::vec3(FLT_MAX);

	for (int i = 0; i < mesh_data.size(); ++i) {
		std::cout << "min: " << glm::to_string(mesh_data[i].min) << std::endl;
		std::cout << "max: " << glm::to_string(mesh_data[i].max) << std::endl;

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

	for (const MeshMeta& meta : mesh_data) {
		glDrawElementsBaseVertex(
			GL_LINES,
			meta.indexCount,
			GL_UNSIGNED_INT,
			0,
			meta.baseIndex
		);
	}


	glBindVertexArray(0);
}

Mesh::MeshMeta::MeshMeta(unsigned int base, unsigned int count, glm::vec3 _min, glm::vec3 _max) {
	
	baseIndex = base;
	indexCount = count;
	
	min = _min;
	max = _max;

	center = (min + max) * glm::vec3(0.5f);

}