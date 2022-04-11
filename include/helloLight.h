#ifndef HELLOLIGHT_H
#define HELLOLIGHT_H
#include "renderable.h"
#include <cstdint>
#include <glm/glm.hpp>
#include "camera.h"

class HelloLight : public Renderable {
public:
	uint32_t VBO, lightVAO, objectVAO;
	Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
	float deltaTime = 0.0f;
	float lastTime = 0.0f;
	// 鼠标默认点
	float lastX = 400.0f, lastY = 300.0f;
	bool firstMove = true;
	Shader objectShader;
	Shader lightShader;
    void init();
	virtual void onCreate();
	virtual void onRender();
	virtual void onDestroy();
	virtual void onProcessInput();
	virtual void onMouseMoved(double xPos, double yPos);
	HelloLight(GLFWwindow *win): Renderable(win){}
};

#endif