#include <learnopengl/basic/helloCamera.h>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stb_image.h"
#include <learnopengl/shader.h>

using namespace std;

void HelloCamera::init() {
	// 隐藏鼠标光标
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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

	shader = Shader(FileSystem::getPath("shaders/helloCamera.vs").c_str(), FileSystem::getPath("shaders/helloCamera.fs").c_str());
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
	stbi_uc *data = stbi_load(FileSystem::getPath("assets/texture/container.jpg").c_str(), &width, &height, &channels, 0);
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
	data = stbi_load(FileSystem::getPath("assets/texture/awesomeface.png").c_str(), &width, &height, &channels, 0);
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

/* 
 * 根据键盘输入平移视角
 */
void HelloCamera::onProcessInput() {
	// W S A D 前后左右移动摄像机
	float speed = deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {	
		camera.processKeyboard(FORWARD, deltaTime);
	}else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera.processKeyboard(BACKWARD, deltaTime);
	}else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		// 叉乘 +X * +Y = +Z  +Y * +X = -Z
		camera.processKeyboard(LEFT, deltaTime);
	}else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera.processKeyboard(RIGHT, deltaTime);
	}
	
}
/* 
 * 根据鼠标移动旋转视角
 */
void HelloCamera::onMouseMoved(double xposIn, double yposIn) {
	float xPos = static_cast<float>(xposIn);
    float yPos = static_cast<float>(yposIn);
	if (firstMove) {
		lastX = xPos;
		lastY = yPos;
		firstMove = false;
	}
	
	// 灵敏度
	float sensitivity = 0.1f;
	float offsetX = xPos - lastX;
	float offsetY = lastY - yPos;
	lastX = xPos;
	lastY = yPos;
	camera.processMouseMovement(offsetX, offsetY);
	// yaw += offsetX * sensitivity;
	// pitch += offsetY * sensitivity;
	// // 限制俯仰角避免翻转现象
	// if (pitch > 89.0f) {
	// 	pitch = 89.0f;
	// } else if (pitch < -89.0f) {
	// 	pitch = -89.0f;
	// }
	
	// // 根据向量的两次投影计算出摄像机朝向向量
	// // 初始pitch yaw都为0时，x=1, y=0, z=0，摄像头实际上指向了x轴正半轴
	// // 所以初始yaw需要是-90，x=0 y=0 z=-1， 指向z轴负半轴
	// cameraFront.x = cos(glm::radians(pitch)) * cos(glm::radians((yaw)));
	// cameraFront.y = sin(glm::radians(pitch));
	// cameraFront.z = cos(glm::radians(pitch)) * sin(glm::radians((yaw)));
	// cameraFront = glm::normalize(cameraFront);
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
	// glm::mat4 view(1.0f);
	glm::mat4 projection(1.0f);
	// 绕x轴旋转
	// model = glm::rotate(model, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	// 向z轴后移
	// 创建一个相机，绕y轴顺时针旋转，半径为10
	// float raduis = 10.0f;
	// float cameraX = static_cast<float>((raduis * sin(glfwGetTime())));
	// float cameraZ = static_cast<float>(raduis * cos(glfwGetTime()));
	// view = glm::lookAt(glm::vec3(cameraX, 0.0f, cameraZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	// view = glm::lookAt(cameraPos, cameraFront + cameraPos, cameraUp);
	// 透视角度
	projection = glm::perspective(glm::radians(camera.zoom), 800 * 1.0f / 600, 0.1f, 100.0f);
	// shader.setMat4("model", model);
	shader.setMat4("view", camera.getViewMat());
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
