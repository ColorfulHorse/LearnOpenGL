#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 mNormal;
layout(location = 2) in vec2 aTexCoord;

out vec3 worldPos;
out vec3 normal;
out vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    // 物体的世界坐标，光照计算都在世界坐标进行
    worldPos = vec3(model * vec4(position, 1.0f));
    // 法线矩阵 = 模型矩阵左上角的逆矩阵的转置矩阵
    normal = mat3(transpose(inverse(model))) * mNormal;
    texCoord = aTexCoord;
    gl_Position = projection * view * vec4(worldPos, 1.0f);
}

