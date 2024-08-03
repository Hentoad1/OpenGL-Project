#include "pch.h"

//#include "MemoryMapper.h"

#include "Basic_Model.h"
#include "Skeletal_Model.h"

//#include "ModelData.h"

static void AppendStringToBuffer(Buffer& b, std::string& str) {
	
	//this is virtually unreadable but its really funny to me so it stays that way.
	
	size_t size = str.size();
	size_t size_size = sizeof(size);
	uint8_t* size_buffer = static_cast<uint8_t*>(static_cast<void*>(&size));

	b.Append(size_buffer, size_size);

	size_t data_size = str.size() * sizeof(std::string::value_type);
	uint8_t* data_buffer = static_cast<uint8_t*>(static_cast<void*>(&str[0]));

	b.Append(data_buffer, data_size);
}

static void AppendTextureToBuffer(Buffer& b, Texture* tex) {

	uint8_t* width = static_cast<uint8_t*>(static_cast<void*>(&tex->width));
	size_t width_size = sizeof(tex->width);

	b.Append(width, width_size);


	uint8_t* height = static_cast<uint8_t*>(static_cast<void*>(&tex->height));
	size_t height_size = sizeof(tex->width);

	b.Append(height, height_size);


	uint8_t* bpp = static_cast<uint8_t*>(static_cast<void*>(&tex->bits_per_pixel));
	size_t bpp_size = sizeof(tex->width);

	b.Append(bpp, bpp_size);

	uint8_t* img_data = static_cast<uint8_t*>(tex->data);
	size_t img_data_size = (size_t)((size_t)tex->width * (size_t)tex->height * (size_t)tex->bits_per_pixel);

	b.Append(img_data, img_data_size);
}

static void AppendMaterialToBuffer(Buffer& b, Material* mat) {

	std::array<Color, numTexTypes> colors = mat->GetColors();
	std::array<Texture*, numTexTypes> textures = mat->GetTextures();

	for (int i = 0; i < textures.size(); ++i){
		
		/*
		nullptrs would just be skipped but
		the case of textures [nullptr, nullptr, texture] and [texture, nullptr, nullptr]
		would be the same. 
		
		So a byte will be dedicated to indicating where a texture exists in the specific index.
		*/
		
		uint8_t texExists = (textures[i] != nullptr);

		b.Append(texExists);

		if (texExists) {
			AppendTextureToBuffer(b, textures[i]);
		}
	}

	size_t num_color_bytes = sizeof(Color) * colors.size();
	uint8_t* color_bytes = static_cast<uint8_t*>(static_cast<void*>(&colors[0]));

	b.Append(color_bytes, num_color_bytes);
}

static void AppendBoneToBuffer(Buffer& b, Bone* bone) {

	//transform
	size_t transform_size = sizeof(bone->localTransform);
	uint8_t* transform_buffer = static_cast<uint8_t*>(static_cast<void*>(&bone->localTransform));

	b.Append(transform_buffer, transform_size);


	//offset
	size_t offset_size = sizeof(bone->offset);
	uint8_t* offset_buffer = static_cast<uint8_t*>(static_cast<void*>(&bone->offset));

	b.Append(offset_buffer, offset_size);



	//name
	AppendStringToBuffer(b, bone->name);



	//children
	size_t children_num = bone->children.size();
	size_t children_num_size = sizeof(children_num);
	uint8_t* children_num_buffer = static_cast<uint8_t*>(static_cast<void*>(&children_num));

	b.Append(children_num_buffer, children_num_size);

	for (int i = 0; i < bone->children.size(); ++i) {
		int childIndex = bone->children[i]->index;

		size_t child_index_size = sizeof(childIndex);
		uint8_t* child_index_buffer = static_cast<uint8_t*>(static_cast<void*>(&childIndex));

		b.Append(child_index_buffer, child_index_size);
	}
}

static void AppendSkeletonToBuffer(Buffer& b, Skeleton* s) {

	size_t num_bones = s->GetBones().size();
	size_t num_bones_size = sizeof(num_bones);
	uint8_t* num_bones_buffer = static_cast<uint8_t*>(static_cast<void*>(&num_bones));
	
	b.Append(num_bones_buffer, num_bones_size);

	const std::vector<Bone*> bones = s->GetBones();

	for (int i = 0; i < bones.size(); ++i) {
		Bone* bone = bones[i];

		AppendBoneToBuffer(b, bone);
	}
}

static void AppendKeyFrameToBuffer(Buffer& b, KeyFrame& kf) {

	/*
	Bone* bone;

	int numPositionFrames;
	PositionKeyFrame* positionFrames;

	int numOrientationFrames;
	OrientationKeyFrame* orientationFrames;

	int numScaleFrames;
	ScaleKeyFrame* scaleFrames;
	*/

	/*
	struct PositionKeyFrame {
		glm::vec3 position;
		double time;
	};

	struct OrientationKeyFrame {
		glm::quat orientation;
		double time;
	};

	struct ScaleKeyFrame {
		glm::vec3 scale;
		double time;
	};
	*/

	uint32_t boneIndex = kf.bone->index;
	size_t bone_index_size = sizeof(boneIndex);
	uint8_t* bone_index_buffer = static_cast<uint8_t*>(static_cast<void*>(&boneIndex));
	
	b.Append(bone_index_buffer, bone_index_size);

	//position frames

	size_t num_pos_size = sizeof(kf.numPositionFrames);
	uint8_t* num_pos_buffer = static_cast<uint8_t*>(static_cast<void*>(&kf.numPositionFrames));

	b.Append(num_pos_buffer, num_pos_size);

	for (int i = 0; i < kf.numPositionFrames; ++i) {
		PositionKeyFrame& keyframe = kf.positionFrames[i];
		
		size_t pos_size = sizeof(keyframe.position);
		uint8_t* pos_buffer = static_cast<uint8_t*>(static_cast<void*>(&keyframe.position));

		b.Append(pos_buffer, pos_size);

		size_t time_size = sizeof(keyframe.time);
		uint8_t* time_buffer = static_cast<uint8_t*>(static_cast<void*>(&keyframe.time));

		b.Append(time_buffer, time_size);
	}


	//orientation frames

	size_t num_ori_size = sizeof(kf.numOrientationFrames);
	uint8_t* num_ori_buffer = static_cast<uint8_t*>(static_cast<void*>(&kf.numOrientationFrames));

	b.Append(num_ori_buffer, num_ori_size);

	for (int i = 0; i < kf.numOrientationFrames; ++i) {
		OrientationKeyFrame& keyframe = kf.orientationFrames[i];

		size_t ori_size = sizeof(keyframe.orientation);
		uint8_t* ori_buffer = static_cast<uint8_t*>(static_cast<void*>(&keyframe.orientation));

		b.Append(ori_buffer, ori_size);

		size_t time_size = sizeof(keyframe.time);
		uint8_t* time_buffer = static_cast<uint8_t*>(static_cast<void*>(&keyframe.time));

		b.Append(time_buffer, time_size);
	}



	//scale frames

	size_t num_scale_size = sizeof(kf.numScaleFrames);
	uint8_t* num_scale_buffer = static_cast<uint8_t*>(static_cast<void*>(&kf.numScaleFrames));

	b.Append(num_scale_buffer, num_scale_size);

	for (int i = 0; i < kf.numScaleFrames; ++i) {
		ScaleKeyFrame& keyframe = kf.scaleFrames[i];

		size_t scale_size = sizeof(keyframe.scale);
		uint8_t* scale_buffer = static_cast<uint8_t*>(static_cast<void*>(&keyframe.scale));

		b.Append(scale_buffer, scale_size);

		size_t time_size = sizeof(keyframe.time);
		uint8_t* time_buffer = static_cast<uint8_t*>(static_cast<void*>(&keyframe.time));

		b.Append(time_buffer, time_size);
	}
}

static void AppendAnimationToBuffer(Buffer& b, Animation* anim) {

	/*
	
	double duration;
	double duration_played;

	int ticksPerSecond;
	
	Skeleton* skeleton;

	std::vector<KeyFrame> KeyFrames;

	*/


	//Here skeleton is just the skeleton used in the model. pointer can be added when unpacking.

	
	//duration
	size_t duration_size = sizeof(anim->duration);
	uint8_t* duration_buffer = static_cast<uint8_t*>(static_cast<void*>(&anim->duration));

	b.Append(duration_buffer, duration_size);


	//duration_played
	size_t duration_played_size = sizeof(anim->duration_played);
	uint8_t* duration_played_buffer = static_cast<uint8_t*>(static_cast<void*>(&anim->duration_played));

	b.Append(duration_played_buffer, duration_played_size);


	//ticks_per_second
	size_t tps_size = sizeof(anim->ticksPerSecond);
	uint8_t* tps_buffer = static_cast<uint8_t*>(static_cast<void*>(&anim->ticksPerSecond));

	b.Append(tps_buffer, tps_size);


	//number of keyframes
	size_t num_KeyFrames = anim->KeyFrames.size();
	size_t num_kf_size = sizeof(num_KeyFrames);
	uint8_t* num_kf_buffer = static_cast<uint8_t*>(static_cast<void*>(&num_KeyFrames));

	b.Append(num_kf_buffer, num_kf_size);

	for (int i = 0; i < anim->KeyFrames.size(); ++i) {
		AppendKeyFrameToBuffer(b, anim->KeyFrames[i]);
	}
}

static void AppendStaticBoundingBoxToBuffer(Buffer& b, StaticBoundingBox* sbb) {
	b.Append(sbb->vertices);
	b.Append(sbb->indices);
	b.Append(sbb->normals);


	size_t min_size = sizeof(sbb->min);
	uint8_t* min_buffer = static_cast<uint8_t*>(static_cast<void*>(&sbb->min));
	b.Append(min_buffer, min_size);


	size_t max_size = sizeof(sbb->max);
	uint8_t* max_buffer = static_cast<uint8_t*>(static_cast<void*>(&sbb->max));
	b.Append(max_buffer, max_size);


	size_t center_size = sizeof(sbb->center);
	uint8_t* center_buffer = static_cast<uint8_t*>(static_cast<void*>(&sbb->normals));
	b.Append(center_buffer, center_size);


	size_t type_size = sizeof(sbb->type);
	uint8_t* type_buffer = static_cast<uint8_t*>(static_cast<void*>(&sbb->type));
	b.Append(type_buffer, type_size);

}

void Basic_Model::AddToBuffer(Buffer& b) const {

	Model_Type model_type = this->GetModelType();
	uint8_t* model_type_buffer = static_cast<uint8_t*>(static_cast<void*>(&model_type));
	size_t model_type_size = sizeof(model_type);

	b.Append(model_type_buffer, model_type_size);

	b.Append(vertices);

	b.Append(indices);

	b.Append(mesh_data);

	size_t num_materials = Materials.size();
	uint8_t* num_materials_buffer = static_cast<uint8_t*>(static_cast<void*>(&num_materials));
	size_t num_material_size = sizeof(num_materials);

	b.Append(num_materials_buffer, num_material_size);

	for (int i = 0; i < Materials.size(); ++i) {
		AppendMaterialToBuffer(b, Materials[i]);
	}

	AppendStaticBoundingBoxToBuffer(b, sbb);

}

void Skeletal_Model::AddToBuffer(Buffer& b) const {

	Model_Type model_type = GetModelType();
	uint8_t* model_type_buffer = static_cast<uint8_t*>(static_cast<void*>(&model_type));
	size_t model_type_size = sizeof(model_type);

	b.Append(model_type_buffer, model_type_size);

	b.Append(vertices);

	b.Append(indices);

	b.Append(mesh_data);

	size_t num_materials = Materials.size();
	uint8_t* num_materials_buffer = static_cast<uint8_t*>(static_cast<void*>(&num_materials));
	size_t num_material_size = sizeof(num_materials);

	b.Append(num_materials_buffer, num_material_size);

	for (int i = 0; i < Materials.size(); ++i) {
		AppendMaterialToBuffer(b, Materials[i]);
	}

	// ---------- Skeleton ----------
	AppendSkeletonToBuffer(b, skeleton);

	// ---------- Animations ---------- 

	size_t num_animations = animations.size();
	uint8_t* num_animations_buffer = static_cast<uint8_t*>(static_cast<void*>(&num_animations));
	size_t num_animations_size = sizeof(num_animations);

	b.Append(num_animations_buffer, num_animations_size);

	for (int i = 0; i < animations.size(); ++i) {
		AppendAnimationToBuffer(b, animations[i]);
	}

	AppendStaticBoundingBoxToBuffer(b, sbb);

}



/*Buffer ModelToBuffer(ModelData* m) {
	Buffer buf;

	bool is_skeletal = (m->skeleton != nullptr);
	uint8_t* is_skeletal_buffer = static_cast<uint8_t*>(static_cast<void*>(&is_skeletal));
	size_t is_skeletal_size = sizeof(is_skeletal);

	buf.Append(is_skeletal_buffer, is_skeletal_size);

	if (m->vType == VERTEX_TYPE_SKELETAL) {
		auto& z = *static_cast<std::vector<sVertex>*>(m->vertices);
		buf.Append(*static_cast<std::vector<sVertex>*>(m->vertices));
	}
	else {
		auto& z = *static_cast<std::vector<Vertex>*>(m->vertices);
		buf.Append(*static_cast<std::vector<Vertex>*>(m->vertices));
	}


	buf.Append(m->indices);

	buf.Append(m->mesh_data);

	// ---------- Materials ----------

	size_t num_materials = m->Materials.size();
	uint8_t* num_materials_buffer = static_cast<uint8_t*>(static_cast<void*>(&num_materials));
	size_t num_material_size = sizeof(num_materials);

	buf.Append(num_materials_buffer, num_material_size);

	for (int i = 0; i < m->Materials.size(); ++i) {
		AppendMaterialToBuffer(buf, m->Materials[i]);
	}


	if (is_skeletal) {

		// ---------- Skeleton ----------
		AppendSkeletonToBuffer(buf, m->skeleton);

		// ---------- Animations ---------- 

		size_t num_animations = m->animations.size();
		uint8_t* num_animations_buffer = static_cast<uint8_t*>(static_cast<void*>(&num_animations));
		size_t num_animations_size = sizeof(num_animations);

		buf.Append(num_animations_buffer, num_animations_size);

		for (int i = 0; i < m->animations.size(); ++i) {
			AppendAnimationToBuffer(buf, m->animations[i]);
		}
	}


	// ---------- BoundingBox ---------- 
	
	AppendStaticBoundingBoxToBuffer(buf, m->sbb);
	
	return buf;
}*/