#ifndef INSTANCEQUAD_H
#define INSTANCEQUAD_H
#include <learnopengl/cameraRenderable.h>
#include <cstdint>
#include <glm/glm.hpp>
#include <vector>

class InstanceQuad : public CameraRenderable {
public:
	Shader objectShader;
	glm::vec2 translations[100];
    void init();
	virtual void onCreate();
	virtual void onRender();
	virtual void onDestroy();
	InstanceQuad(GLFWwindow *win): CameraRenderable(win){}

private:
	typedef CameraRenderable super;
	uint32_t instanceVBO;
};

#endif