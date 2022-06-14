#version 330 core
layout(location = 0) in vec3 mPosition;
layout(location = 1) in vec3 mNormal;

out VS_OUT {
    vec3 normal;
} vs_out;

uniform mat4 model;
uniform mat4 view;

void main() {
    // 变换法线到观察空间
    vs_out.normal = mat3(transpose(inverse(view * model))) * mNormal;
    // 这里先不乘投影矩阵，因为要先在观察空间计算法向量可视化
    gl_Position = view * model * vec4(mPosition, 1.0);
}

