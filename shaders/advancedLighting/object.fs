#version 330 core
struct Material {
    sampler2D texture_diffuse;
    sampler2D texture_specular;
    sampler2D texture_reflect;
    float shininess;
};

uniform Material material;
uniform vec3 viewPos;
uniform vec3 lightPos;

uniform bool blinn;

in VS_OUT {
    vec3 mFragPos;
    vec3 mNormal;
    vec2 mTexCoords;
} fs_in;


out vec4 FragColor;

void main() {
    // 片段法线
    vec3 norm = normalize(fs_in.mNormal);
    // 视线向量
    vec3 viewDirection = normalize(fs_in.mFragPos - viewPos);

    // 光源散射到片段的方向
    vec3 lightDirection = normalize(fs_in.mFragPos - lightPos);
    // 物体贴图
    vec3 tex = vec3(texture(material.texture_diffuse, fs_in.mTexCoords));

    // 点乘计算光源对这个面的影响，因为法向量垂直平面朝上，所以这里取光照的反方向
    float diff = max(dot(norm, -lightDirection), 0.0);

    float spec = 0.0;

    if(blinn) {
        // 半程向量
        vec3 halfWayDir = - normalize(viewDirection + lightDirection);
        spec = max(dot(norm, halfWayDir), 0.0);
    } else {
        // 光线基于法线的反射向量
        vec3 reflectDirection = reflect(lightDirection, norm);
        // 镜面反射影响
        spec = max(dot(-viewDirection, reflectDirection), 0.0);
    }
    // 反光度
    spec = pow(spec, material.shininess);
    
    // 环境光照
    vec3 ambient = 0.0 * tex;
    vec3 diffuse = diff * tex;
    vec3 specular = spec * vec3(0.05);
    vec3 res = ambient + diffuse + specular;
    FragColor = vec4(res, 1.0);
}
