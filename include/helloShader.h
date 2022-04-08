#pragma once
#include "renderable.h"
#include <cstdint>

class HelloShader : public Renderable {
public:
	HelloShader(GLFWwindow *win): Renderable(win){}
	void dynamicColor();
	void multiColor();
	virtual void onCreate();
	virtual void onRender();
	virtual void onDestroy();
};