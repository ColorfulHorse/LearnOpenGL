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

float calcShadow(vec3 lightDir, vec3 normal) {
    // 变换到裁剪空间
    vec3 projCoords = fs_in.fragPosLightSpace.xyz / fs_in.fragPosLightSpace.w;
    // 因为z值在0-1内，所以纹理坐标[-1, 1] 变换到 [0, 1]
    projCoords = projCoords * 0.5 + 0.5;
    // 强制超出光的正交视锥的远平面的片段不在阴影中
    if(projCoords.z > 1.0) {
        return 0.0; 
    }

    float bias = max(0.05 * dot(-lightDir, normal), 0.005);
    // pcf阴影模糊，3*3均值模糊
    float shadow = 0.0;
    // 每个片段的纹理大小
    vec2 texSize = 1.0 / textureSize(shadowTexture, 0);
    for(int x = -1; x <= 1; x++) {
        for(int y = -1; y <= 1; y++) {
            // 偏移采样
            float minDepth = texture(shadowTexture, projCoords.xy + vec2(x, y) * texSize).r;
            shadow += projCoords.z > minDepth ? 1.0 : 0.0;
            // shadow += projCoords.z - bias > minDepth ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;
    return shadow;


    // float minDepth = texture(shadowTexture, projCoords.xy).r;
    // 阴影失真
    // 由于阴影贴图分辨率不足，多个邻近像素使用深度贴图中一个像素来作比较，导致邻近像素深度值有细微差别，造成最先被照射到的面有明暗条纹
    // 两种解决方案，一种是根据片段和光方向的角度将z值向近处偏移一些再判断；但是这样会导致悬浮失真(Peter Panning)
    // 一种为建立阴影贴图时剔除正面；但是剔除正面时由于平面只有一面所以无效，深度值永远为1，所以平面永远没有阴影
    // https://www.zhihu.com/question/49090321
    // https://www.zhihu.com/question/321779117
    // 两种方法不能同时使用
    // return projCoords.z - bias > minDepth ? 1.0 : 0.0;
    // return projCoords.z > > minDepth ? 1.0 : 0.0;
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
    vec3 ambient = 0.1 * tex;
    vec3 diffuse = diff * tex;
    vec3 specular = spec * tex;
    vec3 res = ambient + diffuse + specular;
    float shadow = calcShadow(lightDirection, norm);
    // 在阴影中时只受环境光影响
    FragColor = vec4(ambient + (1.0 - shadow) * (diffuse + specular), 1.0);
}