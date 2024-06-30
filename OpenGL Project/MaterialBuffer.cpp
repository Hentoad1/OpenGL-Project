#include "pch.h"

#include "MaterialBuffer.h"


std::array<GLint, numTexTypes> MaterialBuffer::GetTextures() const {
	return textures;
}

std::array<GLint, numTexTypes> MaterialBuffer::GetTexturesExist() const {
	return loaded;
}

std::array<Color, numTexTypes> MaterialBuffer::GetColors() const {
	return MaterialColors;
}

static constexpr GLenum Type = GL_TEXTURE_2D;

MaterialBuffer::MaterialBuffer(const Material* mat) : MaterialColors(mat->GetColors()) {
	const std::array<Texture*, numTexTypes>& texturedata = mat->GetTextures();

	textures = std::array<GLint, numTexTypes>();
	loaded = std::array<GLint, numTexTypes>();

	for (int i = 0; i < texturedata.size(); ++i) {
		
		const Texture* tex = texturedata[i];

		if (tex == nullptr) {
			//texture is empty / does not exist.

			loaded[i] = false;
			continue;
		}

		if (tex->width == 0 && tex->height == 0) {
			//means default constructor was used and is empty texture.

			loaded[i] = false;
			continue;
		}

		GLuint glTexture;

		glGenTextures(1, &glTexture);
		glBindTexture(Type, glTexture);

		//indicates that the image buffer is byte-aligned
		glPixelStorei(GL_PACK_ALIGNMENT, 1);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		if (tex->bits_per_pixel == 1) {

			glTexImage2D(Type, 0, GL_RED, tex->width, tex->height, 0, GL_RED, GL_UNSIGNED_BYTE, tex->data);

		}
		else if (tex->bits_per_pixel == 2) {

			glTexImage2D(Type, 0, GL_RG, tex->width, tex->height, 0, GL_RG, GL_UNSIGNED_BYTE, tex->data);

		}
		else if (tex->bits_per_pixel == 3) {

			glTexImage2D(Type, 0, GL_RGB, tex->width, tex->height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex->data);

		}
		else if (tex->bits_per_pixel == 4) {

			glTexImage2D(Type, 0, GL_RGBA, tex->width, tex->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex->data);

		}
		else {

			throw;

		}


		glTexParameteri(Type, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(Type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(Type, GL_TEXTURE_BASE_LEVEL, 0);


		/*
		Repeats the texture.
		https://gamedev.stackexchange.com/questions/62548/what-does-changing-gl-texture-wrap-s-t-do
		This forum shows the differnce in these params.
		*/

		glTexParameteri(Type, GL_TEXTURE_WRAP_S, GL_REPEAT); //maybe mirrored repeat?
		glTexParameteri(Type, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glGenerateMipmap(Type);

		//glBindTexture(Type, 0);
		
		textures[i] = glTexture;
		loaded[i] = true;
	}
}

MaterialBuffer::~MaterialBuffer() {
	for (int i = 0; i < numTexTypes; ++i) {
		if (loaded[i]) {
			glDeleteTextures(1, (GLuint*) &textures[i]);
		}
	}
}