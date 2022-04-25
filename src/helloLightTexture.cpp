#include "helloLightTexture.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "shader.h"
#include "stb_image.h"
#include "utils.h"

using namespace std;

void HelloLightTexture::init() {
	// 隐藏鼠标光标
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glEnable(GL_DEPTH_TEST);
	// 顶点坐标，法向量
	float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };
		
	lightShader = Shader("shaders/lightTexture/lightSource.vs", "shaders/lightTexture/lightSource.fs");
	objectShader = Shader("shaders/lightTexture/object.vs", "shaders/lightTexture/object.fs");

	glGenVertexArrays(1, &lightVAO);
	glGenVertexArrays(1, &objectVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(lightVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	// glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBindVertexArray(objectVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	loadTexture("assets/texture/container2.png");
}

void HelloLightTexture::onCreate() {
	init();
}

/*
 * 根据键盘输入平移视角
 */
void HelloLightTexture::onProcessInput() {
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
void HelloLightTexture::onMouseMoved(double xposIn, double yposIn) {
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

void HelloLightTexture::onRender() {
	float currentTime = (float)glfwGetTime();
	// lightPos.x = 1.0f + sin(currentTime) * 2.0f;
	// lightPos.y = sin(currentTime / 2.0f) * 1.0f;
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;
	glm::mat4 model(1.0f);
	glm::mat4 projection(1.0f);
	// 透视角度
	projection = glm::perspective(glm::radians(camera.zoom), 800 * 1.0f / 600, 0.1f, 100.0f);

	glBindTexture(GL_TEXTURE_2D, texture1);

	objectShader.use();
	objectShader.setVec3("viewPos", camera.position);
	objectShader.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
	objectShader.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
	objectShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
	objectShader.setFloat("material.shininess", 32.0f);


	// 动态更新光的颜色
	glm:: vec3 lightColor(1.0f);
	lightColor.x = sin(currentTime * 0.3f);
	lightColor.y = sin(currentTime * 1.2f);
	lightColor.z = sin(currentTime * 0.6f);
	// 环境光照通常会设置为一个比较低的强度，因为我们不希望环境光颜色太过显眼。
	// 光源的漫反射分量通常设置为光所具有的颜色，通常是一个比较明亮的白色。
	// 镜面光分量通常会保持为vec3(1.0)，以最大强度发光
	objectShader.setInt("light.diffuse", 0);
	objectShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
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

void HelloLightTexture::onDestroy() {
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteVertexArrays(1, &objectVAO);
	glDeleteBuffers(1, &VBO);
	lightShader.release();
	objectShader.release();
}
