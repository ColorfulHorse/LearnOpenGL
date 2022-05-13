#ifndef HELLOLIGHT_H
#define HELLOLIGHT_H
#include <learnopengl/cameraRenderable.h>
#include <cstdint>
#include <glm/glm.hpp>

class HelloLight : public CameraRenderable {
public:
	uint32_t VBO, lightVAO, objectVAO;
	Shader objectShader;
	Shader lightShader;
	glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
    void init();
	virtual void onCreate();
	virtual void onRender();
	virtual void onDestroy();
	HelloLight(GLFWwindow *win): CameraRenderable(win){}
};

#endif