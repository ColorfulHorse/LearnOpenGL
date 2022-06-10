#ifndef UBO_H
#define UBO_H
#include <learnopengl/cameraRenderable.h>
#include <cstdint>
#include <glm/glm.hpp>
#include <vector>

class UBO : public CameraRenderable {
public:
	Shader greenShader, redShader;
	uint32_t ubo;
	std::vector<glm::vec3> boxes {
		glm::vec3(-1.0f, 0.0f, -1.0f),
		glm::vec3(2.0f, 0.0f, 0.0f)
	};
    void init();
	virtual void onCreate();
	virtual void onRender();
	virtual void onDestroy();
	UBO(GLFWwindow *win): CameraRenderable(win){}

private:
	typedef CameraRenderable super;
};

#endif