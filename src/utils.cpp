#include <learnopengl/utils.h>

uint32_t loadTexture(const char *path, GLint repeatMode, bool gamma) {
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
		if (repeatMode != -1) {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, repeatMode);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, repeatMode);
		} else {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
		}
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	} else {
		std::cout << "Failed to load texture" << path << std::endl;
	}
	stbi_image_free(data);
	return textureId;
}

uint32_t textureFromFile(const char *filename, const std::string &directory) {
	std::string path = directory + '/' + filename;
	return loadTexture(path.c_str(), GL_REPEAT);
}

uint32_t loadCubeMap(std::vector<std::string> faces) {
	uint32_t textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
	GLenum format;
	int32_t width, height, channels;
	for (size_t i = 0; i < faces.size(); i++) {
		std::string path = faces[i];
		stbi_uc *data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		if (channels == 1)
			format = GL_RED;
		else if (channels == 3)
			format = GL_RGB;
		else if (channels == 4)
			format = GL_RGBA;

		if (data) {
			// 根据图片创建纹理
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		} else {
			std::cout << "Failed to load texture" << path << std::endl;
		}
		stbi_image_free(data);
	}
	// 环绕和过滤
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	return textureId;
}