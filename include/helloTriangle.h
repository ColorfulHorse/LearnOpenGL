#pragma once
#ifndef HELLOTRIANGLE_H
#define HELLOTRIANGLE_H

#include "renderable.h"
#include <cstdint>

class HelloTriangle : public Renderable {
public:
	HelloTriangle(GLFWwindow *win): Renderable(win){}
	void initTriangle();
	void initMulti();
	virtual void onCreate();
	virtual void onRender();
	virtual void onDestroy();
};

#endif