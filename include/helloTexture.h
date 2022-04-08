#pragma once
#include "renderable.h"
#include <cstdint>

class HelloTexture : public Renderable {
public:
	uint32_t texture1 = 0, texture2 = 0;
	HelloTexture(GLFWwindow *win): Renderable(win){}
	void initTexture();
	virtual void onCreate();
	virtual void onRender();
	virtual void onDestroy();
};