#pragma once
#include "renderable.h"
#include <cstdint>

class HelloShader : public Renderable {
public:
	void dynamicColor();
	void multiColor();
	virtual void onCreate();
	virtual void onRender();
	virtual void onDestroy();
};