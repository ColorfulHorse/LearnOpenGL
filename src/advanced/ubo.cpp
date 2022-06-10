#include "stb_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <learnopengl/advanced/ubo.h>
#include <learnopengl/shader.h>
#include <learnopengl/utils.h>
#include <algorithm>

using namespace std;

void UBO::init() {
	// 隐藏鼠标光标
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glEnable(GL_DEPTH_TEST);
	float cubeVertices[] = {
        // positions         
        -0.5f, -0.5f, -0.5f, 
         0.5f, -0.5f, -0.5f,  
         0.5f,  0.5f, -0.5f,  
         0.5f,  0.5f, -0.5f,  
        -0.5f,  0.5f, -0.5f, 
        -0.5f, -0.5f, -0.5f, 

        -0.5f, -0.5f,  0.5f, 
         0.5f, -0.5f,  0.5f,  
         0.5f,  0.5f,  0.5f,  
         0.5f,  0.5f,  0.5f,  
        -0.5f,  0.5f,  0.5f, 
        -0.5f, -0.5f,  0.5f, 

        -0.5f,  0.5f,  0.5f, 
        -0.5f,  0.5f, -0.5f, 
        -0.5f, -0.5f, -0.5f, 
        -0.5f, -0.5f, -0.5f, 
        -0.5f, -0.5f,  0.5f, 
        -0.5f,  0.5f,  0.5f, 

         0.5f,  0.5f,  0.5f,  
         0.5f,  0.5f, -0.5f,  
         0.5f, -0.5f, -0.5f,  
         0.5f, -0.5f, -0.5f,  
         0.5f, -0.5f,  0.5f,  
         0.5f,  0.5f,  0.5f,  

        -0.5f, -0.5f, -0.5f, 
         0.5f, -0.5f, -0.5f,  
         0.5f, -0.5f,  0.5f,  
         0.5f, -0.5f,  0.5f,  
        -0.5f, -0.5f,  0.5f, 
        -0.5f, -0.5f, -0.5f, 

        -0.5f,  0.5f, -0.5f, 
         0.5f,  0.5f, -0.5f,  
         0.5f,  0.5f,  0.5f,  
         0.5f,  0.5f,  0.5f,  
        -0.5f,  0.5f,  0.5f, 
        -0.5f,  0.5f, -0.5f, 
    };

	greenShader = Shader(FileSystem::getPath("shaders/advanced/ubo/object.vs").c_str(), FileSystem::getPath("shaders/advanced/ubo/green.fs").c_str());
	redShader = Shader(FileSystem::getPath("shaders/advanced/ubo/object.vs").c_str(), FileSystem::getPath("shaders/advanced/ubo/red.fs").c_str());

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), nullptr, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(cubeVertices), cubeVertices);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	

	glGenBuffers(1, &ubo);
	glBindBuffer(GL_UNIFORM_BUFFER, ubo);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), nullptr, GL_STATIC_DRAW);
	// ubo绑定到绑定点
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, ubo);
	glBindBufferRange(GL_UNIFORM_BUFFER, 0, ubo, 0, 2 * sizeof(glm::mat4));

	greenShader.use();
	greenShader.bindUniformBlock("Matrices", 0);
	redShader.use();
	redShader.bindUniformBlock("Matrices", 0);

	// 写入projection矩阵到uniform块0位置
	glm::mat4 projection = glm::perspective(glm::radians(camera.zoom), 800.0f/600.0f, 0.1f, 100.f);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UBO::onCreate() {
	init();
}

void UBO::onRender() {
    super::onRender();
	glBindBuffer(GL_UNIFORM_BUFFER, ubo);
	glm::mat4 view = camera.getViewMat();
	// 这里偏移为一个mat4
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	
	glm::mat4 model(1.0f);
	glBindBuffer(GL_ARRAY_BUFFER, VAO);
	greenShader.use();
	model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
	greenShader.setMat4("model", model);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	redShader.use();
	model = glm::translate(model, glm::vec3(-1.5f, 0.0f, 0.0f));
	redShader.setMat4("model", model);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void UBO::onDestroy() {
	
}
