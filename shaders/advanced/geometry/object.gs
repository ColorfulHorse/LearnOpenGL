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

uniform mat4 projection;

uniform float time;

vec3 getNormal() {
    vec3 a = vec3(gl_in[0].gl_Position - gl_in[1].gl_Position);
    vec3 b = vec3(gl_in[2].gl_Position - gl_in[1].gl_Position);
    return normalize(cross(a, b));
}


void main() {
    vec3 mNormal = getNormal();
    float magnitude = 2.0;
    // 随时间0-1变化
    vec3 direction = mNormal * ((sin(time) + 1.0) / 2.0) * magnitude;
    for(int i = 0; i < 3; i++) {
        gl_Position = projection * (gl_in[i].gl_Position + vec4(direction * magnitude, 1.0));
        texCoord = gs_in[i].textCoord;
        worldPos = gs_in[i].worldPos;
        normal = mNormal;
        EmitVertex();
    }
    EndPrimitive();
} 