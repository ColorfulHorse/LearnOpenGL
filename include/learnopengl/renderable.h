#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdint>
#include <iostream>
#include <learnopengl/filesystem.h>
#include <learnopengl/shader.h>
class Renderable {
public:
	virtual void onCreate() = 0;
	virtual void onRender() = 0;
	virtual void onDestroy() = 0;

	Renderable(GLFWwindow *win) :
		window(win) {
	}
	virtual ~Renderable() {
		window = nullptr;
	}

protected:
	uint32_t VBO = 0, VAO = 0, EBO = 0;
	uint32_t shaderProgram = 0;
	Shader shader;
	GLFWwindow *window = nullptr;
};
#endif
