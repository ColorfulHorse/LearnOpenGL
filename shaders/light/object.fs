#version 330 core

uniform vec3 lightColor;
uniform vec3 objectColor;

out vec4 FragColor;

void main() {
    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * lightColor;
    FragColor = vec4(ambient * objectColor, 1.0f);
}