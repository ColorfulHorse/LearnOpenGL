#include "stb_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <learnopengl/advanced/cullFace.h>
#include <learnopengl/shader.h>
#include <learnopengl/utils.h>

using namespace std;

void CullFace::init() {
	// 隐藏鼠标光标
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glEnable(GL_DEPTH_TEST);
	// 顶点坐标，这里的顶点是按照顺时针方向的
	// float vertices[] = {
	// 	// back face
	// 	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // bottom-left
	// 	0.5f, -0.5f, -0.5f, 1.0f, 0.0f,	 // bottom-right
	// 	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,	 // top-right
	// 	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,	 // top-right
	// 	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,	 // top-left
	// 	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // bottom-left
	// 	// front face
	// 	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom-left
	// 	0.5f, 0.5f, 0.5f, 1.0f, 1.0f,	// top-right
	// 	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,	// bottom-right
	// 	0.5f, 0.5f, 0.5f, 1.0f, 1.0f,	// top-right
	// 	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom-left
	// 	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,	// top-left
	// 	// left face
	// 	-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,	 // top-right
	// 	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // bottom-left
	// 	-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,	 // top-left
	// 	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // bottom-left
	// 	-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,	 // top-right
	// 	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,	 // bottom-right
	// 									 // right face
	// 	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,	 // top-left
	// 	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,	 // top-right
	// 	0.5f, -0.5f, -0.5f, 0.0f, 1.0f,	 // bottom-right
	// 	0.5f, -0.5f, -0.5f, 0.0f, 1.0f,	 // bottom-right
	// 	0.5f, -0.5f, 0.5f, 0.0f, 0.0f,	 // bottom-left
	// 	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,	 // top-left
	// 	// bottom face
	// 	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // top-right
	// 	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,	 // bottom-left
	// 	0.5f, -0.5f, -0.5f, 1.0f, 1.0f,	 // top-left
	// 	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,	 // bottom-left
	// 	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // top-right
	// 	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,	 // bottom-right
	// 	// top face
	// 	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, // top-left
	// 	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,	// top-right
	// 	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,	// bottom-right
	// 	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,	// bottom-right
	// 	-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,	// bottom-left
	// 	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f	// top-left
	// };

	float vertices[] = {
		// back face
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,	 // top-right
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f,	 // bottom-right
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // bottom-left
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // bottom-left
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,	 // top-left
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,	 // top-right
		// front face
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,	// bottom-right
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f,	// top-right
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom-left
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,	// top-left
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom-left
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f,	// top-right
		// left face
		-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,	 // top-left
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // bottom-left
		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,	 // top-right
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,	 // bottom-right
		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,	 // top-right
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // bottom-left
										 // right face
		0.5f, -0.5f, -0.5f, 0.0f, 1.0f,	 // bottom-right
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,	 // top-right
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,	 // top-left
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,	 // top-left
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f,	 // bottom-left
		0.5f, -0.5f, -0.5f, 0.0f, 1.0f,	 // bottom-right
		// bottom face
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f,	 // top-left
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,	 // bottom-left
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // top-right
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,	 // bottom-right
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // top-right
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,	 // bottom-left
		// top face
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,	// bottom-right
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,	// top-right
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, // top-left
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,	// top-left
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,	// bottom-left
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f	// bottom-right
	};

	shader = Shader(FileSystem::getPath("shaders/advanced/stencilTest/object.vs").c_str(), FileSystem::getPath("shaders/advanced/stencilTest/object.fs").c_str());
	normalShader = Shader(
		FileSystem::getPath("shaders/advanced/cullFace/normal.vs").c_str(), 
		FileSystem::getPath("shaders/advanced/cullFace/normal.fs").c_str(), 
		FileSystem::getPath("shaders/advanced/cullFace/normal.gs").c_str()
	);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
	glBindVertexArray(0);

	texture = loadTexture(FileSystem::getPath("assets/texture/marble.jpg").c_str());

	shader.use();
	shader.setInt("tex", 0);

	// glEnable(GL_CULL_FACE);

	// // 定义顺时针为正面，默认顶点逆时针顺序为正面 = CCW
	// glFrontFace(GL_CW);
	// // 剔除哪些面，默认剔除背面
	// glCullFace(GL_FRONT);
}

void CullFace::onCreate() {
	init();
}

void CullFace::onRender() {
    super::onRender();

	glm::mat4 model(1.0f);
	glm::mat4 projection(1.0f);
	projection = glm::perspective(glm::radians(camera.zoom), 800 * 1.0f / 600, 0.1f, 100.0f);

	// shader.use();
	// shader.setMat4("projection", projection);
	// shader.setMat4("view", camera.getViewMat());
	// shader.setMat4("model", model);

	// glBindVertexArray(VAO);
	// glActiveTexture(GL_TEXTURE0);
	// glBindTexture(GL_TEXTURE_2D, texture);
	// glDrawArrays(GL_TRIANGLES, 0, 36);

	normalShader.use();
	normalShader.setMat4("projection", projection);
	normalShader.setMat4("view", camera.getViewMat());
	normalShader.setMat4("model", model);

	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void CullFace::onDestroy() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	shader.release();
}
