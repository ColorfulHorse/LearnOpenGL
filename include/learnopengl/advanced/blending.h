#ifndef BLENDING_H
#define BLENDING_H
#include <learnopengl/cameraRenderable.h>
#include <cstdint>
#include <glm/glm.hpp>
#include <vector>

class Blending : public CameraRenderable {
public:
	uint32_t containerVBO, floorVBO, grassVBO, containerVAO, floorVAO, grassVAO;
	uint32_t floorTexture, containerTexture, grassTexture;
	Shader objectShader;
	std::vector<glm::vec3> boxes {
		glm::vec3(-1.0f, 0.0f, -1.0f),
		glm::vec3(2.0f, 0.0f, 0.0f)
	};
	std::vector<glm::vec3> grasses {
		// 让草在箱子表面
		glm::vec3(-1.0f, 0.0f, -0.49f),
		glm::vec3(2.0f, 0.0f, 0.51f),
		glm::vec3(0.5f, 0.0f, 1.0f)
	};
    void init();
	virtual void onCreate();
	virtual void onRender();
	virtual void onDestroy();
	Blending(GLFWwindow *win): CameraRenderable(win){}
};

#endif