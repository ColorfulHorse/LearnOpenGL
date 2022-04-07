#include "helloCamera.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stb_image.h"
#include "shader.h"

using namespace std;

void HelloCamera::init() {
	glEnable(GL_DEPTH_TEST);
	float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

	shader = Shader("helloCamera.vs", "helloCamera.fs");
	shaderProgram = shader.id;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &texture1);
	glActiveTexture(GL_TEXTURE1);
	glGenTextures(1, &texture2);

	glBindTexture(GL_TEXTURE_2D, texture1);
	// 设置纹理环绕, str对应xyz
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// 放大缩小时平滑过滤
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int32_t width, height, channels;
	stbi_uc *data = stbi_load("container.jpg", &width, &height, &channels, 0);
	if (data) {
		// 根据图片创建纹理
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		// 创建多级渐远纹理
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		std::cout << "Failed to load texture1" << std::endl;
	}
	stbi_image_free(data);

	glBindTexture(GL_TEXTURE_2D, texture2);
	// 设置纹理环绕, str对应xyz
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// 放大缩小时平滑过滤
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	data = stbi_load("awesomeface.png", &width, &height, &channels, 0);
	if (data) {
		// 根据图片创建纹理
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		// 创建多级渐远纹理
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		std::cout << "Failed to load texture2" << std::endl;
	}
	stbi_image_free(data);
	shader.use();
	shader.setInt("texture1", 0);
	shader.setInt("texture2", 1);
}

void HelloCamera::onCreate() {
	init();
}

void HelloCamera::onProcessInput(GLFWwindow *window) {
	// W S A D 前后左右移动摄像机
	float speed = deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {	
		cameraPos += speed * cameraFront;
	}else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		cameraPos -= speed * cameraFront;
	}else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		// 叉乘 +X * +Y = +Z  +Y * +X = -Z
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
	}else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
	}
	
}

void HelloCamera::onRender() {
	float currentTime = (float) glfwGetTime();
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);

	shader.use();
	glBindVertexArray(VAO);
	// glm::mat4 model(1.0f);
	glm::mat4 view(1.0f);
	glm::mat4 projection(1.0f);
	// 绕x轴旋转
	// model = glm::rotate(model, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	// 向z轴后移
	// 创建一个相机，绕y轴顺时针旋转，半径为10
	// float raduis = 10.0f;
	// float cameraX = static_cast<float>((raduis * sin(glfwGetTime())));
	// float cameraZ = static_cast<float>(raduis * cos(glfwGetTime()));
	// view = glm::lookAt(glm::vec3(cameraX, 0.0f, cameraZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	view = glm::lookAt(cameraPos, cameraFront + cameraPos, cameraUp);
	// 透视角度
	projection = glm::perspective(glm::radians(45.0f), 800 * 1.0f / 600, 0.1f, 100.0f);
	// shader.setMat4("model", model);
	shader.setMat4("view", view);
	shader.setMat4("projection", projection);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	for (size_t i = 0; i < 10; i++) {
		glm::mat4 model(1.0f);
		model = glm::translate(model, cubePositions[i]);
		shader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}


void HelloCamera::onDestroy() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteTextures(1, &texture1);
	glDeleteTextures(1, &texture2);
	glDeleteProgram(shaderProgram);
}
