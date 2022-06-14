#version 330 core
layout(location = 0) in vec3 mPosition;
layout(location = 1) in vec3 mNormal;
layout(location = 2) in vec2 mTextCoord;

out VS_OUT {
    vec2 textCoord;
    vec3 normal;
    vec3 worldPos;
} vs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    vs_out.worldPos = vec3(model * vec4(mPosition, 1.0));
    vs_out.textCoord = mTextCoord;
    vs_out.normal = mat3(transpose(inverse(model))) * mNormal;
    gl_Position = projection * view * vec4(vs_out.worldPos, 1.0);
}

