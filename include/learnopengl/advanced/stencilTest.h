#ifndef STENCILTEST_H
#define STENCILTEST_H
#include <learnopengl/cameraRenderable.h>
#include <cstdint>
#include <glm/glm.hpp>

class StencilTest : public CameraRenderable {
public:
	uint32_t containerVBO, floorVBO, containerVAO, floorVAO;
	uint32_t floorTexture, containerTexture;
	Shader objectShader;
	Shader borderShader;
    void init();
	virtual void onCreate();
	virtual void onRender();
	virtual void onDestroy();
	StencilTest(GLFWwindow *win): CameraRenderable(win){}

private:
	typedef CameraRenderable super;
};

#endif