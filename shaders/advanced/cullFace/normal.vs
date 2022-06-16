#version 330 core
layout(location = 0) in vec3 position;


uniform mat4 model;

void main() {
    // 这里先不乘投影矩阵，因为要先在观察空间计算法向量可视化
    gl_Position = view * model * vec4(position, 1.0);
}

