#version 330 core

layout(triangles) in;
layout(line_strip, max_vertices = 6) out;

uniform mat4 projection;

out vec3 fColor;


const float MAGNITUDE = 0.2;

vec3 getNormal() {
    vec3 a = vec3(gl_in[0].gl_Position - gl_in[1].gl_Position);
    vec3 b = vec3(gl_in[2].gl_Position - gl_in[1].gl_Position);
    return normalize(cross(a, b));
}


void main() {
    vec3 faceNormal = getNormal();
    // for(int i = 0; i < 3; i++) {
    //     vec4 vertex = gl_in[i].gl_Position;

    //     fColor = vec3(1.0, 1.0, 0.0);
    //     // 在view-space计算完后变换到投影空间
    //     gl_Position = projection * vertex;
    //     EmitVertex();
    //     gl_Position = projection * (vertex + vec4(gs_in[i].normal * MAGNITUDE, 0.0));
    //     EmitVertex();
    //     EndPrimitive();

    // }

    for(int i = 0; i < 3; i++) {
        vec4 vertex = gl_in[i].gl_Position;

        fColor = vec3(1.0, 1.0, 0.0);
        // 在view-space计算完后变换到投影空间
        gl_Position = projection * vertex;
        EmitVertex();
        gl_Position = projection * (vertex + vec4(faceNormal * MAGNITUDE, 0.0));
        EmitVertex();
        EndPrimitive();
    }
}

