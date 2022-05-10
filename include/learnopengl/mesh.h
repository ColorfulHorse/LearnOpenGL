#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include <cstdint>
#include <vector>
#include <learnopengl/shader.h>

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 texCoords;
};

struct Texture {
	uint32_t id;
	std::string type;
};

// 网格，模型的一个部分
class Mesh {
private:
	uint32_t VAO, VBO, EBO;
    void setupMesh();

public:
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices; 
    std::vector<Texture> textures;

    Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices, std::vector<Texture> textures);

    void render(Shader shader);
};

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices, std::vector<Texture> textures) {
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
}

void Mesh::setupMesh() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
}

void Mesh::render(Shader Shader) {
    
}

#endif
