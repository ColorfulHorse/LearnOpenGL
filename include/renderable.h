#pragma once
#include <cstdint>
class Renderable {
public:
	virtual void onCreate() = 0;
	virtual void onRender() = 0;
	virtual void onDestroy() = 0;
protected:
	uint32_t VBO = 0, VAO = 0, EBO = 0;
	uint32_t shaderProgram = 0;
};
