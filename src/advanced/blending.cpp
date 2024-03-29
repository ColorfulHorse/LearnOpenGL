﻿#include "stb_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <learnopengl/advanced/blending.h>
#include <learnopengl/shader.h>
#include <learnopengl/utils.h>
#include <algorithm>

using namespace std;

void Blending::init() {
	// 隐藏鼠标光标
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glEnable(GL_DEPTH_TEST);
	// 箱子
	float boxVertices[] = {
		// positions          // texture Coords
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f};
	// 地板
	float floorVertices[] = {
		5.0f, -0.5f, 5.0f, 2.0f, 0.0f,
		-5.0f, -0.5f, 5.0f, 0.0f, 0.0f,
		-5.0f, -0.5f, -5.0f, 0.0f, 2.0f,

		5.0f, -0.5f, 5.0f, 2.0f, 0.0f,
		-5.0f, -0.5f, -5.0f, 0.0f, 2.0f,
		5.0f, -0.5f, -5.0f, 2.0f, 2.0f};
	// 草
	float grassVertices[] = {
		-0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 1.0f,

		-0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f};

	objectShader = Shader(FileSystem::getPath("shaders/advanced/blending/object.vs").c_str(), FileSystem::getPath("shaders/advanced/blending/object.fs").c_str());

	glGenVertexArrays(1, &containerVAO);
	glGenBuffers(1, &containerVBO);
	glGenVertexArrays(1, &floorVAO);
	glGenBuffers(1, &floorVBO);
	glGenVertexArrays(1, &grassVAO);
	glGenBuffers(1, &grassVBO);

	glBindVertexArray(containerVAO);
	glBindBuffer(GL_ARRAY_BUFFER, containerVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(boxVertices), boxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
	glBindVertexArray(0);

	glBindVertexArray(floorVAO);
	glBindBuffer(GL_ARRAY_BUFFER, floorVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(floorVertices), floorVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
	glBindVertexArray(0);

	glBindVertexArray(grassVAO);
	glBindBuffer(GL_ARRAY_BUFFER, grassVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grassVertices), grassVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
	glBindVertexArray(0);

	floorTexture = loadTexture(FileSystem::getPath("assets/texture/metal.png").c_str());
	containerTexture = loadTexture(FileSystem::getPath("assets/texture/marble.jpg").c_str());
	grassTexture = loadTexture(FileSystem::getPath("assets/texture/window.png").c_str());

	objectShader.use();
	objectShader.setInt("tex", 0);

	glEnable(GL_BLEND);
	// 上面绿60%alpha, 下面红100%, 最终颜色=绿*0.6+红*0.4
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Blending::onCreate() {
	init();
}

void Blending::onRender() {
    super::onRender();

	// 根据window距离观察者的距离由远到近排序
	std::sort(windows.begin(), windows.end(), [this](glm::vec3 &first, glm::vec3 &second) {
		float distance1 = glm::length(camera.position - first);
		float distance2 = glm::length(camera.position - second);
		return distance1 > distance2;
	});

	// 先绘制箱子本体，将对应点的模板值设为1，然后将箱子放大一点，只绘制模板值不为1的部分为边框

	glm::mat4 model(1.0f);
	glm::mat4 projection(1.0f);
	// 透视角度
	projection = glm::perspective(glm::radians(camera.zoom), 800 * 1.0f / 600, 0.1f, 100.0f);

	objectShader.use();
	objectShader.setMat4("projection", projection);
	objectShader.setMat4("view", camera.getViewMat());


	// ============== 绘制地板

	glBindVertexArray(floorVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, floorTexture);
	objectShader.setMat4("model", model);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	// =========== 绘制箱子
	glBindVertexArray(containerVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, containerTexture);

	for (size_t i = 0; i < boxes.size(); i++) {
		model = glm::mat4(1.0f);
		model = glm::translate(model, boxes[i]);
		objectShader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	// =========== 绘制草
	glBindVertexArray(grassVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, grassTexture);

	for (size_t i = 0; i < windows.size(); i++) {
		model = glm::mat4(1.0f);
		model = glm::translate(model, windows[i]);
		objectShader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	glBindVertexArray(0);
}

void Blending::onDestroy() {
	glDeleteVertexArrays(1, &containerVAO);
	glDeleteVertexArrays(1, &floorVAO);
	glDeleteVertexArrays(1, &grassVAO);
	glDeleteBuffers(1, &containerVBO);
	glDeleteBuffers(1, &floorVBO);
	glDeleteBuffers(1, &grassVBO);
	objectShader.release();
}
