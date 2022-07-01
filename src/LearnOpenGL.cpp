// LearnOpenGL.cpp : Defines the entry point for the application.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <learnopengl/LearnOpenGL.h>
#include <learnopengl/basic/helloCamera.h>
#include <learnopengl/basic/helloCoordinate.h>
#include <learnopengl/basic/helloShader.h>
#include <learnopengl/basic/helloTexture.h>
#include <learnopengl/basic/helloTransform.h>
#include <learnopengl/basic/helloTriangle.h>
#include <learnopengl/light/helloLight.h>
#include <learnopengl/light/helloLightTexture.h>
#include <learnopengl/light/helloMaterial.h>
#include <learnopengl/light/helloRealLight.h>
#include <learnopengl/light/multipleLights.h>
#include <type_traits>
#include <learnopengl/utils.h>
#include <learnopengl/modelLoad/modelLoad.h>
#include <learnopengl/advanced/stencilTest.h>
#include <learnopengl/advanced/blending.h>
#include <learnopengl/advanced/cullFace.h>
#include <learnopengl/advanced/framebuffer.h>
#include <learnopengl/advanced/cubemap.h>
#include <learnopengl/advanced/ubo.h>
#include <learnopengl/advanced/geometry.h>
#include <learnopengl/advanced/normalVisualization.h>
#include <learnopengl/advanced/instanceQuad.h>
#include <learnopengl/advanced/galaxy.h>
#include <learnopengl/advanced/antiAliasing.h>
#include <learnopengl/advancedLighting/blinnPhong.h>

using namespace std;

Renderable *renderObj = nullptr;

float deltaTime = 0.0f;
float lastTime = 0.0f;

/*
 * 接收键盘输入
 */
void processInput(GLFWwindow *window) {
	// esc键关闭窗口
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	if (renderObj) {
		auto renderable = dynamic_cast<CameraRenderable *>(renderObj);
		if (renderable) {
			renderable->onProcessInput(deltaTime);
		}
	}
}

void mouse_callback(GLFWwindow *window, double xPos, double yPos) {
	auto renderable = dynamic_cast<CameraRenderable *>(renderObj);
	if (renderable) {
		renderable->onMouseMoved(xPos, yPos);
	}
}


int main() {
	glfwInit();
	// 主次版本
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// 只使用核心集
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow *window = glfwCreateWindow(800, 600, "test", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	// glad 用于初始化opengl函数指针
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}

	glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int width, int height) {
		// viewprot 相当于opengl显示区域，当window大小被改变时它也应该被改变
		glViewport(0, 0, width, height);
	});
	glfwSetCursorPosCallback(window, mouse_callback);

	// renderObj = new HelloCamera(window);
	// renderObj = new HelloLight(window);
	// renderObj = new HelloMaterial(window);
	// renderObj = new HelloLightTexture(window);
	// renderObj = new HelloRealLight(window);
	// renderObj = new MultipleLights(window);
	// renderObj = new ModelLoad(window);
	// renderObj = new StencilTest(window);
	// renderObj = new Blending(window);
	// renderObj = new CullFace(window);
	// renderObj = new FrameBuffer(window);
	// renderObj = new CubeMap(window);
	// renderObj = new UBO(window);
	// renderObj = new Geometry(window);
	// renderObj = new NormalVisualization(window);
	// renderObj = new InstanceQuad(window);
	// renderObj = new Galaxy(window);
	// renderObj = new AntiAliasing(window);
	renderObj = new BlinnPhong(window);
	renderObj->onCreate();
	while (!glfwWindowShouldClose(window)) {
		float currentTime = (float)glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;
		processInput(window);
		
		renderObj->onRender();
		// 双缓冲，交换缓冲
		glfwSwapBuffers(window);

		// 检查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，并调用对应的回调函数
		glfwPollEvents();
	}
	renderObj->onDestroy();
	delete renderObj;
	renderObj = nullptr;
	glfwTerminate();
	return 0;
}