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
	Shader skyboxShader;
	uint32_t skyboxTexture;
	uint32_t skyboxVBO, skyboxVAO;
	glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
	std::unique_ptr<Model> model = nullptr;
	std::vector<std::string> faces = {
		FileSystem::getPath("assets/texture/skybox/right.jpg"),
        FileSystem::getPath("assets/texture/skybox/left.jpg"),
        FileSystem::getPath("assets/texture/skybox/top.jpg"),
        FileSystem::getPath("assets/texture/skybox/bottom.jpg"),
        FileSystem::getPath("assets/texture/skybox/front.jpg"),
        FileSystem::getPath("assets/texture/skybox/back.jpg")
	};
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