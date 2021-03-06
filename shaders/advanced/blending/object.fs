#version 330 core

in vec2 texCoords;

// out vec4 FragColor;

uniform sampler2D tex;

out vec4 FragColor;

void main() {
    vec4 texColor = texture(tex, texCoords);
    FragColor = texColor;
}