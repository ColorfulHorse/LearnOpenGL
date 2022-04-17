// LearnOpenGL.cpp : Defines the entry point for the application.
//

#include "LearnOpenGL.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "helloTriangle.h"
#include "helloShader.h"
#include "helloTexture.h"
#include "helloTransform.h"
#include "helloCoordinate.h"
#include "helloCamera.h"
#include "helloLight.h"

using namespace std;

Renderable *renderObj = nullptr;

/*
 * 接收键盘输入
 */
void processInput(GLFWwindow *window) {
	// esc键关闭窗口
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if (renderObj) {
		renderObj->onProcessInput();
	}
}

void mouse_callback(GLFWwindow *window, double xPos, double yPos) {
	if (renderObj) {
		renderObj->onMouseMoved(xPos, yPos);
	}
}

int main() {
	// unique_ptr<Renderable> renderObj(new HelloTriangle());
	// unique_ptr<Renderable> renderObj(new HelloShader());
	// unique_ptr<Renderable> renderObj(new HelloTexture());
	// unique_ptr<Renderable> renderObj(new HelloTransform());
	// unique_ptr<Renderable> renderObj(new HelloCoordinate(800, 600));
	// renderObj = new HelloCoordinate(800, 600);
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
	renderObj = new HelloLight(window);
	renderObj->onCreate();
	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		// 设置清屏颜色
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		// 清空缓冲颜色值
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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