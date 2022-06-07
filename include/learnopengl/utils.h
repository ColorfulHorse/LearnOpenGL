#ifndef UTILS_H
#define UTILS_H

#include <glad/glad.h>
#include "stb_image.h"
#include <cstdint>
#include <iostream>
#include <vector>

uint32_t loadTexture(const char *path, GLint repeatMode = -1);

uint32_t textureFromFile(const char *filename, const std::string &directory);

uint32_t loadCubeMap(std::vector<std::string> faces);

template <typename T1, typename T2>
struct is_same_type {
	operator bool() {
		return false;
	}
};

template <typename T1>
struct is_same_type<T1, T1> {
	operator bool() {
		return true;
	}
};
#endif