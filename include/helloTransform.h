#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "renderable.h"
#include <cstdint>

class HelloTransform : public Renderable {
public:
    uint32_t texture1 = 0, texture2 = 0;
    void initTexture();
	virtual void onCreate();
	virtual void onRender();
	virtual void onDestroy();
};

#endif