#include "pch.h"
#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

static constexpr GLenum Type = GL_TEXTURE_2D;

static GLuint AttachTexture(const stbi_uc* buff, const int width, const int height, const int bits_per_pixel) {
	GLuint glTexture;
	
	glGenTextures(1, &glTexture);
	glBindTexture(Type, glTexture);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	if (bits_per_pixel == 1) {

		glTexImage2D(Type, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, buff);

	}
	else if (bits_per_pixel == 2) {

		glTexImage2D(Type, 0, GL_RG, width, height, 0, GL_RG, GL_UNSIGNED_BYTE, buff);

	}
	else if (bits_per_pixel == 3) {

		glTexImage2D(Type, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, buff);

	}
	else if (bits_per_pixel == 4) {

		glTexImage2D(Type, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buff);

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

	glBindTexture(Type, 0);

	return glTexture;
}

GLuint LoadTexture(const aiTexture* texture) {

	//Regular 2D file
	if (texture->mHeight != 0) {
		//glGenTextures(1, &glTexture);
		//glBindTexture(GL_TEXTURE_1D, glTexture);

		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->mWidth, texture->mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, &texture->pcData[0]);

		std::cout << "we are getting textures here";
		throw;

		return 0;
	}
	//Embedded file
	else {
		stbi_uc* compressedBuff = (stbi_uc*)&texture->pcData[0];
		int len = texture->mWidth * sizeof(texture->pcData[0]);

		int width;
		int height;
		int bits_per_pixel;


		//if no components are requested then i guess bits per pixel is returned?
		stbi_uc* buff = stbi_load_from_memory(compressedBuff, len, &width, &height, &bits_per_pixel, 0);

		GLuint glTexture = AttachTexture(buff, width, height, bits_per_pixel);
		
		stbi_image_free(buff);

		return glTexture;
	}
}

GLuint LoadTexture(std::string path) {
	int width;
	int height;
	int bits_per_pixel;

	stbi_set_flip_vertically_on_load(1);

	//if no components are requested then i guess bits per pixel is returned?
	stbi_uc* buff = stbi_load(path.c_str(), &width, &height, &bits_per_pixel, 0);

	if (buff == nullptr) {
		std::cout << stbi_failure_reason();
		throw;
	}


	GLuint glTexture = AttachTexture(buff, width, height, bits_per_pixel);

	stbi_image_free(buff);

	return glTexture;
}

