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
	std::vector<Texture> texture_loaded;
	std::vector<Mesh> meshes;
	std::string dictionary;
	void loadModel(std::string path) {
		Assimp::Importer importer;
		// aiProcess_Triangulate 模型不是全为三角形组成就把图元全部转换为三角形
		// aiProcess_FlipUVs翻转纹理Y坐标
		// aiProcess_GenNormals：如果模型不包含法向量的话，就为每个顶点创建法线。
		// aiProcess_SplitLargeMeshes：将比较大的网格分割成更小的子网格，如果你的渲染有最大顶点数限制，只能渲染较小的网格，那么它会非常有用。
		// aiProcess_OptimizeMeshes：和上个选项相反，它会将多个小网格拼接为一个大的网格，减少绘制调用从而进行优化。
		const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
			std::cout << "loadModel error:" << importer.GetErrorString() << std::endl;
			return;
		}
		dictionary = path.substr(0, path.find_last_of("/"));
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
				texCoords.y = mesh->mTextureCoords[0][i].x;
			}
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
			std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, DIFFUSE);
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
			std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, SPECULAR);
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		}
	}

	// 纹理
	std::vector<Texture> loadMaterialTextures(aiMaterial *material, aiTextureType aiType, TextureType type) {
		std::vector<Texture> textures;
		for (size_t i = 0; i < material->GetTextureCount(aiType); i++) {
			aiString name;
			std::string a("xxx");
			std::string b("xxx");
			auto c = a == b;
			material->GetTexture(aiType, i, &name);
			auto iter = find_if(texture_loaded.begin(), texture_loaded.end(), [=](Texture &texture) -> bool {
				return texture.name == name.C_Str();
			});
			if (iter != texture_loaded.end()) {
				
			}

			Texture texture;
			texture.id = textureFromFile(name.C_Str(), dictionary);
			texture.type = type;
			texture.name = name.C_Str();
			textures.push_back(texture);
		}
		return textures;
	}

public:
	Model(std::string path) {
		loadModel(path);
	}

	void render(Shader shader) {
		for (auto iter = meshes.begin(); iter != meshes.end(); iter++) {
			iter->render(shader);
		}
	}
};

#endif
