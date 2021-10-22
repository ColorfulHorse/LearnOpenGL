#pragma once
#include "renderable.h"
#include <cstdint>

class HelloTexture : public Renderable {
public:
	uint32_t VBO = 0, VAO = 0, EBO = 0, texture = 0;
	uint32_t shaderProgram = 0;
	void initTexture();
	virtual void onCreate();
	virtual void onRender();
	virtual void onDestroy();
};