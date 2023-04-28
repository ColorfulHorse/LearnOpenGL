#ifndef SHADOW_MAPPING_H
#define SHADOW_MAPPING_H

#include <cstdint>
#include <learnopengl/cameraRenderable.h>

class ShadowMapping : public CameraRenderable {
public:
	void init();
	virtual void onCreate();
	virtual void onRender();
	virtual void onDestroy();
	virtual void onProcessInput(float deltaTime);
	ShadowMapping(GLFWwindow *win) :
		CameraRenderable(win) {
	}

	virtual ~ShadowMapping() {

	}

private:
	typedef CameraRenderable super;
	Shader depthShader;
	Shader lightShader;
    GLuint depthFBO;
    GLuint depthTexture;
	GLuint planeTexture;
	GLuint boxTexture;
    glm::vec3 lightPos = glm::vec3(-2.0f, 4.0f, -1.0f);
    glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 10.5f);

    GLuint planeVAO, planeVBO;
	GLuint quadVAO = 0;
	GLuint quadVBO;
	GLuint cubeVAO = 0;
	GLuint cubeVBO = 0;
    void renderScene(Shader &shader);
    void renderCube();
};

#endif