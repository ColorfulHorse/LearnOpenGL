#pragma once
#ifndef HELLOSHADER_H
#define HELLOSHADER_H

#include <learnopengl/renderable.h>
#include <cstdint>

class HelloShader : public Renderable {
public:
	HelloShader(GLFWwindow *win): Renderable(win){}
	void dynamicColor();
	void multiColor();
	virtual void onCreate();
	virtual void onRender();
	virtual void onDestroy();

private:
	typedef Renderable super;
};
#endif