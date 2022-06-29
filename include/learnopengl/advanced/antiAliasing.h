#ifndef ANTIALIASING_H
#define ANTIALIASING_H
#include <learnopengl/cameraRenderable.h>
#include <cstdint>
#include <glm/glm.hpp>
#include <vector>

// 面剔除
class AntiAliasing : public CameraRenderable {
public:
	uint32_t fbo, rbo, intermediateFbo;
	uint32_t textureMsaa, textureScreen;
    void init();
	virtual void onCreate();
	virtual void onRender();
	virtual void onDestroy();
	AntiAliasing(GLFWwindow *win): CameraRenderable(win){}

private:
	typedef CameraRenderable super;
	uint32_t screenVAO, screenVBO;
	Shader screenShader;
};

#endif