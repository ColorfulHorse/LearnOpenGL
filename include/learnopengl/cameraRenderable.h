#ifndef CAMERARENDERABLE_H
#define CAMERARENDERABLE_H

#include <learnopengl/camera.h>
#include <learnopengl/renderable.h>

class CameraRenderable : public Renderable {
public:
	virtual void onCreate() = 0;
	virtual void onRender() {
		super::onRender();
	}
	virtual void onDestroy() = 0;

	/*
	 * 根据键盘输入平移视角
	 */
	virtual void onProcessInput(float deltaTime) {
		// W S A D 前后左右移动摄像机
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			camera.processKeyboard(FORWARD, deltaTime);
		} else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			camera.processKeyboard(BACKWARD, deltaTime);
		} else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			// 叉乘 +X * +Y = +Z  +Y * +X = -Z
			camera.processKeyboard(LEFT, deltaTime);
		} else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			camera.processKeyboard(RIGHT, deltaTime);
		}
	}
	/*
	 * 根据鼠标移动旋转视角
	 */
	void onMouseMoved(double xposIn, double yposIn) {
		float xPos = static_cast<float>(xposIn);
		float yPos = static_cast<float>(yposIn);
		if (firstMove) {
			lastX = xPos;
			lastY = yPos;
			firstMove = false;
		}

		// 灵敏度
		float sensitivity = 0.1f;
		float offsetX = xPos - lastX;
		float offsetY = lastY - yPos;
		lastX = xPos;
		lastY = yPos;
		camera.processMouseMovement(offsetX, offsetY);
	}

	CameraRenderable(GLFWwindow *win) : Renderable(win) {
		
	}

	virtual ~CameraRenderable() {
		
	}

protected:
	Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
	// 鼠标默认点
	float lastX = 400.0f, lastY = 300.0f;
	bool firstMove = true;

private:
	typedef Renderable super;
};
#endif
