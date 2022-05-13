#ifndef UTILS_H
#define UTILS_H

#include <glad/glad.h>
#include "stb_image.h"
#include <cstdint>
#include <iostream>

uint32_t loadTexture(const char *path);

uint32_t textureFromFile(const char *filename, const std::string &directory);

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