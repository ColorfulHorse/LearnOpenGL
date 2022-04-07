#ifndef CAMERA_H
#define CAMERA_H
#include "renderable.h"
#include <cstdint>
#include <glm/glm.hpp>

class HelloCamera : public Renderable {
public:
    uint32_t texture1 = 0, texture2 = 0;
	glm::vec3 cameraPos = glm::vec3(0.0f, 1.0f, 3.0f);
	// 相机朝向
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cubePositions[10] = {
		glm::vec3(0.0f,  0.0f, 0.0f), 
		glm::vec3(2.0f,  5.0f, -15.0f), 
		glm::vec3(-1.5f, -2.2f, -2.5f),  
		glm::vec3(-3.8f, -2.0f, -12.3f),  
		glm::vec3( 2.4f, -0.4f, -3.5f),  
		glm::vec3(-1.7f,  3.0f, -7.5f),  
		glm::vec3( 1.3f, -2.0f, -2.5f),  
		glm::vec3( 1.5f,  2.0f, -2.5f), 
		glm::vec3( 1.5f,  0.2f, -1.5f), 
		glm::vec3(-1.3f,  1.0f, -1.5f)  
	};
	float deltaTime = 0.0f;
	float lastTime = 0.0f;
    void init();
	virtual void onCreate();
	virtual void onRender();
	virtual void onDestroy();
	virtual void onProcessInput(GLFWwindow *window);

};

#endif