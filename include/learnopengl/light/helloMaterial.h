#ifndef HELLOMATERIAL_H
#define HELLOMATERIAL_H
#include <learnopengl/renderable.h>
#include <cstdint>
#include <glm/glm.hpp>
#include <learnopengl/camera.h>

class HelloMaterial : public Renderable {
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
	glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
    void init();
	virtual void onCreate();
	virtual void onRender();
	virtual void onDestroy();
	virtual void onProcessInput();
	virtual void onMouseMoved(double xPos, double yPos);
	HelloMaterial(GLFWwindow *win): Renderable(win){}
};

#endif