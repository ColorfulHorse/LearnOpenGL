#version 330 core

in vec3 normal;
in vec3 fragPostion;

uniform vec3 cameraPos;

uniform samplerCube tex;

out vec4 FragColor;

void main(){
    // 视线方向
    vec3 viewDir = normalize(fragPostion - cameraPos);
    // 反射采样
    // vec3 r = reflect(viewDir, normalize(normal));
    // 折射采样
    // 空气	1.00
    // 水	1.33
    // 冰	1.309
    // 玻璃	1.52
    // 钻石	2.42
    vec3 r = refract(viewDir, normalize(normal), 1.0/1.52);
    FragColor = vec4(texture(tex, r).rgb, 1.0);
}