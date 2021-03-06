#include "stb_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <learnopengl/light/helloLightTexture.h>
#include <learnopengl/shader.h>
#include <learnopengl/utils.h>

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
		
	lightShader = Shader(FileSystem::getPath("shaders/lightTexture/lightSource.vs").c_str(), FileSystem::getPath("shaders/lightTexture/lightSource.fs").c_str());
	objectShader = Shader(FileSystem::getPath("shaders/lightTexture/object.vs").c_str(), FileSystem::getPath("shaders/lightTexture/object.fs").c_str());

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

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	texture1 = loadTexture(FileSystem::getPath("assets/texture/container2.png").c_str());
	texture2 = loadTexture(FileSystem::getPath("assets/texture/container2_specular.png").c_str());
	texture3 = loadTexture(FileSystem::getPath("assets/texture/matrix.jpg").c_str());

	objectShader.use();
    objectShader.setInt("material.diffuse", 0);
    objectShader.setInt("material.specular", 1);
	objectShader.setInt("material.emission", 2);
}

void HelloLightTexture::onCreate() {
	init();
}


void HelloLightTexture::onRender() {
    super::onRender();
	glm::mat4 model(1.0f);
	glm::mat4 projection(1.0f);
	// 透视角度
	projection = glm::perspective(glm::radians(camera.zoom), 800 * 1.0f / 600, 0.1f, 100.0f);


	objectShader.use();
	objectShader.setVec3("viewPos", camera.position);
	// objectShader.setInt("material.diffuse", 0);
	// objectShader.setInt("material.specular", 1);
	objectShader.setFloat("material.shininess", 32.0f);

	float currentTime = static_cast<float>(glfwGetTime());
	// 动态更新光的颜色
	glm:: vec3 lightColor(1.0f);
	lightColor.x = sin(currentTime * 0.3f);
	lightColor.y = sin(currentTime * 1.2f);
	lightColor.z = sin(currentTime * 0.6f);
	// 环境光照通常会设置为一个比较低的强度，因为我们不希望环境光颜色太过显眼。
	// 光源的漫反射分量通常设置为光所具有的颜色，通常是一个比较明亮的白色。
	// 镜面光分量通常会保持为vec3(1.0)，以最大强度发光
	objectShader.setVec3("light.ambient", glm::vec3(0.2f)); 
	objectShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
	objectShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
	objectShader.setVec3("light.position", lightPos);

	// model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.0f, -1.0f, 0.0f));
	objectShader.setMat4("model", model);
	objectShader.setMat4("view", camera.getViewMat());
	objectShader.setMat4("projection", projection);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, texture3);

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
	glDeleteTextures(1, &texture1);
	glDeleteTextures(1, &texture2);
	glDeleteTextures(1, &texture3);
	lightShader.release();
	objectShader.release();
}
