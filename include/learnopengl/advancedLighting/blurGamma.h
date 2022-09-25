#ifndef BLUR_GAMMA_H
#define BLUR_GAMMA_H
#include <learnopengl/cameraRenderable.h>
#include <cstdint>
#include <glm/glm.hpp>
#include <vector>

// 面剔除
class BlurGamma : public CameraRenderable {
public:
	Shader screenShader;
	uint32_t fbo, rbo;
	uint32_t textureColorBuffer;
	uint32_t containerVBO, floorVBO, rectVBO, containerVAO, floorVAO, rectVAO;
	uint32_t floorTexture, containerTexture;
	uint32_t normalTexture, gammaTexture;
	Shader objectShader;
	bool gamma = false;
	bool pressed = false;
	int smallWidth = 100, smallHeight = 75;
	std::vector<glm::vec3> boxes {
		glm::vec3(-1.0f, 0.0f, -1.0f),
		glm::vec3(2.0f, 0.0f, 0.0f)
	};
    void init();
	virtual void onCreate();
	virtual void onRender();
	virtual void onDestroy();
	virtual void onProcessInput(float deltaTime);
	BlurGamma(GLFWwindow *win): CameraRenderable(win){}

private:
	typedef CameraRenderable super;
};

#endif