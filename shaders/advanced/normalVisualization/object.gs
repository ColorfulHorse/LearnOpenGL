#version 330 core
// 定义输入输出类型
layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in VS_OUT {
    vec2 textCoord;
    vec3 normal;
    vec3 worldPos;
} gs_in[];

out vec2 texCoord;

out vec3 worldPos;

out vec3 normal;

uniform float time;

vec3 getNormal() {
    vec3 a = vec3(gl_in[0].gl_Position - gl_in[1].gl_Position);
    vec3 b = vec3(gl_in[2].gl_Position - gl_in[1].gl_Position);
    return normalize(cross(b, a));
}


void main() {
    vec3 mNormal = getNormal();
    for(int i = 0; i < 3; i++) {
        gl_Position = gl_in[i].gl_Position;
        texCoord = gs_in[i].textCoord;
        worldPos = gs_in[i].worldPos;
        // 每个顶点都使用面的法向量
        normal = mNormal;
        // normal = gs_in[i].normal;
        EmitVertex();
    }
    EndPrimitive();
} 