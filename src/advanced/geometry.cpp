#include "stb_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <learnopengl/advanced/geometry.h>
#include <learnopengl/shader.h>
#include <learnopengl/utils.h>
#include <algorithm>

using namespace std;

void Geometry::init() {
	float skyboxVertices[] = {
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

	// 隐藏鼠标光标
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glEnable(GL_DEPTH_TEST);

	model = make_unique<Model>(FileSystem::getPath("assets/objects/nanosuit_reflection/nanosuit.obj"));

	skyboxShader = Shader(FileSystem::getPath("shaders/advanced/cubemap/skybox.vs").c_str(), FileSystem::getPath("shaders/advanced/cubemap/skybox.fs").c_str());
	lightShader = Shader(FileSystem::getPath("shaders/modelLoad/lightSource.vs").c_str(), FileSystem::getPath("shaders/modelLoad/lightSource.fs").c_str());

	objectShader = Shader(
		FileSystem::getPath("shaders/advanced/geometry/object.vs").c_str(), 
		FileSystem::getPath("shaders/advanced/geometry/object.fs").c_str(),
		FileSystem::getPath("shaders/advanced/geometry/object.gs").c_str()
	);

	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);

	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glBindVertexArray(0);

	skyboxTexture = loadCubeMap(faces);
	objectShader.use();
	objectShader.setInt("skyboxTexture", 3);

	skyboxShader.use();
	skyboxShader.setInt("tex", 0);
	glfwSetTime(0.0);
}

void Geometry::onCreate() {
	init();
}

void Geometry::onRender() {
    super::onRender();
	glm::mat4 view = camera.getViewMat();
	glm::mat4 projection(1.0f);
	projection = glm::perspective(glm::radians(camera.zoom), 800 * 1.0f / 600, 0.1f, 100.0f);

	objectShader.use();
	objectShader.setVec3("viewPos", camera.position);
	objectShader.setFloat("material.shininess", 32.0f);


	objectShader.setVec3("dirLight.ambient", glm::vec3(0.4f)); 
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
	md = glm::scale(md, glm::vec3(0.5f, 0.5f, 0.5f));	//
	objectShader.setMat4("model", md);
	objectShader.setMat4("view", view);
	objectShader.setMat4("projection", projection);

	float time = static_cast<float>(glfwGetTime());
	 
	cout << "time:" << time << endl;
	cout << "factor:" << (sin(time) + 1.0) / 2.0 << endl;
	objectShader.setFloat("time", static_cast<float>(glfwGetTime()));

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);

	this->model->render(objectShader);

	glDepthFunc(GL_LEQUAL);
	glm::mat4 model(1.0f);
	view = glm::mat4(glm::mat3(camera.getViewMat()));
	skyboxShader.use();
	skyboxShader.setMat4("model", model);
	skyboxShader.setMat4("view", view);
	skyboxShader.setMat4("projection", projection);
	glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDepthFunc(GL_LESS);
}

void Geometry::onDestroy() {
	
}
