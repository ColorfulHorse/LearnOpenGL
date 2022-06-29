#include <glad/glad.h>
#include "stb_image.h"
#include <GLFW/glfw3.h>
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <learnopengl/advanced/galaxy.h>
#include <learnopengl/shader.h>
#include <learnopengl/utils.h>
#include <random>

using namespace std;

void Galaxy::init() {
	// 隐藏鼠标光标
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glEnable(GL_DEPTH_TEST);

	float quadVertices[] = {
		// 位置          // 颜色
		-0.05f, 0.05f, 1.0f, 0.0f, 0.0f,
		0.05f, -0.05f, 0.0f, 1.0f, 0.0f,
		-0.05f, -0.05f, 0.0f, 0.0f, 1.0f,

		-0.05f, 0.05f, 1.0f, 0.0f, 0.0f,
		0.05f, -0.05f, 0.0f, 1.0f, 0.0f,
		0.05f, 0.05f, 0.0f, 1.0f, 1.0f};

	matrices = new glm::mat4[amount];
	default_random_engine e;
	uniform_real_distribution<float> translateRandom(-offset, offset);
	uniform_real_distribution<float> scaleRandom(0.05f, 0.25f);
	uniform_real_distribution<float> rotateRandom(0.0f, 360.0f);
	for (size_t i = 0; i < amount; i++) {
		glm::mat4 model(1.0f);
		float angle = i * 1.0f / amount * 360.0f;
		float displacement = translateRandom(e);
		float x = sin(angle) * radius + displacement;
		displacement = translateRandom(e);
		float y = displacement * 0.4f;
		displacement = translateRandom(e);
		float z = cos(angle) * radius + displacement;
		model = glm::translate(model, glm::vec3(x, y, z));
		float scale = scaleRandom(e);
		model = glm::scale(model, glm::vec3(scale, scale, scale));
		float rotateAngle = rotateRandom(e);
		model = glm::rotate(model, rotateAngle, glm::vec3(0.4f, 0.6f, 0.8f));
		matrices[i] = model;
	}
	
	rock = make_unique<Model>(FileSystem::getPath("assets/objects/rock/rock.obj"));
	planet = make_unique<Model>(FileSystem::getPath("assets/objects/planet/planet.obj"));

	planetShader = Shader(FileSystem::getPath("shaders/advanced/galaxy/planet.vs").c_str(), FileSystem::getPath("shaders/advanced/galaxy/planet.fs").c_str());
	rockShader = Shader(FileSystem::getPath("shaders/advanced/galaxy/rock.vs").c_str(), FileSystem::getPath("shaders/advanced/galaxy/rock.fs").c_str());
	camera.move(glm::vec3(0.0f, 0.0f, 50.0f));
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), matrices, GL_STATIC_DRAW);

	for (auto iter = rock->meshes.begin(); iter != rock->meshes.end(); iter++) {
		uint32_t vao = iter->getVAO();
		glBindVertexArray(vao);
		int size = sizeof(glm::vec4);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * size, 0);
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * size, (void *) size);
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * size, (void *) (size * 2));
		glEnableVertexAttribArray(6);
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * size, (void *) (size * 3));
		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);
		glVertexAttribDivisor(6, 1);
		glBindVertexArray(0);
	}
	
}

void Galaxy::onCreate() {
	init();
}

void Galaxy::onRender() {
	super::onRender();
	glm::mat4 model(1.0f);
	glm::mat4 view = camera.getViewMat();;
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 1000.0f);
	model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f));
	model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
	planetShader.use();
	planetShader.setMat4("model", model);
	planetShader.setMat4("view", view);
	planetShader.setMat4("projection", projection);
	planet->render(planetShader);
	// for (size_t i = 0; i < amount; i++) {
	// 	planetShader.setMat4("model", matrices[i]);
	// 	rock->render(planetShader);
	// }
	rockShader.use();
	rockShader.setMat4("view", view);
	rockShader.setMat4("projection", projection);
	rockShader.setInt("metrial.texture_diffuse0", 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, rock->texture_loaded[0].id);
	// 把每个模型的mesh绘制amount遍
	for (size_t i = 0; i < rock->meshes.size(); i++) {
		auto mesh = rock->meshes[i];
		uint32_t vao = mesh.getVAO();
		glBindVertexArray(vao);
		glDrawElementsInstanced(GL_TRIANGLES, static_cast<unsigned int>(mesh.indices.size()), GL_UNSIGNED_INT, 0, amount);
		glBindVertexArray(0);
	}
	
}

void Galaxy::onDestroy() {
}
