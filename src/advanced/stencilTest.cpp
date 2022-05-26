#include "stb_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <learnopengl/advanced/stencilTest.h>
#include <learnopengl/shader.h>
#include <learnopengl/utils.h>

using namespace std;

void StencilTest::init() {
	// 隐藏鼠标光标
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glEnable(GL_DEPTH_TEST);
	// 顶点坐标，法向量
	float vertices[] = {
		// positions          // texture Coords
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f};

	float floorVertices[] = {
		 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

         5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
         5.0f, -0.5f, -5.0f,  2.0f, 2.0f
	};

	borderShader = Shader(FileSystem::getPath("shaders/advanced/stencilTest/object.vs").c_str(), FileSystem::getPath("shaders/advanced/stencilTest/border.fs").c_str());
	objectShader = Shader(FileSystem::getPath("shaders/advanced/stencilTest/object.vs").c_str(), FileSystem::getPath("shaders/advanced/stencilTest/object.fs").c_str());

	glGenVertexArrays(1, &containerVAO);
	glGenVertexArrays(1, &floorVAO);
	glGenBuffers(1, &containerVBO);
	glGenBuffers(1, &floorVBO);

	glBindVertexArray(containerVAO);
	glBindBuffer(GL_ARRAY_BUFFER, containerVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
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

	floorTexture = loadTexture(FileSystem::getPath("assets/texture/metal.png").c_str());
	containerTexture = loadTexture(FileSystem::getPath("assets/texture/marble.jpg").c_str());
	
	objectShader.use();
	objectShader.setInt("tex", 0);
	
	glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_STENCIL_TEST);
	// 模板测试 通过/失败 进行的操作
	// 模板测试和深度测试都通过时，替换模板值
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
}

void StencilTest::onCreate() {
	init();
}

void StencilTest::onRender() {
	float currentTime = (float)glfwGetTime();

	deltaTime = currentTime - lastTime;
	lastTime = currentTime;

	// 先绘制箱子本体，将对应点的模板值设为1，然后将箱子放大一点，只绘制模板值不为1的部分为边框

	glm::mat4 model(1.0f);
	glm::mat4 projection(1.0f);
	// 透视角度
	projection = glm::perspective(glm::radians(camera.zoom), 800 * 1.0f / 600, 0.1f, 100.0f);

	objectShader.use();
	objectShader.setMat4("projection", projection);
	objectShader.setMat4("view", camera.getViewMat());
	
	borderShader.use();
	borderShader.setMat4("projection", projection);
	borderShader.setMat4("view", camera.getViewMat());

	// ============== 绘制地板

	objectShader.use();
	// // 永远通过测试，但是关闭模板写入
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilMask(0x00);
	glBindVertexArray(floorVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, floorTexture);
	objectShader.setMat4("model", model);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	// =========== 绘制箱子

	// 永远通过测试，开启模板写入
	// 所以绘制箱子时会将箱子部分对应的模板值更新为1，(new & mask) ref > (old & mask)
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilMask(0xff);
	glBindVertexArray(containerVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, containerTexture);

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
	objectShader.setMat4("model", model);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	objectShader.setMat4("model", model);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// ========= 绘制箱子边框

	// 模板值不为1时通过测试
	glStencilFunc(GL_NOTEQUAL, 1, 0xff);
	glStencilMask(0x00);
	// 关闭深度测试防止边框被地板遮挡
	glDisable(GL_DEPTH_TEST);

	borderShader.use();
	glBindVertexArray(containerVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, containerTexture);

	float scale = 1.1f;

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
	model = glm::scale(model, glm::vec3(scale, scale, scale));
	borderShader.setMat4("model", model);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(scale, scale, scale));
	borderShader.setMat4("model", model);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// 重置参数
	glStencilFunc(GL_ALWAYS, 1, 0xff);
	glStencilMask(0xff);
	glEnable(GL_DEPTH_TEST);
}

void StencilTest::onDestroy() {
	glDeleteVertexArrays(1, &containerVAO);
	glDeleteVertexArrays(1, &floorVAO);
	glDeleteBuffers(1, &containerVBO);
	glDeleteBuffers(1, &floorVBO);
	borderShader.release();
	objectShader.release();
}
