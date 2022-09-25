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

// gamma校正
// 人眼感知到的亮度和物理亮度并不相同，0.2的物理亮度 ≈ 人眼感觉到的0.5亮度
// 这样的话，当用8bit存储亮度时，如果直接存物理亮度，那么低于人眼0.5亮度的暗部只有55（255 * 0.2）个，暗部亮部不平衡
// 为了平衡暗部和亮度，我们存人眼感觉到的亮度，用幂函数将物理亮度映射为人眼感知亮度，幂函数指数为1/gamma
// sRGB存储的就是人眼感觉到的亮度值，sRGB 0.5 ≈ 物理0.2，gamma为1/2.2

// 为什么gamma是2.2？
// 由于最开始的CRT显示器的输入电平和亮度是一个幂函数关系，这个函数的指数为2.2，后来的液晶显示器为了兼容一般也将gamma设置为这个值
// gamma为2.2时，物理亮度和人眼亮度的映射关系也比较准确
// 两全其美，这样一来我们只需要将亮度存为人眼感知到的亮度然后交给显示器就可以完美显示了

// 由于我们在计算光照时是基于物理模拟进行的，所以应该使用物理亮度，在线性空间进行计算
// 但是大多数贴图图片都是基于sRGB创作的，所以导入时要将它从gamma空间变换为线性空间，最后显示时再变换回去
void Gamma::init() {
	float planeVertices[] = {
        // positions            // normals         // texcoords
         10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
        -10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
        -10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,

         10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
        -10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,
         10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,  10.0f, 10.0f
    };

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

	shader = Shader(FileSystem::getPath("shaders/advancedLighting/gamma/object.vs").c_str(), FileSystem::getPath("shaders/advancedLighting/gamma/object.fs").c_str());
	lightShader = Shader(FileSystem::getPath("shaders/advancedLighting/gamma/light.vs").c_str(), FileSystem::getPath("shaders/advancedLighting/gamma/light.fs").c_str());

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
	shader.setFloat("material.shininess", 64.0f);
	glUniform3fv(glGetUniformLocation(shader.id, "lightPositions"), 4, &lightPositions[0][0]);
	glUniform3fv(glGetUniformLocation(shader.id, "lightColors"), 4, &lightColors[0][0]);
}

void Gamma::onProcessInput(float deltaTime) {
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
	shader.setBool("gamma", gamma);
	shader.setMat4("model", model);
	shader.setMat4("view", view);
	shader.setMat4("projection", projection);
	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gamma ? planetTextureGamma : planetTexture);
	
	glDrawArrays(GL_TRIANGLES, 0, 6);

	for (size_t i = 0; i < 4; i++) {
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPositions[i]);
		model = glm::scale(model, glm::vec3(0.1f));
		lightShader.use();
		lightShader.setMat4("model", model);
		lightShader.setMat4("view", view);
		lightShader.setMat4("projection", projection);
		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	
}

void Gamma::onDestroy() {
}
