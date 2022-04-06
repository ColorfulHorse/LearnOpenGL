#pragma once
#include "renderable.h"
#include <cstdint>

class HelloTriangle : public Renderable {
public:
	void initTriangle();
	void initMulti();
	virtual void onCreate();
	virtual void onRender();
	virtual void onDestroy();
};