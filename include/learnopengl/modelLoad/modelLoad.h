#ifndef MODELLOAD_H
#define MODELLOAD_H

#include <cstdint>
#include <glm/glm.hpp>
#include <learnopengl/cameraRenderable.h>
#include <learnopengl/model.h>
// #include <learnopengl/model1.h>

class ModelLoad : public CameraRenderable {
public:
	Shader objectShader;
	Shader lightShader;
	glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
	std::unique_ptr<Model> model = nullptr;

	glm::vec3 pointLights[4] = {
		glm::vec3(0.7f, 0.2f, 2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f, 2.0f, -12.0f),
		glm::vec3(0.0f, 0.0f, -3.0f)};
	void init();
	virtual void onCreate();
	virtual void onRender();
	virtual void onDestroy();
	ModelLoad(GLFWwindow *win) :
		CameraRenderable(win) {
	}

private:
	typedef CameraRenderable super;
};

#endif