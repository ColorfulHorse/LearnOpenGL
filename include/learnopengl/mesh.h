#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdint>
#include <glm/glm.hpp>
#include <learnopengl/shader.h>
#include <string>
#include <vector>

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
};

enum TextureType {
	DIFFUSE = 1,
	SPECULAR,
	REFLECT,
	NORMAL
};

struct Texture {
	uint32_t id;
	TextureType type;
	std::string name;
};

// 网格，模型的一个部分
class Mesh {
private:
	uint32_t VAO, VBO, EBO;
	void setupMesh() {
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), &indices[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, texCoords));

		// 解绑
		glBindVertexArray(0);
	}

public:
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	std::vector<Texture> textures;

	Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices, std::vector<Texture> textures) {
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;
		setupMesh();
	}

	void render(Shader shader) {
		int diffuseIdx = 0;
		int specularIdx = 0;
		int normalIdx = 0;
		int reflectIdx = 0;
		for (size_t i = 0; i < textures.size(); i++) {
			Texture texture = textures[i];
			glActiveTexture(GL_TEXTURE0 + static_cast<GLenum>(i));
			shader.use();
			if (texture.type == DIFFUSE) {
				shader.setInt("material.texture_diffuse" + std::to_string(diffuseIdx++), static_cast<unsigned int>(i));
			} else if (texture.type == SPECULAR) {
				shader.setInt("material.texture_specular" + std::to_string(specularIdx++), static_cast<unsigned int>(i));
			} else if (texture.type == NORMAL) {
				shader.setInt("material.texture_normal" + std::to_string(normalIdx++), static_cast<unsigned int>(i));
			}else if (texture.type == REFLECT) {
				shader.setInt("material.texture_reflect" + std::to_string(reflectIdx++), static_cast<unsigned int>(i));
			}
			glBindTexture(GL_TEXTURE_2D, texture.id);
		}

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
		// 解绑VAO
		glBindVertexArray(0);
		glActiveTexture(GL_TEXTURE0);
	}

	uint32_t getVAO() {
		return VAO;
	}
};

#endif
