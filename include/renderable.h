#ifndef RENDERABLE_H
#define RENDERABLE_H
#include <cstdint>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader.h"
class Renderable {
public:
	virtual void onCreate() = 0;
	virtual void onProcessInput(GLFWwindow *window) {
	}
	virtual void onRender() = 0;
	virtual void onDestroy() = 0;

protected:
	uint32_t VBO = 0, VAO = 0, EBO = 0;
	uint32_t shaderProgram = 0;
	Shader shader;
};
#endif
