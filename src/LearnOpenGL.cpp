// LearnOpenGL.cpp : Defines the entry point for the application.
//

#include "LearnOpenGL.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;


void processInput(GLFWwindow* window) {
	// esc键关闭窗口
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

int main()
{
	glfwInit();
	// 主次版本
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// 只使用核心集
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "test", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	// glad 用于初始化opengl函数指针
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
		// viewprot 相当于opengl显示区域，当window大小被改变时它也应该被改变
		glViewport(0, 0, width, height);
	});
	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		// 设置清屏颜色
		glClearColor(0.2f, 0.3f, 0.2f, 1.0f);
		// 清空缓冲颜色值
		glClear(GL_COLOR_BUFFER_BIT);
		// 双缓冲，交换缓冲
		glfwSwapBuffers(window);
		// 检查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，并调用对应的回调函数
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}

//void onWindowSizeChanged(GLFWwindow* window, int width, int height) {
//	// viewprot 相当于opengl显示区域，当window大小被改变时它也应该被改变
//	glViewport(0, 0, width, height);
//}
