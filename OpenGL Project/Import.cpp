#include "pch.h"

#include "MemoryMapper.h"

#include "Packed_Skeleton.h"

static Texture* BufferToTexture(const Buffer& b, const std::function<void(void*, size_t)>& Read) {

	/*
	
	int width = 0;
	int height = 0;
	int bits_per_pixel = -1;
	void* data = nullptr;

	*/

	int width;
	Read(&width, sizeof(width));

	int height;
	Read(&height, sizeof(height));

	int bits_per_pixel;
	Read(&bits_per_pixel, sizeof(bits_per_pixel));

	size_t texBytes = ((size_t)width * (size_t)height * (size_t)bits_per_pixel);
	void* data = new uint8_t[texBytes]();
	Read(data, texBytes);


	return new Texture(width, height, bits_per_pixel, data);
}

static Material* BufferToMaterial(const Buffer& b, const std::function<void(void*, size_t)>& Read) {

	/*
	std::array<Texture*, numTexTypes> Textures;
	std::array<Color, numTexTypes> Colors;
	*/

	std::array<Texture*, numTexTypes> Textures;

	for (int i = 0; i < numTexTypes; ++i) {

		uint8_t texExists;
		Read(&texExists, sizeof(texExists));

		if (texExists) {
			Textures[i] = BufferToTexture(b, Read);
		}
		else {
			Textures[i] = nullptr;
		}

	}

	std::array<Color, numTexTypes> Colors{};

	Read(&Colors[0], sizeof(Color) * numTexTypes);

	return new Material(Textures, Colors);
}

static std::string BufferToString(const Buffer& b, const std::function<void(void*, size_t)>& Read) {

	
	
	/*size_t numChars;
	Read(&numChars, sizeof(numChars));

	char* str = new char[numChars]();

	Read(str, numChars);

	std::string content = std::string(str);
	throw;

	delete[] str;*/

	
	

	size_t numChars;
	Read(&numChars, sizeof(numChars));

	std::string content;
	content.resize(numChars);

	Read(&content[0], sizeof(std::string::value_type) * numChars);

	return content;

}

static Skeleton* BufferToSkeleton(const Buffer& b, const std::function<void(void*, size_t)>& Read) {

	size_t numBones;
	Read(&numBones, sizeof(numBones));

	std::vector<Packed_Bone> bones = std::vector<Packed_Bone>(numBones);
	for (int i = 0; i < numBones; ++i) {

		Read(&bones[i].localTransform, sizeof(bones[i].localTransform));

		Read(&bones[i].offset, sizeof(bones[i].offset));

		bones[i].name = BufferToString(b, Read);

		size_t numChildren;
		Read(&numChildren, sizeof(numChildren));

		if (numChildren != 0) {
			bones[i].childrenIndices.resize(numChildren);
			Read(&bones[i].childrenIndices[0], sizeof(bones[i].childrenIndices[0]) * numChildren);
		}
	}

	return new Skeleton(bones);

}

static PositionKeyFrame BufferToPositionKeyFrame(const Buffer& b, const std::function<void(void*, size_t)>& Read) {
	/*
	
	glm::vec3 position;
	double time;

	*/


	glm::vec3 position;
	Read(&position, sizeof(position));

	double time;
	Read(&time, sizeof(time));


	return PositionKeyFrame{ position, time };
}

static OrientationKeyFrame BufferToOrientationKeyFrame(const Buffer& b, const std::function<void(void*, size_t)>& Read) {
	/*

	glm::quat orientation;
	double time;

	*/


	glm::quat orientation;
	Read(&orientation, sizeof(orientation));

	double time;
	Read(&time, sizeof(time));


	return OrientationKeyFrame{ orientation, time };
}

static ScaleKeyFrame BufferToScaleKeyFrame(const Buffer& b, const std::function<void(void*, size_t)>& Read) {
	/*

	glm::vec3 scale;
	double time;

	*/


	glm::vec3 scale;
	Read(&scale, sizeof(scale));

	double time;
	Read(&time, sizeof(time));


	return ScaleKeyFrame{ scale, time };
}

inline static void BufferToKeyFrame(const Buffer& b, const std::function<void(void*, size_t)>& Read, Skeleton* skeleton, std::vector<KeyFrame>& vector) {
	/*
	
	Bone* bone;

	int numPositionFrames;
	PositionKeyFrame* positionFrames;

	int numOrientationFrames;
	OrientationKeyFrame* orientationFrames;

	int numScaleFrames;
	ScaleKeyFrame* scaleFrames;

	*/

	uint32_t boneIndex;
	Read(&boneIndex, sizeof(boneIndex));



	int32_t numPositionFrames;
	Read(&numPositionFrames, sizeof(numPositionFrames));

	PositionKeyFrame* positionFrames = new PositionKeyFrame[numPositionFrames]();

	for (int i = 0; i < numPositionFrames; ++i) {
		positionFrames[i] = BufferToPositionKeyFrame(b, Read);
	}



	int32_t numOrientationFrames;
	Read(&numOrientationFrames, sizeof(numOrientationFrames));

	OrientationKeyFrame* orientationFrames = new OrientationKeyFrame[numOrientationFrames]();

	for (int i = 0; i < numOrientationFrames; ++i) {
		orientationFrames[i] = BufferToOrientationKeyFrame(b, Read);
	}



	int32_t numScaleFrames;
	Read(&numScaleFrames, sizeof(numScaleFrames));

	ScaleKeyFrame* scaleFrames = new ScaleKeyFrame[numScaleFrames]();

	for (int i = 0; i < numScaleFrames; ++i) {
		scaleFrames[i] = BufferToScaleKeyFrame(b, Read);
	}

	vector.emplace_back(skeleton->GetBones()[boneIndex], numPositionFrames, positionFrames, numOrientationFrames, orientationFrames, numScaleFrames, scaleFrames);

	//return KeyFrame{ skeleton->GetBones()[boneIndex], numPositionFrames, positionFrames, numOrientationFrames, orientationFrames, numScaleFrames, scaleFrames };
}

static Animation* BufferToAnimation(const Buffer& b, const std::function<void(void*, size_t)>& Read, Skeleton* skeleton) {

	/*
	
	double duration;
	double duration_played;

	int ticksPerSecond;

	Skeleton* skeleton;

	std::vector<KeyFrame> KeyFrames;

	*/

	double duration;
	Read(&duration, sizeof(duration));

	double duration_played;
	Read(&duration_played, sizeof(duration_played));

	int ticksPerSecond;
	Read(&ticksPerSecond, sizeof(ticksPerSecond));

	size_t numKeyFrames;
	Read(&numKeyFrames, sizeof(numKeyFrames));

	/*
	std::vector<KeyFrame> keyframes = std::vector<KeyFrame>(numKeyFrames);
	for (int i = 0; i < keyframes.size(); ++i) {
		keyframes[i] = BufferToKeyFrame(b, Read, skeleton);
	}
	*/

	Animation* anim = new Animation{ duration, duration_played, ticksPerSecond, skeleton, std::vector<KeyFrame>() };

	/*
	std::vector<KeyFrame> keyframes;
	keyframes.reserve(numKeyFrames);
	for (int i = 0; i < numKeyFrames; ++i) {
		BufferToKeyFrame(b, Read, skeleton, keyframes);
	}
	*/

	anim->KeyFrames.reserve(numKeyFrames);
	for (int i = 0; i < numKeyFrames; ++i) {
		BufferToKeyFrame(b, Read, skeleton, anim->KeyFrames);
	}

	return anim;
}

ModelData* BufferToModel(Buffer& b) {

	/*
	
	std::vector<Vertex> vertices;

	std::vector<unsigned int> indices;

	std::vector<SubMesh> mesh_data;

	std::vector<Material*> Materials;

	Skeleton* skeleton;
	std::vector<Animation*> animations;

	glm::vec3 min;
	glm::vec3 max;

	*/

	int offset = 0;

	auto Read = [&](void* ptr, size_t num) -> void {
		b.Read(ptr, num, offset);
		offset += num;
	};


	bool is_skeletal;
	Read(&is_skeletal, sizeof(is_skeletal));


	//Vertices

	size_t numVertices;
	Read(&numVertices, sizeof(numVertices));

	std::vector<Vertex> vertices;
	std::vector<sVertex> sVertices;

	if (is_skeletal) {
		sVertices.resize(numVertices);
		Read(&sVertices[0], sizeof(sVertices[0]) * numVertices);
	}
	else {
		vertices.resize(numVertices);
		Read(&vertices[0], sizeof(vertices[0]) * numVertices);
	}



	//Indices

	size_t numIndices;
	Read(&numIndices, sizeof(numIndices));

	std::vector<unsigned int> indices = std::vector<unsigned int>(numIndices);
	Read(&indices[0], sizeof(indices[0]) * numIndices);



	//mesh_data

	size_t numMeshes;
	Read(&numMeshes, sizeof(numMeshes));

	std::vector<SubMesh> meshes = std::vector<SubMesh>(numMeshes);
	Read(&meshes[0], sizeof(meshes[0]) * numMeshes);


	//Material

	size_t numMaterials;
	Read(&numMaterials, sizeof(numMaterials));

	std::vector<Material*> materials = std::vector<Material*>(numMaterials);
	for (int i = 0; i < numMaterials; ++i) {
		materials[i] = BufferToMaterial(b, Read);
	}






	Skeleton* skeleton = nullptr;

	std::vector<Animation*> animations;

	if (is_skeletal) {
		
		//Skeleton
		skeleton = BufferToSkeleton(b, Read);


		//Animations
		size_t numAnimations;
		Read(&numAnimations, sizeof(numAnimations));

		animations.resize(numAnimations);

		for (int i = 0; i < animations.size(); ++i) {
			animations[i] = BufferToAnimation(b, Read, skeleton);
		}

	}




	


	//Min/Max

	glm::vec3 min;
	Read(&min, sizeof(min));

	glm::vec3 max;
	Read(&max, sizeof(max));






	if (is_skeletal) {
		return new ModelData{ sVertices, indices, meshes, materials, skeleton, animations, min, max };
	}
	else {
		return new ModelData{ vertices, indices, meshes, materials, skeleton, animations, min, max };
	}
}