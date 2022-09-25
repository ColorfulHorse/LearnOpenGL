#version 330 core
struct Material {
    sampler2D texture_diffuse;
    sampler2D texture_specular;
    sampler2D texture_reflect;
    float shininess;
};

uniform Material material;
uniform vec3 viewPos;
uniform vec3 lightPositions[4];
uniform vec3 lightColors[4];

uniform bool gamma;

in VS_OUT {
    vec3 mFragPos;
    vec3 mNormal;
    vec2 mTexCoords;
} fs_in;


out vec4 FragColor;

vec3 calcLight(vec3 norm, vec3 viewPos, vec3 lightPos, vec3 lightColor) {
    vec3 viewDirection = normalize(fs_in.mFragPos - viewPos);
    vec3 lightDirection = normalize(fs_in.mFragPos - lightPos);
    float distance = length(fs_in.mFragPos - lightPos);
    // 点乘计算光源对这个面的影响，因为法向量垂直平面朝上，所以这里取光照的反方向
    float diff = max(dot(norm, -lightDirection), 0.0);
    float spec = 0.0;
    // 半程向量
    vec3 halfWayDir = - normalize(viewDirection + lightDirection);
    spec = max(dot(norm, halfWayDir), 0.0);

    // 反光度
    spec = pow(spec, material.shininess);

    // 开启gamma时使用平方衰减
    float attenuation = 1.0 / (gamma ? distance * distance : distance);
    
    // 环境光照
    vec3 ambient = vec3(0.0);
    vec3 diffuse = diff * lightColor;
    vec3 specular = spec * lightColor;
    vec3 res = ambient + diffuse * attenuation + specular * attenuation;
    return res; 
}

void main() {
    // 片段法线
    vec3 norm = normalize(fs_in.mNormal);
    // 物体贴图
    vec3 color = vec3(texture(material.texture_diffuse, fs_in.mTexCoords));
    vec3 lighting = vec3(0.0);
    for(int i = 0; i < 4; i++) {
        lighting += calcLight(norm, viewPos, lightPositions[i], lightColors[i]);
    }
    color *= lighting;
    if(gamma) {
        color = pow(color, vec3(1.0/2.2));
    }
    FragColor = vec4(color, 1.0);
}
