#version 330 core
out vec4 FragColor;

in vec3 finalColor;
in vec2 texCoord;

uniform sampler2D finalTexture;

void main() {
    FragColor = texture(finalTexture, texCoord);
}