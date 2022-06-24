#version 330 core
layout(location = 0) in vec2 mPosition;
layout(location = 1) in vec3 mColor;
layout(location = 2) in vec2 mOffset;

out vec3 fColor;

void main() {
    fColor = mColor;
    vec2 pos = mPosition * (gl_InstanceID / 100.0);
    gl_Position = vec4(pos + mOffset, 0.0, 1.0);
}