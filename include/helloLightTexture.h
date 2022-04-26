#ifndef HELLOLIGHTTEXTURE_H
#define HELLOLIGHTTEXTURE_H
#include "renderable.h"
#include <cstdint>
#include <glm/glm.hpp>
#include "camera.h"

class HelloLightTexture : public Renderable {
public:
	uint32_t VBO, lightVAO, objectVAO;
	uint32_t texture1, texture2, texture3;
	Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
	float deltaTime = 0.0f;
	float lastTime = 0.0f;
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
	virtual void onProcessInput();
	virtual void onMouseMoved(double xPos, double yPos);
	HelloLightTexture(GLFWwindow *win): Renderable(win){}
};

#endif