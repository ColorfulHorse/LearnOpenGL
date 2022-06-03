#ifndef HELLOMATERIAL_H
#define HELLOMATERIAL_H
#include <learnopengl/cameraRenderable.h>
#include <cstdint>
#include <glm/glm.hpp>

class HelloMaterial : public CameraRenderable {
public:
	uint32_t VBO, lightVAO, objectVAO;
	Shader objectShader;
	Shader lightShader;
	glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
    void init();
	virtual void onCreate();
	virtual void onRender();
	virtual void onDestroy();
	HelloMaterial(GLFWwindow *win): CameraRenderable(win){}

private:
	typedef CameraRenderable super;
};


#endif