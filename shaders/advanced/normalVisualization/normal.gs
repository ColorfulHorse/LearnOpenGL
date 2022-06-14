#version 330 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 6) out;

uniform mat4 projection;

in VS_OUT {
    vec3 normal;
} gs_in[];

const float MAGNITUTE = 0.4;

void main() {
    for(int i = 0; i < 3; i++) {
        vec4 vertex = gl_in[i].gl_Position;
        // 在view-space计算完后变换到投影空间
        gl_Position = projection * vertex;
        EmitVertex();
        gl_Position = projection * (vertex + vec4(gs_in[i].normal * MAGNITUTE, 0.0));
        EmitVertex();
        EndPrimitive();
    }
}

