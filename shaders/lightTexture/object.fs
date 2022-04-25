#version 330 core
struct Material {
    sampler2D diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 position;
};

// 光源位置
uniform Light light;
uniform Material material;
uniform vec3 viewPos;

// 片段的世界坐标
in vec3 worldPos;
// 观察者坐标
// 片段所在面法向量
in vec3 normal;

in vec2 texCoord;
out vec4 FragColor;


void main() {
    // 环境光照
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoord));

    // 漫反射
    vec3 norm = normalize(normal);
    // 光源散射到顶点的方向
    vec3 lightDirection = normalize(worldPos - light.position);
    // 点乘计算光源对这个面的影响，因为法向量垂直平面朝上，所以这里取光照的反方向
    float diff = max(dot(norm, -lightDirection), 0.0f);
    vec3 diffuse = light.diffuse * vec3(texture(material.diffuse, texCoord));

    // 视线向量
    vec3 viewDirection = normalize(worldPos - viewPos);
    // 光线基于法线的反射向量
    vec3 reflectDirection = reflect(lightDirection, norm);
    // 镜面反射影响
    float spec = max(dot(-viewDirection, reflectDirection), 0.0);
    // 反光度
    spec = pow(spec, material.shininess);
    vec3 specular = light.specular * (spec * material.specular);
    vec3 res = ambient + diffuse + specular;
    FragColor = vec4(res, 1.0);
}