#include <learnopengl/light/multipleLights.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <learnopengl/shader.h>
#include "stb_image.h"
#include <learnopengl/utils.h>
#include <assimp/Importer.hpp>

using namespace std;

void MultipleLights::init() {
	Assimp::Importer importer;
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
		
	lightShader = Shader(FileSystem::getPath("shaders/multipleLights/lightSource.vs").c_str(), FileSystem::getPath("shaders/multipleLights/lightSource.fs").c_str());
	objectShader = Shader(FileSystem::getPath("shaders/multipleLights/object.vs").c_str(), FileSystem::getPath("shaders/multipleLights/object.fs").c_str());

	glGenVertexArrays(1, &lightVAO);
	glGenVertexArrays(1, &objectVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(lightVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(objectVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	texture1 = loadTexture(FileSystem::getPath("assets/texture/container2.png").c_str());
	texture2 = loadTexture(FileSystem::getPath("assets/texture/container2_specular.png").c_str());


	objectShader.use();
    objectShader.setInt("material.diffuse", 0);
    objectShader.setInt("material.specular", 1);
}

void MultipleLights::onCreate() {
	init();
}

void MultipleLights::onRender() {
    super::onRender();

	glm::mat4 projection(1.0f);
	// 透视角度
	projection = glm::perspective(glm::radians(camera.zoom), 800 * 1.0f / 600, 0.1f, 100.0f);


	objectShader.use();
	objectShader.setVec3("viewPos", camera.position);
	objectShader.setFloat("material.shininess", 32.0f);


	// 动态更新光的颜色
	glm:: vec3 lightColor(1.0f);
	// lightColor.x = sin(currentTime * 0.3f);
	// lightColor.y = sin(currentTime * 1.2f);
	// lightColor.z = sin(currentTime * 0.6f);
	// 环境光照通常会设置为一个比较低的强度，因为我们不希望环境光颜色太过显眼。
	// 光源的漫反射分量通常设置为光所具有的颜色，通常是一个比较明亮的白色。
	// 镜面光分量通常会保持为vec3(1.0)，以最大强度发光
	objectShader.setVec3("dirLight.ambient", glm::vec3(0.05f)); 
	objectShader.setVec3("dirLight.diffuse", glm::vec3(0.4f));
	objectShader.setVec3("dirLight.specular", glm::vec3(0.5f));
	objectShader.setVec3("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));

	objectShader.setVec3("spotLight.ambient", glm::vec3(0.0f)); 
	objectShader.setVec3("spotLight.diffuse", glm::vec3(1.0f));
	objectShader.setVec3("spotLight.specular", glm::vec3(1.0f));
	objectShader.setVec3("spotLight.position", camera.position);
	objectShader.setVec3("spotLight.direction", camera.front);
	objectShader.setFloat("spotLight.constant", 1.0f);
	objectShader.setFloat("spotLight.linear", 0.09f);
	objectShader.setFloat("spotLight.quadratic", 0.032f);
	objectShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
	objectShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));


	for (size_t i = 0; i < 4; i++) {
		objectShader.setVec3(std::string("pointLights") + "[" + std::to_string(i) + "].ambient", glm::vec3(0.05f)); 
		objectShader.setVec3(std::string("pointLights") + "[" + std::to_string(i) + "].diffuse", glm::vec3(0.8f));
		objectShader.setVec3(std::string("pointLights") + "[" + std::to_string(i) + "].specular", glm::vec3(1.0f));
		objectShader.setVec3(std::string("pointLights") + "[" + std::to_string(i) + "].position", pointLights[i]);
		objectShader.setFloat(std::string("pointLights") + "[" + std::to_string(i) + "].constant", 1.0f);
		objectShader.setFloat(std::string("pointLights") + "[" + std::to_string(i) + "].linear", 0.09f);
		objectShader.setFloat(std::string("pointLights") + "[" + std::to_string(i) + "].quadratic", 0.032f);
	}

	objectShader.setMat4("view", camera.getViewMat());
	objectShader.setMat4("projection", projection);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	
	glBindVertexArray(objectVAO);
	for (size_t i = 0; i < 10; i++) {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[i]);
		float angle = 20.0f * i;
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		objectShader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	lightShader.use();
	lightShader.setVec3("lightColor", lightColor);
	lightShader.setMat4("view", camera.getViewMat());
	lightShader.setMat4("projection", projection);

	glBindVertexArray(lightVAO);
	for (size_t i = 0; i < 10; i++) {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, pointLights[i]);
		model = glm::scale(model, glm::vec3(0.2f));
		lightShader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

void MultipleLights::onDestroy() {
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteVertexArrays(1, &objectVAO);
	glDeleteBuffers(1, &VBO);
	glDeleteTextures(1, &texture1);
	glDeleteTextures(1, &texture2);
	lightShader.release();
	objectShader.release();
}
