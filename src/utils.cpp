#include <learnopengl/utils.h>

uint32_t loadTexture(const char* path) {
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
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		// 创建多级渐远纹理
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		std::cout << "Failed to load " << path << std::endl;
	}
	stbi_image_free(data);
	return textureId;
}