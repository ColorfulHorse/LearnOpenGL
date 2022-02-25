#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <glad/glad.h>

class Shader {
public:
	uint32_t id;
	Shader(const GLchar *vertexPath, const GLchar *fragmentPath);
	~Shader();
	void use() const;
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
};

Shader::Shader(const GLchar *vertexPath, const GLchar *fragmentPath) {
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vertexFile;
	std::ifstream fragmentFile;
	vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		vertexFile.open(vertexPath);
		fragmentFile.open(fragmentPath);
		std::stringstream vertexStream, fragmentStream;
		vertexStream << vertexFile.rdbuf();
		fragmentStream << fragmentFile.rdbuf();
		vertexFile.close();
		fragmentFile.close();
		vertexCode = vertexStream.str();
		fragmentCode = fragmentStream.str();
	} catch (const std::iostream::failure &e) {
		std::cout << "ERROR::SHADER::FILE:" << e.what() << std::endl;
	}
	const char *vShaderCode = vertexCode.c_str();
	const char *fShaderCode = fragmentCode.c_str();
	uint32_t vertexShader, fragmentShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// 绑定glsl到着色器对象
	glShaderSource(vertexShader, 1, &vShaderCode, nullptr);
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

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// 绑定glsl到着色器对象
	glShaderSource(fragmentShader, 1, &fShaderCode, nullptr);
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
	id = glCreateProgram();
	// 链接
	glAttachShader(id, vertexShader);
	glAttachShader(id, fragmentShader);
	glLinkProgram(id);
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(id, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM: " << infoLog << std::endl;
		return;
	}
	// 链接后删除
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::use() const {
	glUseProgram(id);
}

void Shader::setBool(const std::string &name, bool value) const {
	glUniform1i(glGetUniformLocation(id, name.c_str()), static_cast<int>(value));
}

void Shader::setInt(const std::string &name, int value) const {
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

Shader::~Shader() {
}