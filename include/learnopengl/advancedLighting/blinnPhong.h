#ifndef BLINNPHONG_H
#define BLINNPHONG_H

#include <cstdint>
#include <glm/glm.hpp>
#include <learnopengl/cameraRenderable.h>
#include <learnopengl/model.h>

class BlinnPhong : public CameraRenderable {
public:
	void init();
	virtual void onCreate();
	virtual void onRender();
	virtual void onDestroy();
	virtual void onProcessInput(float deltaTime);
	BlinnPhong(GLFWwindow *win) :
		CameraRenderable(win) {
	}

private:
	typedef CameraRenderable super;
	uint32_t lightVAO, lightVBO;
	uint32_t planetTexture;
	Shader lightShader;
	glm::vec3 lightPos = glm::vec3(0.0f, 0.4f, 1.6f);
	bool blinn = false;
	bool pressed = false;
};

#endif