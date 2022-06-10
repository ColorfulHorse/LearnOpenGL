#include "stb_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <learnopengl/advanced/framebuffer.h>
#include <learnopengl/shader.h>
#include <learnopengl/utils.h>

using namespace std;

void FrameBuffer::init() {
	// 隐藏鼠标光标
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// 箱子
	float boxVertices[] = {
		// positions          // texture Coords
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f};
	// 地板
	float floorVertices[] = {
		5.0f, -0.5f, 5.0f, 2.0f, 0.0f,
		-5.0f, -0.5f, 5.0f, 0.0f, 0.0f,
		-5.0f, -0.5f, -5.0f, 0.0f, 2.0f,

		5.0f, -0.5f, 5.0f, 2.0f, 0.0f,
		-5.0f, -0.5f, -5.0f, 0.0f, 2.0f,
		5.0f, -0.5f, -5.0f, 2.0f, 2.0f};
	// 默认缓冲的四边形
	float rectVertices[] = {
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };
	screenShader = Shader(FileSystem::getPath("shaders/advanced/frameBuffer/screen.vs").c_str(), FileSystem::getPath("shaders/advanced/frameBuffer/screen.fs").c_str());
	objectShader = Shader(FileSystem::getPath("shaders/advanced/blending/object.vs").c_str(), FileSystem::getPath("shaders/advanced/blending/object.fs").c_str());

	glGenVertexArrays(1, &containerVAO);
	glGenBuffers(1, &containerVBO);
	glGenVertexArrays(1, &floorVAO);
	glGenBuffers(1, &floorVBO);
	glGenVertexArrays(1, &rectVAO);
	glGenBuffers(1, &rectVBO);

	glBindVertexArray(containerVAO);
	glBindBuffer(GL_ARRAY_BUFFER, containerVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(boxVertices), boxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
	glBindVertexArray(0);

	glBindVertexArray(floorVAO);
	glBindBuffer(GL_ARRAY_BUFFER, floorVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(floorVertices), floorVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
	glBindVertexArray(0);

	glBindVertexArray(rectVAO);
	glBindBuffer(GL_ARRAY_BUFFER, rectVAO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectVertices), rectVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
	glBindVertexArray(0);

	floorTexture = loadTexture(FileSystem::getPath("assets/texture/metal.png").c_str());
	containerTexture = loadTexture(FileSystem::getPath("assets/texture/container.jpg").c_str());

	objectShader.use();
	objectShader.setInt("tex", 0);

	screenShader.use();
	screenShader.setInt("screenTexture", 0);


	glGenFramebuffers(1, &fbo);
	// GL_READ_FRAMEBUFFER 读  GL_DRAW_FRAMEBUFFER 写
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	glGenTextures(1, &textureColorBuffer);
	glBindTexture(GL_TEXTURE_2D, textureColorBuffer);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// 纹理作为颜色附件
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorBuffer,0);
	// 纹理作为深度和模板缓冲
	// glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, 800, 600, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);

	// 创建一个深度和模板渲染缓冲对象
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	// 指定rbo格式
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		cout << "ERROR::FRAMEBUFFER:: Framebuffer is incomplete!" << endl;
		return;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	// 线框模式
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void FrameBuffer::onCreate() {
	init();
}

void FrameBuffer::onRender() {
	// // 马赛克效果
	// glBindTexture(GL_TEXTURE_2D, textureColorBuffer);
	// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, smallWidth, smallHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// glViewport(0, 0, smallWidth, smallHeight);
	// glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	// glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, smallWidth, smallHeight);
	// glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	//======= 先绑定自定义帧缓冲，将箱子和地板绘制到它的纹理颜色附件中
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glm::mat4 model(1.0f);
	glm::mat4 projection(1.0f);
	// 透视角度
	projection = glm::perspective(glm::radians(camera.zoom), 800 * 1.0f / 600, 0.1f, 100.0f);

	objectShader.use();
	objectShader.setMat4("projection", projection);
	objectShader.setMat4("view", camera.getViewMat());

	// ============== 绘制地板

	glBindVertexArray(floorVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, floorTexture);
	objectShader.setMat4("model", model);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	// =========== 绘制箱子
	glBindVertexArray(containerVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, containerTexture);

	for (size_t i = 0; i < boxes.size(); i++) {
		model = glm::mat4(1.0f);
		model = glm::translate(model, boxes[i]);
		objectShader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	// 绑定到默认帧缓冲
	glViewport(0, 0, 800, 600);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);


	screenShader.use();
	glBindVertexArray(rectVAO);
	// 直接把绘制好的纹理绑定到默认缓冲
	glBindTexture(GL_TEXTURE_2D, textureColorBuffer);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void FrameBuffer::onDestroy() {
	glDeleteVertexArrays(1, &floorVAO);
	glDeleteVertexArrays(1, &containerVAO);
	glDeleteVertexArrays(1, &rectVAO);
	glDeleteBuffers(1, &floorVBO);
	glDeleteBuffers(1, &containerVBO);
	glDeleteBuffers(1, &rectVBO);
	glDeleteFramebuffers(1, &fbo);
	shader.release();
}
