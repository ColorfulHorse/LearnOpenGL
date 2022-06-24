﻿#include <glad/glad.h>
#include "stb_image.h"
#include <GLFW/glfw3.h>
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <learnopengl/advanced/galaxy.h>
#include <learnopengl/shader.h>
#include <learnopengl/utils.h>
#include <random>

using namespace std;

void Galaxy::init() {
	// 隐藏鼠标光标
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glEnable(GL_DEPTH_TEST);

	float quadVertices[] = {
		// 位置          // 颜色
		-0.05f, 0.05f, 1.0f, 0.0f, 0.0f,
		0.05f, -0.05f, 0.0f, 1.0f, 0.0f,
		-0.05f, -0.05f, 0.0f, 0.0f, 1.0f,

		-0.05f, 0.05f, 1.0f, 0.0f, 0.0f,
		0.05f, -0.05f, 0.0f, 1.0f, 0.0f,
		0.05f, 0.05f, 0.0f, 1.0f, 1.0f};

	matrices = new glm::mat4[amount];
	default_random_engine e();
	uniform_int_distribution<int> random();

	for (size_t i = 0; i < amount; i++)
	{
		/* code */
	}
	

	objectShader = Shader(FileSystem::getPath("shaders/advanced/instanceQuad/object.vs").c_str(), FileSystem::getPath("shaders/advanced/instanceQuad/object.fs").c_str());

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(2 * sizeof(float)));

	glGenBuffers(1, &instanceVBO);
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glBufferData(GL_ARRAY_BUFFER, 100 * sizeof(glm::vec2), translations, GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), 0);
	// 每渲染一个实例更新index=2的顶点属性
	glVertexAttribDivisor(2, 1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	// objectShader.use();
	// for (size_t i = 0; i < 100; i++) {
	// 	stringstream ss;
	// 	ss << "offsets[" << i << "]";
	// 	objectShader.setVec2(ss.str(), translations[i]);
	// }
}

void Galaxy::onCreate() {
	init();
}

void Galaxy::onRender() {
	super::onRender();
	objectShader.use();
	glBindVertexArray(VAO);
	glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100);
}

void Galaxy::onDestroy() {
}
