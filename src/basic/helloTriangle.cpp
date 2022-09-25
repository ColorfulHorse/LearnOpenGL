#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <learnopengl/basic/helloTriangle.h>

using namespace std;

/*
  单个三角形
 */
void HelloTriangle::initTriangle() {
	const char *vertexShaderSource = "#version 330 core\n"
									 "layout (location = 0) in vec3 aPos;\n"
									 "void main()\n"
									 "{\n"
									 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
									 "}\0";
	const char *fragmentShaderSource = "#version 330 core\n"
									   "out vec4 FragColor;\n"
									   "void main()\n"
									   "{\n"
									   "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
									   "}\n\0";

	// 创建顶点着色器
	uint32_t vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// 绑定glsl到着色器对象
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	// 编译着色器
	glCompileShader(vertexShader);
	int32_t success;
	char infoLog[512];
	// 获取着色器状态
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::VERTEX: " << infoLog << std::endl;
		return;
	}

	// 创建片段着色器
	uint32_t fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// 绑定glsl到着色器对象
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	// 编译着色器
	glCompileShader(fragmentShader);
	// 获取着色器状态
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT: " << infoLog << std::endl;
		return;
	}

	// 着色器程序，用于链接多个着色器
	shaderProgram = glCreateProgram();
	// 链接
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM: " << infoLog << std::endl;
		return;
	}

	// 链接后删除
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// 三个顶点x,y,z
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f};

	// 创建顶点数组对象，VAO用于管理多个VBO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// 创建顶点缓冲对象
	glGenBuffers(1, &VBO);
	// 绑定数组类型缓冲
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// 顶点数据送入缓冲
	// GL_STATIC_DRAW ：数据不会或几乎不会改变。
	// GL_DYNAMIC_DRAW：数据会被改变很多。
	// GL_STREAM_DRAW ：数据每次绘制时都会改变。
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 链接顶点属性
	// 如何读取顶点数据，最后参数为偏移量
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

/*
  多个三角形
 */
void HelloTriangle::initMulti() {
	const char *vertexShaderSource = "#version 330 core\n"
									 "layout (location = 0) in vec3 aPos;\n"
									 "out vec4 vertexColor;\n"
									 "void main()\n"
									 "{\n"
									 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
									 "   vertexColor = vec4(0.2, 0.2, 0.2, 0.0);\n"
									 "}\0";
	const char *fragmentShaderSource = "#version 330 core\n"
									   "out vec4 FragColor;\n"
									   "in vec4 vertexColor;\n"
									   "void main()\n"
									   "{\n"
									   "   vec3 res = pow(vec3(vertexColor), vec3(1.0/2.2)); \n"
									   "   FragColor = vec4(res, 1.0);\n"
									   "}\n\0";

	// 创建顶点着色器
	uint32_t vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// 绑定glsl到着色器对象
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	// 编译着色器
	glCompileShader(vertexShader);
	int32_t success;
	char infoLog[512];
	// 获取着色器状态
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::VERTEX: " << infoLog << std::endl;
		return;
	}

	// 创建片段着色器
	uint32_t fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// 绑定glsl到着色器对象
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	// 编译着色器
	glCompileShader(fragmentShader);
	// 获取着色器状态
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT: " << infoLog << std::endl;
		return;
	}

	// 着色器程序，用于链接多个着色器
	shaderProgram = glCreateProgram();
	// 链接
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM: " << infoLog << std::endl;
		return;
	}

	// 链接后删除
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // 左下角
		-0.5f, 0.5f, 0.0f,	// 左上角

		0.5f, 0.5f, 0.0f,  // 右上角
		0.5f, -0.5f, 0.0f, // 右下角
	};

	/* float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f,
	}; */
	// 两组连接三个点构成两个三角形
	uint32_t indices[] = {
		0, 1, 3,
		1, 2, 3};

	// 创建顶点数组对象，VAO用于管理多个VBO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// 创建顶点缓冲对象
	glGenBuffers(1, &VBO);
	// 绑定数组类型缓冲
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// 顶点数据送入缓冲
	// GL_STATIC_DRAW ：数据不会或几乎不会改变。
	// GL_DYNAMIC_DRAW：数据会被改变很多。
	// GL_STREAM_DRAW ：数据每次绘制时都会改变。
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 创建并绑定顶点索引数组
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 链接顶点属性
	// 如何读取顶点数据，最后参数为偏移量
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// 线框模式
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void HelloTriangle::onCreate() {
	initMulti();
}

void HelloTriangle::onRender() {
    super::onRender();
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);

	// glDrawArrays(GL_TRIANGLES, 0, 3);
	// 参数3:索引数据类型
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void HelloTriangle::onDestroy() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
}