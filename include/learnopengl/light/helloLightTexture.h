#ifndef HELLOLIGHTTEXTURE_H
#define HELLOLIGHTTEXTURE_H
#include <cstdint>
#include <glm/glm.hpp>
#include <learnopengl/cameraRenderable.h>

class HelloLightTexture : public CameraRenderable {
public:
	uint32_t VBO, lightVAO, objectVAO;
	uint32_t texture1, texture2, texture3;
	// 鼠标默认点
	float lastX = 400.0f, lastY = 300.0f;
	bool firstMove = true;
	Shader objectShader;
	Shader lightShader;
	glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
	void init();
	virtual void onCreate();
	virtual void onRender();
	virtual void onDestroy();
	HelloLightTexture(GLFWwindow *win) :
		CameraRenderable(win) {
	}

private:
	typedef CameraRenderable super;
};

#endif