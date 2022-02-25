#version 330 core
out vec4 FragColor;

in vec3 finalColor;
in vec2 textCoord;

uniform sampler2D finalTexture;

void main() {
    FragColor = texture(finalTexture, textCoord);
}