#ifndef GALAXY_H
#define GALAXY_H
#include <cstdint>
#include <glm/glm.hpp>
#include <learnopengl/cameraRenderable.h>
#include <learnopengl/model.h>
#include <vector>

class Galaxy : public CameraRenderable {
public:
	Shader objectShader;
	glm::vec2 translations[100];
	void init();
	virtual void onCreate();
	virtual void onRender();
	virtual void onDestroy();
	Galaxy(GLFWwindow *win) :
		CameraRenderable(win) {
	}

private:
	typedef CameraRenderable super;
	uint32_t instanceVBO;
	int amount = 2000;
	float radius = 50.0f;
	float offset = 2.5f;
	glm::mat4 *matrices = nullptr;
};

#endif