#ifndef MESH_H
#define MESH_H

#include <GLFW/glfw3.h>
#include <cstdint>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <learnopengl/shader.h>
#include <string>
#include <vector>

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
};

enum TextureType{
    DIFFUSE = 1,
    SPECULAR
};

struct Texture {
	uint32_t id;
	TextureType type;
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

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), &indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, texCoords));
	glEnableVertexAttribArray(0);

	// 解绑
	glBindVertexArray(0);
}

void Mesh::render(Shader shader) {
	for (size_t i = 0; i < textures.size(); i++) {
        Texture texture = textures[i];
		glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, texture.id);
        shader.use();
        if (texture.type == DIFFUSE) {
            shader.setFloat("material.texture_diffuse" + std::to_string(i), i);
        } else {
            shader.setFloat("material.texture_specular" + std::to_string(i), i);
        }
	}
    glActiveTexture(GL_TEXTURE0);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    // 解绑VAO
    glBindVertexArray(VAO);
}

#endif
