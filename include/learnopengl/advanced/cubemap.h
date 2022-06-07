#ifndef CUBEMAP_H
#define CUBEMAP_H
#include <learnopengl/cameraRenderable.h>
#include <cstdint>
#include <glm/glm.hpp>
#include <vector>
#include <learnopengl/model.h>

// 面剔除
class CubeMap : public CameraRenderable {
public:
	Shader skyboxShader, objectShader;
	uint32_t fbo, rbo;
	uint32_t skyboxTexture, containerTexture;
	uint32_t objectVBO, skyboxVBO, objectVAO, skyboxVAO;
	int smallWidth = 100, smallHeight = 75;
	std::unique_ptr<Model> model = nullptr;
	std::vector<glm::vec3> boxes {
		glm::vec3(-1.0f, 0.0f, -1.0f),
		glm::vec3(2.0f, 0.0f, 0.0f)
	};
	std::vector<std::string> faces = {
		FileSystem::getPath("assets/texture/skybox/right.jpg"),
        FileSystem::getPath("assets/texture/skybox/left.jpg"),
        FileSystem::getPath("assets/texture/skybox/top.jpg"),
        FileSystem::getPath("assets/texture/skybox/bottom.jpg"),
        FileSystem::getPath("assets/texture/skybox/front.jpg"),
        FileSystem::getPath("assets/texture/skybox/back.jpg")
	};
    void init();
	virtual void onCreate();
	virtual void onRender();
	virtual void onDestroy();
	CubeMap(GLFWwindow *win): CameraRenderable(win){}

private:
	typedef CameraRenderable super;
};

#endif