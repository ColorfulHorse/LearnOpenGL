#ifndef HELLOREALLIGHT_H
#define HELLOREALLIGHT_H
#include <learnopengl/renderable.h>
#include <cstdint>
#include <glm/glm.hpp>
#include <learnopengl/camera.h>

class HelloRealLight : public Renderable {
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
	glm::vec3 cubePositions[10] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    void init();
	virtual void onCreate();
	virtual void onRender();
	virtual void onDestroy();
	virtual void onProcessInput();
	virtual void onMouseMoved(double xPos, double yPos);
	HelloRealLight(GLFWwindow *win): Renderable(win){}
};

#endif