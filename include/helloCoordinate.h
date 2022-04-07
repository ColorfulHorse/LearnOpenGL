#ifndef COORDINATE_H
#define COORDINATE_H
#include "renderable.h"
#include <cstdint>

class HelloCoordinate : public Renderable {
public:
    uint32_t texture1 = 0, texture2 = 0;
	uint32_t screenWidth, screenHeight;
	glm::vec3 cubePositions[10] = {
		glm::vec3(0.0f,  0.0f, 0.0f), 
		glm::vec3(2.0f,  5.0f, -15.0f), 
		glm::vec3(-1.5f, -2.2f, -2.5f),  
		glm::vec3(-3.8f, -2.0f, -12.3f),  
		glm::vec3( 2.4f, -0.4f, -3.5f),  
		glm::vec3(-1.7f,  3.0f, -7.5f),  
		glm::vec3( 1.3f, -2.0f, -2.5f),  
		glm::vec3( 1.5f,  2.0f, -2.5f), 
		glm::vec3( 1.5f,  0.2f, -1.5f), 
		glm::vec3(-1.3f,  1.0f, -1.5f)  
	};
    void init();
	void drawMulti();
	virtual void onCreate();
	virtual void onRender();
	virtual void onDestroy();
	HelloCoordinate(uint32_t w, uint32_t h):screenWidth(w), screenHeight(h) {}
};

#endif