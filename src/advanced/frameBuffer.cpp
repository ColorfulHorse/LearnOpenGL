#include "stb_image.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
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
	glEnable(GL_DEPTH_TEST);
	// 顶点坐标，这里的顶点是按照顺时针方向的
	float vertices[] = {
		// back face
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // bottom-left
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f,	 // bottom-right
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,	 // top-right
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,	 // top-right
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,	 // top-left
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // bottom-left
		// front face
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom-left
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f,	// top-right
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,	// bottom-right
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f,	// top-right
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom-left
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,	// top-left
		// left face
		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,	 // top-right
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // bottom-left
		-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,	 // top-left
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // bottom-left
		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,	 // top-right
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,	 // bottom-right
										 // right face
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,	 // top-left
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,	 // top-right
		0.5f, -0.5f, -0.5f, 0.0f, 1.0f,	 // bottom-right
		0.5f, -0.5f, -0.5f, 0.0f, 1.0f,	 // bottom-right
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f,	 // bottom-left
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,	 // top-left
		// bottom face
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // top-right
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,	 // bottom-left
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f,	 // top-left
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,	 // bottom-left
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // top-right
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,	 // bottom-right
		// top face
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, // top-left
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,	// top-right
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,	// bottom-right
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,	// bottom-right
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,	// bottom-left
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f	// top-left
	};

	shader = Shader(FileSystem::getPath("shaders/advanced/stencilTest/object.vs").c_str(), FileSystem::getPath("shaders/advanced/stencilTest/object.fs").c_str());

	glGenFramebuffers(1, &fbo);
	// GL_READ_FRAMEBUFFER 读  GL_DRAW_FRAMEBUFFER 写
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	glGenTextures(1, &textureColorBuffer);
	glBindTexture(GL_TEXTURE_2D, textureColorBuffer);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// 纹理作为颜色附件
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, 0);
	// 纹理作为深度和模板缓冲
	// glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, 800, 600, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);

	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE) {
		
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::onCreate() {
	init();
}

void FrameBuffer::onRender() {
	float currentTime = (float)glfwGetTime();

	deltaTime = currentTime - lastTime;
	lastTime = currentTime;

	glm::mat4 model(1.0f);
	glm::mat4 projection(1.0f);
	projection = glm::perspective(glm::radians(camera.zoom), 800 * 1.0f / 600, 0.1f, 100.0f);

	shader.use();
	shader.setMat4("projection", projection);
	shader.setMat4("view", camera.getViewMat());
	shader.setMat4("model", model);

	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureColorBuffer);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void FrameBuffer::onDestroy() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteFramebuffers(1, &fbo);
	shader.release();
}
