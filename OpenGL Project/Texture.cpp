#include "pch.h"
#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

GLuint LoadTexture(const aiTexture* texture) {
	
	GLuint glTexture;

	//No data.
	if (texture->mWidth == 0) {
		
	}


	

	//Regular 2D file
	if (texture->mHeight != 0) {
		//glGenTextures(1, &glTexture);
		//glBindTexture(GL_TEXTURE_1D, glTexture);

		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->mWidth, texture->mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, &texture->pcData[0]);

		

		return 0;
	}
	//Embedded file
	else {
		stbi_uc* buff = (stbi_uc*)&texture->pcData[0];
		int len = texture->mWidth * sizeof(texture->pcData[0]);

		int width;
		int height;
		int bits_per_pixel;


		//if no components are requested then i guess bits per pixel is returned?
		stbi_uc* newBuff = stbi_load_from_memory(buff, len, &width, &height, &bits_per_pixel, 0);

		glGenTextures(1, &glTexture);
		glBindTexture(GL_TEXTURE_2D, glTexture);

		if (bits_per_pixel == 1) {

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, newBuff);

		} else if (bits_per_pixel == 2) {

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, width, height, 0, GL_RG, GL_UNSIGNED_BYTE, newBuff);

		} else if (bits_per_pixel == 3) {

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, newBuff);

		} else if (bits_per_pixel == 4) {

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, newBuff);

		} else {

			throw;

		}


		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
	}
	
	return glTexture;
}

GLuint LoadTexture(std::string path) {
	return 0;
}

