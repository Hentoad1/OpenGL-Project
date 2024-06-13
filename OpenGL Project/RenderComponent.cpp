
#include "pch.h"
#include "RenderComponent.h"

#include "Shader.h"

RenderComponent::RenderComponent(ComponentData* _cData, const ComponentMeta* cMeta, const ModelBuffers* _mData) : cData(_cData), mData(_mData) {
	if (cMeta->has(MESH_SHADERTYPE_BASIC)) {
		shader = (ShaderProgram*)(new BasicShader(cData->camera, mData->center()));
	}
}

RenderComponent::~RenderComponent() {

}

void RenderComponent::Render() {

	/* -------------------------------- USE AND UPDATE SHADER -------------------------------- */

	//shader->SetPosition(cData->bounds.Center());
	
	shader->SetPosition(glm::mat4(1.0f));

	shader->Use();

	shader->Update();

	/* ----------------------------------- RENDER BUFFERS ------------------------------------ */

	glBindVertexArray(mData->VAO);
	
	for (const SubMesh& sub : mData->mesh_data) {

		const MaterialBuffer* mat = mData->MBO[sub.materialIndex];

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