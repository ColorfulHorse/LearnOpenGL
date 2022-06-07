#version 330 core

// 代表3D纹理坐标的方向向量
in vec3 texCoords;

uniform samplerCube tex;

out vec4 FragColor;

void main() {
    vec4 texColor = texture(tex, texCoords);
    FragColor = texColor;
}