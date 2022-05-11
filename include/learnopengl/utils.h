#ifndef UTILS_H
#define UTILS_H

#include "stb_image.h"
#include <cstdint>
#include <glad/glad.h>
#include <iostream>

uint32_t loadTexture(const char *path) {
	uint32_t textureId;
	glGenTextures(1, &textureId);
	int32_t width, height, channels;
	stbi_uc *data = stbi_load(path, &width, &height, &channels, 0);
	GLenum format;
	if (channels == 1)
		format = GL_RED;
	else if (channels == 3)
		format = GL_RGB;
	else if (channels == 4)
		format = GL_RGBA;

	if (data) {
		glBindTexture(GL_TEXTURE_2D, textureId);
		// 根据图片创建纹理
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		// 创建多级渐远纹理
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	} else {
		std::cout << "Failed to load texture" << path << std::endl;
	}
	stbi_image_free(data);
	return textureId;
}

uint32_t textureFromFile(const char *filename, const string &directory) {
	string path = string(filename);
	path = directory + '/' + filename;
	return loadTexture(path);
}

#endif