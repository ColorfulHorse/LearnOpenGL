#ifndef GAMMA_H
#define GAMMA_H

#include <cstdint>
#include <glm/glm.hpp>
#include <learnopengl/cameraRenderable.h>
#include <learnopengl/model.h>

class Gamma : public CameraRenderable {
public:
	void init();
	virtual void onCreate();
	virtual void onRender();
	virtual void onDestroy();
	virtual void onProcessInput(float deltaTime);
	Gamma(GLFWwindow *win) :
		CameraRenderable(win) {
	}

private:
	typedef CameraRenderable super;
	uint32_t lightVAO, lightVBO;
	uint32_t planetTexture, planetTextureGamma;
	Shader lightShader;
	glm::vec3 lightPos = glm::vec3(0.0f, 0.4f, 1.6f);
	bool blinn = false;
	bool pressed = false;
	glm::vec3 lightPositions[4] = {
        glm::vec3(-3.0f, 0.0f, 0.0f),
        glm::vec3(-1.0f, 0.0f, 0.0f),
        glm::vec3 (1.0f, 0.0f, 0.0f),
        glm::vec3 (3.0f, 0.0f, 0.0f)
    };
    glm::vec3 lightColors[4] = {
        glm::vec3(0.25),
        glm::vec3(0.50),
        glm::vec3(0.75),
        glm::vec3(1.00)
    };
};

#endif