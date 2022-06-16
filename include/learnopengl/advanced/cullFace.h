#ifndef CULLFACE_H
#define CULLFACE_H
#include <learnopengl/cameraRenderable.h>
#include <cstdint>
#include <glm/glm.hpp>

// 面剔除
class CullFace : public CameraRenderable {
public:
	uint32_t texture;
	Shader normalShader;
    void init();
	virtual void onCreate();
	virtual void onRender();
	virtual void onDestroy();
	CullFace(GLFWwindow *win): CameraRenderable(win){}

private:
	typedef CameraRenderable super;
};

#endif