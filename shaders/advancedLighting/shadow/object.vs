#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 textCoords;

out VS_OUT {
    vec3 fragPos;
    vec3 mNormal;
    vec2 mTexCoords;
    vec4 fragPosLightSpace;
} vs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 lightTransfer;

void main()
{
    vs_out.fragPos = vec3(model * vec4(position, 1.0));
    vs_out.mNormal = transpose(inverse(mat3(model))) * normal;
    vs_out.mTexCoords = textCoords;
    vs_out.fragPosLightSpace = lightTransfer * vec4(vs_out.fragPos, 1.0);
    gl_Position = projection * view * model * vec4(position, 1.0);
}