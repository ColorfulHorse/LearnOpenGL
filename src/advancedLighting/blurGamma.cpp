#include "stb_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <learnopengl/advancedLighting/blurGamma.h>
#include <learnopengl/shader.h>
#include <learnopengl/utils.h>

using namespace std;

void BlurGamma::init() {
	// 隐藏鼠标光标
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	float vertices[] = {
        -1.0f, -1.0f,  0.0f, 0.0f,
		1.0f, -1.0f,   1.0f, 0.0f,
		-1.0f, 1.0f,   0.0f, 1.0f,

		1.0f, -1.0f,   1.0f, 0.0f,
		1.0f, 1.0f,    1.0f, 1.0f,
		-1.0f, 1.0f,   0.0f, 1.0f
    };

	stbi_set_flip_vertically_on_load(true);

	// 默认缓冲的四边形
	float rectVertices[] = {
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };
	screenShader = Shader(FileSystem::getPath("shaders/advancedLighting/blurGamma/screen.vs").c_str(), FileSystem::getPath("shaders/advancedLighting/blurGamma/screen.fs").c_str());
	objectShader = Shader(FileSystem::getPath("shaders/advancedLighting/blurGamma/object.vs").c_str(), FileSystem::getPath("shaders/advancedLighting/blurGamma/object.fs").c_str());

	normalTexture = loadTexture(FileSystem::getPath("assets/texture/mix.png").c_str(), GL_CLAMP_TO_EDGE);
	gammaTexture = loadTexture(FileSystem::getPath("assets/texture/mix.png").c_str(), GL_CLAMP_TO_EDGE, true);

	// 反向
	// normalTexture = loadTexture(FileSystem::getPath("assets/texture/mix_reverse.png").c_str(), GL_CLAMP_TO_EDGE);
	// gammaTexture = loadTexture(FileSystem::getPath("assets/texture/mix_reverse.png").c_str(), GL_CLAMP_TO_EDGE, true);

	glGenVertexArrays(1, &containerVAO);
	glGenBuffers(1, &containerVBO);

	glBindVertexArray(containerVAO);
	glBindBuffer(GL_ARRAY_BUFFER, containerVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
	glBindVertexArray(0);

	screenShader.use();
	screenShader.setInt("screenTexture", 0);
}

void BlurGamma::onCreate() {
	init();
}


void BlurGamma::onProcessInput(float deltaTime) {
	super::onProcessInput(deltaTime);

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        if (!pressed) {
			pressed = true;
			gamma = !gamma;
		}
		
    }

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
        pressed = false;
    }
}

void BlurGamma::onRender() {
	// 绑定到默认帧缓冲
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	screenShader.use();
	screenShader.setBool("gamma", gamma);
	glBindVertexArray(containerVAO);
	// 直接把绘制好的纹理绑定到默认缓冲
	glBindTexture(GL_TEXTURE_2D, gamma ? gammaTexture : normalTexture);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void BlurGamma::onDestroy() {
}
