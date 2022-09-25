#version 330 core
layout(location = 0) in vec3 mPosition;
layout(location = 1) in vec3 mNormal;
layout(location = 2) in vec2 mTexCoord;

out VS_OUT {
    vec3 mFragPos;
    vec3 mNormal;
    vec2 mTexCoords;
} vs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    vs_out.mFragPos = vec3(model * vec4(mPosition, 1.0));
    // 法线矩阵 = 模型矩阵左上角的逆矩阵的转置矩阵
    vs_out.mNormal = mat3(transpose(inverse(model))) * mNormal;
    vs_out.mTexCoords = mTexCoord;
    gl_Position = projection * view * vec4(vs_out.mFragPos, 1.0);
}

