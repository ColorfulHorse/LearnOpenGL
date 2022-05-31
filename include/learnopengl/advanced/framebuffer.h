#ifndef CULLFACE_H
#define CULLFACE_H
#include <learnopengl/cameraRenderable.h>
#include <cstdint>
#include <glm/glm.hpp>

// 面剔除
class FrameBuffer : public CameraRenderable {
public:
	uint32_t fbo, rbo;
	uint32_t textureColorBuffer;
    void init();
	virtual void onCreate();
	virtual void onRender();
	virtual void onDestroy();
	FrameBuffer(GLFWwindow *win): CameraRenderable(win){}
};

#endif