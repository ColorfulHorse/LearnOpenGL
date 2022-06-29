#version 330 core

in vec2 texCoord;

out vec4 FragColor;

struct Material {
    sampler2D texture_diffuse0;
    sampler2D texture_specular0;
    sampler2D texture_reflect0;
    float shininess;
};

uniform Material material;

void main() {
    vec3 diffuse = texture(material.texture_diffuse0, texCoord).rgb;
    FragColor = vec4(diffuse, 1.0);
}