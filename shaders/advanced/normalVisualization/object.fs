#version 330 core
struct Material {
    sampler2D texture_diffuse0;
    sampler2D texture_specular0;
    sampler2D texture_reflect0;
    float shininess;
};

// 方向光源，不衰减，比如阳光
struct DirLight {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 direction;
};

// 点光源
struct PointLight {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 position;

    float constant;
    // 线性变化率
    float linear;
    // 平方变化率
    float quadratic;
};

// 聚光光源，范围有限
struct SpotLight {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 position;
    vec3 direction;

    float constant;
    // 线性变化率
    float linear;
    // 平方变化率
    float quadratic;

    // 切光角的余弦值，光源散射角度
    float cutOff;
    // 外切光角，用于平滑过渡
    float outerCutOff;
};

#define NR_POINT_LIGHTS 4

uniform Material material;
uniform vec3 viewPos;
uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLight;

uniform samplerCube skyboxTexture;

// 片段的世界坐标
in vec3 worldPos;
// 观察者坐标
// 片段所在面法向量
in vec3 normal;

in vec2 texCoord;
out vec4 FragColor;

// 方向光源
vec3 calDirLight(DirLight light, vec3 norm, vec3 viewDirection) { 
    // 光源散射到片段的方向
    vec3 lightDirection = normalize(light.direction);
    // 物体贴图
    vec3 tex = vec3(texture(material.texture_diffuse0, texCoord));

    vec3 R = reflect(viewDirection, norm);
    // 反射贴图
    vec3 reflectTexture = vec3(texture(material.texture_reflect0, texCoord));
    vec3 reflection = texture(skyboxTexture, R).rgb * reflectTexture;
    tex += reflection;

    // 点乘计算光源对这个面的影响，因为法向量垂直平面朝上，所以这里取光照的反方向
    float diff = max(dot(norm, -lightDirection), 0.0);
    // 光线基于法线的反射向量
    vec3 reflectDirection = reflect(lightDirection, norm);
    // 镜面反射影响
    float spec = max(dot(-viewDirection, reflectDirection), 0.0);
    // 反光度
    spec = pow(spec, material.shininess);
    
    // 环境光照
    vec3 ambient = light.ambient * tex;
    vec3 diffuse = light.diffuse * diff * tex;
    vec3 specular = light.specular * spec * vec3(texture(material.texture_specular0, texCoord));
    vec3 res = ambient + diffuse + specular;
    return res;
}

// 点光源
vec3 calPointLight(PointLight light, vec3 norm, vec3 viewDirection) { 
    // 光源散射到片段的方向
    vec3 lightDirection = normalize(worldPos - light.position);
    // 物体贴图
    vec3 tex = vec3(texture(material.texture_diffuse0, texCoord));

    vec3 R = reflect(viewDirection, norm);
    // 反射贴图
    vec3 reflectTexture = vec3(texture(material.texture_reflect0, texCoord));
    vec3 reflection = texture(skyboxTexture, R).rgb * reflectTexture;
    tex += reflection;

    // 点乘计算光源对这个面的影响，因为法向量垂直平面朝上，所以这里取光照的反方向
    float diff = max(dot(norm, -lightDirection), 0.0f);
    // 光线基于法线的反射向量
    vec3 reflectDirection = reflect(lightDirection, norm);
    // 镜面反射影响
    float spec = max(dot(-viewDirection, reflectDirection), 0.0);
    // 反光度
    spec = pow(spec, material.shininess);
    float distance = length(light.position - worldPos);
    
    // 距离衰减
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

    
    // 环境光照
    vec3 ambient = light.ambient * tex;
    vec3 diffuse = light.diffuse * diff * tex;
    vec3 specular = light.specular * spec * texture(material.texture_specular0, texCoord).rgb;
    vec3 res = ambient * attenuation + diffuse * attenuation + specular * attenuation;
    return res;
}

// 聚光光源影响
vec3 calSpotLight(SpotLight light, vec3 norm, vec3 viewDirection) {
    // 光源散射到片段的方向
    vec3 lightDirection = normalize(worldPos - light.position);
    // 光线聚光方向和到片段散射方向的夹角余弦
    float fragAngle = dot(normalize(light.direction), lightDirection);
    // 在外切光角内的强度 = (fragAngle - cos(out)) / (cos(in) - cos(out))
    // 平滑强度在内切光角和外切光角范围内才有意义，限制为0-1
    float intensity = clamp((fragAngle - light.outerCutOff) / (light.cutOff - light.outerCutOff), 0.0, 1.0);
    // 物体贴图
    vec3 tex = vec3(texture(material.texture_diffuse0, texCoord));

    vec3 R = reflect(viewDirection, norm);
    // 反射贴图
    vec3 reflectTexture = vec3(texture(material.texture_reflect0, texCoord));
    vec3 reflection = texture(skyboxTexture, R).rgb * reflectTexture;
    tex += reflection;

    // 环境光照
    vec3 ambient = light.ambient * tex;

    // 点乘计算光源对这个面的影响，因为法向量垂直平面朝上，所以这里取光照的反方向
    float diff = max(dot(norm, -lightDirection), 0.0f);
    vec3 diffuse = light.diffuse * diff * tex;

    // 光线基于法线的反射向量
    vec3 reflectDirection = reflect(lightDirection, norm);
    // 镜面反射影响
    float spec = max(dot(-viewDirection, reflectDirection), 0.0);
    // 反光度
    spec = pow(spec, material.shininess);
    vec3 specular = light.specular * spec * texture(material.texture_specular0, texCoord).rgb;


    float distance = length(light.position - worldPos);
    // 距离衰减
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);
    vec3 res = ambient * attenuation * intensity + diffuse * attenuation * intensity + specular * attenuation * intensity;
    return res;
}

uniform sampler2D texture_diffuse0;

void main() {
    // 片段法线
    vec3 norm = normalize(normal);
    // // 视线向量
    vec3 viewDirection = normalize(worldPos - viewPos);
    
    vec3 res = calDirLight(dirLight, norm, viewDirection);

    for(int i = 0; i < NR_POINT_LIGHTS; i++){
        res += calPointLight(pointLights[i], norm, viewDirection);
    }

    // res += calSpotLight(spotLight, norm, viewDirection);

    FragColor = vec4(res, 1.0);
}