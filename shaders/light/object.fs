#version 330 core

uniform vec3 lightColor;
uniform vec3 objectColor;
// 光源位置
uniform vec3 lightPos;

// 片段的世界坐标
in vec3 worldPos;
// 观察者坐标
in vec3 viewPos;
// 片段所在面法向量
in vec3 normal;
out vec4 FragColor;

void main() {
    // 环境光照
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

    // 漫反射
    vec3 norm = normalize(normal);
    // 光源散射到顶点的方向
    vec3 lightDirection = normalize(worldPos - lightPos);
    // 点乘计算光源对这个面的影响，因为法向量垂直平面朝上，所以这里取光照的反方向
    float diff = max(dot(norm, -lightDirection), 0.0f);
    vec3 diffuse = diff * lightColor;

    float specularStrength = 0.5f;
    // 视线向量
    vec3 viewDirection = normalize(worldPos - viewPos);
    // 光线基于法线的反射向量
    vec3 reflectDirection = reflect(lightDirection, norm);
    // 镜面反射影响
    float spec = max(dot(reflectDirection, -viewDirection), 0.0f);
    // 反光度
    spec = pow(spec, 32);
    vec3 specular = spec * lightColor;
    FragColor = vec4((ambient + diffuse + specular) * objectColor, 1.0f);
}