#version 330 core
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 position;
    vec3 direction;
    // 切光角的余弦值   光源散射角度
    float cutOff;

    float constant;
    // 线性变化率
    float linear;
    // 平方变化率
    float quadratic;
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
    // 光源散射到顶点的方向
    vec3 lightDirection = normalize(worldPos - light.position);
    float theta = dot(normalize(light.direction), lightDirection);

    vec3 tex = vec3(texture(material.diffuse, texCoord));

    // 环境光照
    vec3 ambient = light.ambient * tex;

    if(theta > light.cutOff) {
        // 漫反射
        vec3 norm = normalize(normal);
        // 点乘计算光源对这个面的影响，因为法向量垂直平面朝上，所以这里取光照的反方向
        float diff = max(dot(norm, -lightDirection), 0.0f);
        vec3 diffuse = light.diffuse * tex;

        // 视线向量
        vec3 viewDirection = normalize(worldPos - viewPos);
        // 光线基于法线的反射向量
        vec3 reflectDirection = reflect(lightDirection, norm);
        // 镜面反射影响
        float spec = max(dot(-viewDirection, reflectDirection), 0.0);
        // 反光度
        spec = pow(spec, material.shininess);
        // vec3 specular = light.specular * (spec * vec3(1.0, 1.0, 1.0));
        vec3 specular = light.specular * spec * texture(material.diffuse, texCoord).rgb;
        float distance = length(light.position - worldPos);
        // 衰减
        float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);
        vec3 res = ambient + diffuse * attenuation + specular * attenuation;
        FragColor = vec4(res, 1.0);
    } else {
        FragColor = vec4(ambient, 1.0);
    }
}