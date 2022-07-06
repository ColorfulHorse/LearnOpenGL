#include <glad/glad.h>
#include "stb_image.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <learnopengl/advancedLighting/gamma.h>
#include <learnopengl/shader.h>
#include <learnopengl/utils.h>

using namespace std;

// gama校正
// 人眼感知到的亮度和物理亮度并不相同，0.2的亮度等同于人眼感觉到的0.5
// 这样的话，如果用8bit物理亮度来表示，那么低于人眼0.5亮度的暗部只有55个
// 这样一来可以表示的暗部和亮部平衡
void Gamma::init() {
	float planeVertices[] = {
		// positions            // normals         // texcoords
		10.0f, -0.5f, 10.0f, 0.0f, 1.0f, 0.0f, 10.0f, 0.0f,
		-10.0f, -0.5f, 10.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		-10.0f, -0.5f, -10.0f, 0.0f, 1.0f, 0.0f, 0.0f, 10.0f,

		10.0f, -0.5f, 10.0f, 0.0f, 1.0f, 0.0f, 10.0f, 0.0f,
		-10.0f, -0.5f, -10.0f, 0.0f, 1.0f, 0.0f, 0.0f, 10.0f,
		10.0f, -0.5f, -10.0f, 0.0f, 1.0f, 0.0f, 10.0f, 10.0f};

	float cubeVertices[] = {
		// positions
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, 0.5f, -0.5f,
		0.5f, 0.5f, -0.5f,
		-0.5f, 0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,

		-0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,

		0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,

		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, 0.5f, -0.5f,
		0.5f, 0.5f, -0.5f,
		0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f, -0.5f};

	shader = Shader(FileSystem::getPath("shaders/advancedLighting/object.vs").c_str(), FileSystem::getPath("shaders/advancedLighting/object.fs").c_str());
	lightShader = Shader(FileSystem::getPath("shaders/advancedLighting/light.vs").c_str(), FileSystem::getPath("shaders/advancedLighting/light.fs").c_str());

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));

	glGenVertexArrays(1, &lightVAO);
	glGenBuffers(1, &lightVBO);
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	
	glBindVertexArray(0);
	planetTexture = loadTexture(FileSystem::getPath("assets/texture/wood.png").c_str());
	planetTextureGamma = loadTexture(FileSystem::getPath("assets/texture/wood.png").c_str(), -1, true);
	shader.use();
	shader.setInt("material.texture_diffuse", 0);
	shader.setFloat("material.shininess", 32.0f);
	shader.setVec3("lightPos", lightPos);
}

void Gamma::onProcessInput(float deltaTime) {
	super::onProcessInput(deltaTime);

	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
        if (!pressed) {
			pressed = true;
			blinn = !blinn;
		}
		
    }

	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_RELEASE) {
        pressed = false;
    }
}

void Gamma::onCreate() {
	init();
}

void Gamma::onRender() {
	super::onRender();

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = camera.getViewMat();
	glm::mat4 projection(1.0f);
	projection = glm::perspective(glm::radians(camera.zoom), 800 * 1.0f / 600, 0.1f, 100.0f);

	shader.use();
	shader.setVec3("viewPos", camera.position);
	shader.setBool("blinn", blinn);
	shader.setMat4("model", model);
	shader.setMat4("view", view);
	shader.setMat4("projection", projection);
	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, planetTexture);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	model = glm::translate(model, lightPos);
	model = glm::scale(model, glm::vec3(0.1f));
	lightShader.use();
	lightShader.setMat4("model", model);
	lightShader.setMat4("view", view);
	lightShader.setMat4("projection", projection);
	glBindVertexArray(lightVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Gamma::onDestroy() {
}
