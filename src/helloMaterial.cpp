#include "helloMaterial.h"
#include "shader.h"
#include "stb_image.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

using namespace std;

void HelloMaterial::init() {
	// 隐藏鼠标光标
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glEnable(GL_DEPTH_TEST);
	// 顶点坐标，法向量
	float vertices[] = {
		// 后面
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,

		// 前面
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

		// 左面
		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,

		// 右面
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,

		// 下面
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,

		// 上面
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f
	};
		
	lightShader = Shader(FileSystem::getPath("shaders/material/lightSource.vs").c_str(), FileSystem::getPath("shaders/material/lightSource.fs").c_str());
	objectShader = Shader(FileSystem::getPath("shaders/material/object.vs").c_str(), FileSystem::getPath("shaders/material/object.fs").c_str());

	glGenVertexArrays(1, &lightVAO);
	glGenVertexArrays(1, &objectVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(lightVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	// glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBindVertexArray(objectVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void HelloMaterial::onCreate() {
	init();
}

/*
 * 根据键盘输入平移视角
 */
void HelloMaterial::onProcessInput() {
	// W S A D 前后左右移动摄像机
	float speed = deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera.processKeyboard(FORWARD, deltaTime);
	} else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera.processKeyboard(BACKWARD, deltaTime);
	} else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		// 叉乘 +X * +Y = +Z  +Y * +X = -Z
		camera.processKeyboard(LEFT, deltaTime);
	} else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera.processKeyboard(RIGHT, deltaTime);
	}
}
/*
 * 根据鼠标移动旋转视角
 */
void HelloMaterial::onMouseMoved(double xposIn, double yposIn) {
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
}

void HelloMaterial::onRender() {
	float currentTime = (float)glfwGetTime();
	// lightPos.x = 1.0f + sin(currentTime) * 2.0f;
	// lightPos.y = sin(currentTime / 2.0f) * 1.0f;
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;
	glm::mat4 model(1.0f);
	glm::mat4 projection(1.0f);
	// 透视角度
	projection = glm::perspective(glm::radians(camera.zoom), 800 * 1.0f / 600, 0.1f, 100.0f);

	objectShader.use();
	objectShader.setVec3("viewPos", camera.position);
	objectShader.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
	objectShader.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
	objectShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
	objectShader.setFloat("material.shininess", 32.0f);

	// objectShader.setVec3("material.ambient", 0.0f, 0.1f, 0.06f);
	// objectShader.setVec3("material.diffuse", 0.0f, 0.50980392f, 0.50980392f);
	// objectShader.setVec3("material.specular", 0.50196078f, 0.50196078f, 0.50196078f);
	// objectShader.setFloat("material.shininess", 32.0f);

	// 动态更新光的颜色
	glm:: vec3 lightColor(1.0f);
	lightColor.x = sin(currentTime * 0.3f);
	lightColor.y = sin(currentTime * 1.2f);
	lightColor.z = sin(currentTime * 0.6f);
	// 环境光照通常会设置为一个比较低的强度，因为我们不希望环境光颜色太过显眼。
	// 光源的漫反射分量通常设置为光所具有的颜色，通常是一个比较明亮的白色。
	// 镜面光分量通常会保持为vec3(1.0)，以最大强度发光
	objectShader.setVec3("light.ambient", lightColor * 0.2f);
	objectShader.setVec3("light.diffuse", lightColor * 0.5f);
	objectShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
	// objectShader.setVec3("light.ambient", 1.0f, 1.0f, 1.0f);
	// objectShader.setVec3("light.diffuse", 1.0f, 1.0f, 1.0f);
	// objectShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
	objectShader.setVec3("light.position", lightPos);

	model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.0f, -1.0f, 0.0f));
	objectShader.setMat4("model", model);
	objectShader.setMat4("view", camera.getViewMat());
	objectShader.setMat4("projection", projection);
	glBindVertexArray(objectVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	lightShader.use();
	model = glm::mat4(1.0f);
	model = glm::translate(model, lightPos);
	model = glm::scale(model, glm::vec3(0.2f));
	lightShader.setVec3("lightColor", lightColor);
	lightShader.setMat4("model", model);
	lightShader.setMat4("view", camera.getViewMat());
	lightShader.setMat4("projection", projection);
	glBindVertexArray(lightVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void HelloMaterial::onDestroy() {
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteVertexArrays(1, &objectVAO);
	glDeleteBuffers(1, &VBO);
	lightShader.release();
	objectShader.release();
}
