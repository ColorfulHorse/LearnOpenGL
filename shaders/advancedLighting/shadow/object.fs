#version 330 core
out vec4 FragColor;

in VS_OUT {
    vec3 fragPos;
    vec3 mNormal;
    vec2 mTexCoords;
    vec4 fragPosLightSpace;
} fs_in;

uniform sampler2D shadowTexture;
uniform sampler2D diffuseTexture;

uniform vec3 lightPos;
uniform vec3 viewPos;

bool calcShadow(vec3 lightDir, vec3 normal) {
    // 变换到裁剪空间
    vec3 projCoords = fs_in.fragPosLightSpace.xyz / fs_in.fragPosLightSpace.w;
    // 因为z值在0-1内，所以纹理坐标[-1, 1] 变换到 [0, 1]
    projCoords = projCoords * 0.5 + 0.5;
    float minDepth = texture(shadowTexture, projCoords.xy).r;
    // 阴影失真
    float bias = max(0.05 * dot(-lightDir, normal), 0.005);
    return projCoords.z - bias > minDepth;
}


void main() {             
   // 片段法线
    vec3 norm = normalize(fs_in.mNormal);
    // 视线向量
    vec3 viewDirection = normalize(fs_in.fragPos - viewPos);

    // 光源散射到片段的方向
    vec3 lightDirection = normalize(fs_in.fragPos - lightPos);
    // 物体贴图
    vec3 tex = vec3(texture(diffuseTexture, fs_in.mTexCoords));

    // 点乘计算光源对这个面的影响，因为法向量垂直平面朝上，所以这里取光照的反方向
    float diff = max(dot(norm, -lightDirection), 0.0);

    float spec = 0.0;
    // 半程向量
    vec3 halfWayDir = - normalize(viewDirection + lightDirection);
    spec = max(dot(norm, halfWayDir), 0.0);

    // 反光度
    spec = pow(spec, 64.0);
    
    // 环境光照
    vec3 ambient = 0.02 * tex;
    vec3 diffuse = diff * tex;
    vec3 specular = spec * vec3(0.1);
    vec3 res = ambient + diffuse + specular;
    // 在阴影中时只受环境光影响
    FragColor = vec4(calcShadow(lightDirection, norm) ? ambient : res, 1.0);
}