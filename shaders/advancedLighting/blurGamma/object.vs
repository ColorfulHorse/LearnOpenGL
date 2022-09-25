#version 330 core
layout(location = 0) in vec2 mPosition;
layout(location = 1) in vec3 mColor;


out vec3 fragColor;

void main() {
    fragColor = mColor;
    gl_Position = vec4(mPosition, 0.0, 1.0);
}

