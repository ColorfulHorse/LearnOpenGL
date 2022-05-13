#version 330 core
layout(location = 0) in vec3 mPosition;
layout(location = 1) in vec3 mNormal;
layout(location = 2) in vec2 mTexCoord;

out vec3 normal;
out vec3 worldPos;
out vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    worldPos = vec3(model * vec4(mPosition, 1.0));
    // 法线矩阵 = 模型矩阵左上角的逆矩阵的转置矩阵
    normal = mat3(transpose(inverse(model))) * mNormal;
    texCoord = mTexCoord;
    gl_Position = projection * view * model * vec4(worldPos, 1.0);
}

