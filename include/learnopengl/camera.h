#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdint>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

enum MovementDirection {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class Camera {
public:
	float yaw;
	float pitch;
    float zoom = ZOOM;
	// 相机朝向
	glm::vec3 position;
	glm::vec3 worldUp;
	glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 right = glm::vec3(1.0f);

	Camera(const Camera &camera) {

	}

	Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) :
		position(pos), worldUp(up), yaw(yaw), pitch(pitch) {
		updateCameraVector();
	}

	void processKeyboard(MovementDirection direction, float deltaTime) {
		float velocity = deltaTime * SPEED;
		if (direction == FORWARD)
			position += front * velocity;
		if (direction == BACKWARD)
			position -= front * velocity;
		if (direction == LEFT)
			position -= right * velocity;
		if (direction == RIGHT)
			position += right * velocity;
	}

	void processMouseMovement(float xOffset, float yOffset, bool constrain = true) {
		yaw += xOffset * SENSITIVITY;
		pitch += yOffset * SENSITIVITY;

		if (constrain) {
			if (pitch > 89.0f) {
				pitch = 89.0f;
			} else if (pitch < -89.0f) {
				pitch = -89.0f;
			}
		}
        updateCameraVector();
	}

    void processMouseScroll(float yOffset) {
        zoom -= yOffset;
        if (zoom < 1.0f)
            zoom = 1.0f;
        if (zoom > 45.0f)
            zoom = 45.0f; 
    }

    glm::mat4 getViewMat() {
        return glm::lookAt(position, front + position, up);
    }

	void move(glm::vec3 vec) {
		position += vec;
	}


private:
	void updateCameraVector() {
		front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
		front.y = sin(glm::radians(pitch));
		front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
		front = glm::normalize(front);
		right = glm::normalize(glm::cross(front, worldUp));
		up = glm::normalize(glm::cross(right, front));
	}
};

#endif