#include "stb_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <learnopengl/modelLoad/modelLoad.h>
#include <learnopengl/shader.h>
#include <learnopengl/utils.h>

using namespace std;

void ModelLoad::init() {

	// 隐藏鼠标光标
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	stbi_set_flip_vertically_on_load(true);
	glEnable(GL_DEPTH_TEST);

	// model = make_unique<Model>(FileSystem::getPath("assets/objects/backup/backup.fbx"));
	model = make_unique<Model>(FileSystem::getPath("assets/objects/elysia/elysia.fbx"));
	lightShader = Shader(FileSystem::getPath("shaders/modelLoad/lightSource.vs").c_str(), FileSystem::getPath("shaders/modelLoad/lightSource.fs").c_str());
	objectShader = Shader(FileSystem::getPath("shaders/modelLoad/object.vs").c_str(), FileSystem::getPath("shaders/modelLoad/object.fs").c_str());
}

void ModelLoad::onCreate() {
	init();
}


void ModelLoad::onRender() {
    super::onRender();

	glm::mat4 projection(1.0f);
	// 透视角度
	projection = glm::perspective(glm::radians(camera.zoom), 800 * 1.0f / 600, 0.1f, 100.0f);

	objectShader.use();
	objectShader.setVec3("viewPos", camera.position);
	objectShader.setFloat("material.shininess", 32.0f);


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
	glm::mat4 md = glm::mat4(1.0f);
	md = glm::translate(md, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
	md = glm::scale(md, glm::vec3(1.0f, 1.0f, 1.0f));	//
	objectShader.setMat4("model", md);
	objectShader.setMat4("view", camera.getViewMat());
	objectShader.setMat4("projection", projection);

	model->render(objectShader);

	// glBindVertexArray(lightVAO);
	// for (size_t i = 0; i < 10; i++) {
	// 	glm::mat4 model = glm::mat4(1.0f);
	// 	model = glm::translate(model, pointLights[i]);
	// 	model = glm::scale(model, glm::vec3(0.2f));
	// 	lightShader.setMat4("model", model);
	// 	glDrawArrays(GL_TRIANGLES, 0, 36);
	// }
}

void ModelLoad::onDestroy() {
	lightShader.release();
	objectShader.release();
}
