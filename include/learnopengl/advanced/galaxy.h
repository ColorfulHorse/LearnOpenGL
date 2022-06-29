#ifndef GALAXY_H
#define GALAXY_H
#include <cstdint>
#include <glm/glm.hpp>
#include <learnopengl/cameraRenderable.h>
#include <learnopengl/model.h>
#include <vector>
#include <learnopengl/model.h>

class Galaxy : public CameraRenderable {
public:
	std::unique_ptr<Model> rock = nullptr;
	std::unique_ptr<Model> planet = nullptr;
	Shader rockShader;
	Shader planetShader;
	void init();
	virtual void onCreate();
	virtual void onRender();
	virtual void onDestroy();
	Galaxy(GLFWwindow *win) :
		CameraRenderable(win) {
	}

private:
	typedef CameraRenderable super;
	uint32_t instanceVBO;
	int amount = 20000;
	float radius = 60.0f;
	float offset = 10.0f;
	glm::mat4 *matrices = nullptr;
};

#endif