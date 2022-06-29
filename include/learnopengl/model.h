#ifndef MODEL_H
#define MODEL_H

#include <algorithm>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <iostream>
#include <learnopengl/mesh.h>
#include <learnopengl/shader.h>
#include <learnopengl/utils.h>
#include <string>
#include <vector>

// 模型类
class Model {
private:
	std::string directory;
	void loadModel(std::string path) {
		Assimp::Importer importer;
		// aiProcess_Triangulate 模型不是全为三角形组成就把图元全部转换为三角形
		// aiProcess_FlipUVs翻转纹理Y坐标
		// aiProcess_GenNormals：如果模型不包含法向量的话，就为每个顶点创建法线。
		// aiProcess_SplitLargeMeshes：将比较大的网格分割成更小的子网格，如果你的渲染有最大顶点数限制，只能渲染较小的网格，那么它会非常有用。
		// aiProcess_OptimizeMeshes：和上个选项相反，它会将多个小网格拼接为一个大的网格，减少绘制调用从而进行优化。
		unsigned int flag = aiProcess_Triangulate;
		std::string::size_type pos = path.find_last_of(".");
		std::string suffix = path.substr(pos + 1, path.length() - pos);
		if (suffix == "obj") {
			flag |= aiProcess_FlipUVs;
		}
		const aiScene *scene = importer.ReadFile(path, flag);
	
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
			std::cout << "loadModel error:" << importer.GetErrorString() << std::endl;
			return;
		}
		directory = path.substr(0, path.find_last_of("/"));
		processNode(scene->mRootNode, scene);
	}

	void processNode(aiNode *node, const aiScene *scene) {
		for (size_t i = 0; i < node->mNumMeshes; i++) {
			// node->mMeshes存放的是mesh在scene中的下标
			aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
			meshes.push_back(processMesh(mesh, scene));
		}
		for (size_t i = 0; i < node->mNumChildren; i++) {
			processNode(node->mChildren[i], scene);
		}
	}

	Mesh processMesh(aiMesh *mesh, const aiScene *scene) {
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
		std::vector<Texture> textures;

		for (size_t i = 0; i < mesh->mNumVertices; i++) {
			Vertex vertex;
			glm::vec3 vec;
			// 顶点坐标
			vec.x = mesh->mVertices[i].x;
			vec.y = mesh->mVertices[i].y;
			vec.z = mesh->mVertices[i].z;
			vertex.position = vec;

			// 顶点法线
			if (mesh->HasNormals()) {
				vec.x = mesh->mNormals[i].x;
				vec.y = mesh->mNormals[i].y;
				vec.z = mesh->mNormals[i].z;
				vertex.normal = vec;
			}

			// 顶点纹理坐标
			if (mesh->HasTextureCoords(0)) {
				glm::vec2 texCoords;
				texCoords.x = mesh->mTextureCoords[0][i].x;
				texCoords.y = mesh->mTextureCoords[0][i].y;
				vertex.texCoords = texCoords;
			} else {
				vertex.texCoords = glm::vec2(0.0f, 0.0f);
			}
			vertices.push_back(vertex);
		}

		for (size_t i = 0; i < mesh->mNumFaces; i++) {
			// 一个face表示一个图元，这里是三角面
			aiFace face = mesh->mFaces[i];
			for (size_t j = 0; j < face.mNumIndices; j++) {
				indices.push_back(face.mIndices[j]);
			}
		}
		if (mesh->mMaterialIndex >= 0) {
			aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
			std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, DIFFUSE, scene);
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
			std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, SPECULAR, scene);
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
			std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, NORMAL, scene);
			textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
			std::vector<Texture> reflectMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, REFLECT, scene);
			textures.insert(textures.end(), reflectMaps.begin(), reflectMaps.end());
		}
		return Mesh(vertices, indices, textures);
	}

	// 纹理
	std::vector<Texture> loadMaterialTextures(aiMaterial *material, aiTextureType aiType, TextureType type, const aiScene *scene) {
		std::vector<Texture> textures;
		unsigned int count = material->GetTextureCount(aiType);
		for (size_t i = 0; i < count; i++) {
			aiString name;
			material->GetTexture(aiType, static_cast<GLenum>(i), &name);
			// 复用
			auto iter = find_if(texture_loaded.begin(), texture_loaded.end(), [name](Texture &texture) {
				return texture.name == name.C_Str();
			});
			if (iter != texture_loaded.end()) {
				textures.push_back(*iter);
				continue;
			}
			Texture texture;
			const aiTexture *tex = scene->GetEmbeddedTexture(name.C_Str());
			if (tex) {
				texture.id = textureFromEmbedded(tex);
			} else {
				texture.id = textureFromFile(name.C_Str(), directory);
			}

			texture.type = type;
			texture.name = name.C_Str();
			textures.push_back(texture);
			texture_loaded.push_back(texture);
		}
		return textures;
	}

	uint32_t textureFromEmbedded(const aiTexture *tex) {
		uint32_t textureId;
		glGenTextures(1, &textureId);
		int32_t width, height, channels;
		stbi_uc *data = nullptr;
		if (tex->mHeight == 0) {
			data = stbi_load_from_memory(reinterpret_cast<stbi_uc *>(tex->pcData), tex->mWidth, &width, &height, &channels, 4);
		} else {
			data = stbi_load_from_memory(reinterpret_cast<stbi_uc *>(tex->pcData), tex->mWidth, &width, &height, &channels, 4);
		}

		GLenum format;
		if (channels == 1)
			format = GL_RED;
		else if (channels == 3)
			format = GL_RGB;
		else if (channels == 4)
			format = GL_RGBA;

		if (data) {
			glBindTexture(GL_TEXTURE_2D, textureId);
			// 根据图片创建纹理
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			// 创建多级渐远纹理
			glGenerateMipmap(GL_TEXTURE_2D);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		} else {
			std::cout << "Failed to load embedded texture" << tex->mFilename.C_Str() << std::endl;
		}
		stbi_image_free(data);
		return textureId;
	}

public:
	std::vector<Mesh> meshes;
	std::vector<Texture> texture_loaded;
	Model(std::string path) {
		loadModel(path);
	}

	void render(Shader &shader) {
		for (auto iter = meshes.begin(); iter != meshes.end(); iter++) {
			iter->render(shader);
		}
	}
};

#endif
