#include <learnopengl/basic/helloShader.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

void HelloShader::dynamicColor() {
	const char *vertexShaderSource = "#version 330 core\n"
									 "layout (location = 0) in vec3 aPos;\n"
									 "void main()\n"
									 "{\n"
									 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
									 "}\0";
	const char *fragmentShaderSource = "#version 330 core\n"
									   "out vec4 FragColor;\n"
									   "uniform vec4 globalColor;\n"
									   "void main()\n"
									   "{\n"
									   "   FragColor = globalColor;\n"
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

void HelloShader::multiColor() {
	const char *vertexShaderSource = "#version 330 core\n"
									 "layout (location = 0) in vec3 aPos;\n"
									 "layout (location = 1) in vec3 aColor;\n"
									 "out vec3 finalColor;\n"
									 "void main()\n"
									 "{\n"
									 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
									 "   finalColor = aColor;\n"
									 "}\0";
	const char *fragmentShaderSource = "#version 330 core\n"
									   "out vec4 FragColor;\n"
									   "in vec3 finalColor;\n"
									   "void main()\n"
									   "{\n"
									   "   FragColor = vec4(finalColor, 1.0);\n"
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
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f};

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

	// 位置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	// 颜色属性   一组6个float，前三个代表顶点位置，后三个代表rgb
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void HelloShader::onCreate() {
	multiColor();
}

void HelloShader::onRender() {
	glUseProgram(shaderProgram);

	// 更新全局颜色
	float time = glfwGetTime();
	float greenValue = sin(time) / 2.0f + 0.5f;
	int32_t colorLocation = glGetUniformLocation(shaderProgram, "globalColor");
	glUniform4f(colorLocation, 0.0f, greenValue, 0.0f, 1.0f);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	// 参数3:索引数据类型
	// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void HelloShader::onDestroy() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
}
