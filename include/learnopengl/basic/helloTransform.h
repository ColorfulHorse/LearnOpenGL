#ifndef TRANSFORM_H
#define TRANSFORM_H
#include <learnopengl/renderable.h>
#include <cstdint>

class HelloTransform : public Renderable {
public:
    uint32_t texture1 = 0, texture2 = 0;
	HelloTransform(GLFWwindow *win): Renderable(win){}
    void initTexture();
	virtual void onCreate();
	virtual void onRender();
	virtual void onDestroy();

private:
	typedef Renderable super;
};

#endif