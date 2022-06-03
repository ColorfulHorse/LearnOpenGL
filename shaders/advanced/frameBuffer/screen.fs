#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

void main()
{
    // 反相
    // vec3 col = vec3(1.0 - texture(screenTexture, TexCoords));
    // FragColor = vec4(col, 1.0);
    // 灰度化
    // float gray = 0.2126 * col.r + 0.7152 * col.g + 0.0722 * col.b;
    // FragColor = vec4(gray, gray, gray, 1.0);

    // vec4 col = texture(screenTexture, TexCoords);
    // FragColor = vec4(col.rgb, 1.0);

    const float offset = 1 / 300.0;

    vec2 offsets[9] = vec2[](
        vec2(-offset,  offset), // 左上
        vec2( 0.0f,    offset), // 正上
        vec2( offset,  offset), // 右上
        vec2(-offset,  0.0f),   // 左
        vec2( 0.0f,    0.0f),   // 中
        vec2( offset,  0.0f),   // 右
        vec2(-offset, -offset), // 左下
        vec2( 0.0f,   -offset), // 正下
        vec2( offset, -offset)  // 右下
    );

    // 锐化kernel
    float kernel[9] = float[](
        -1, -1, -1,
        -1,  9, -1,
        -1, -1, -1
    );

    // 模糊
    // float kernel[9] = float[](
    //     1.0 / 16, 2.0 / 16, 1.0 / 16,
    //     2.0 / 16, 4.0 / 16, 2.0 / 16,
    //     1.0 / 16, 2.0 / 16, 1.0 / 16  
    // );

    vec3 sampleTex[9];

    for(int i = 0; i < 9; i++) {
        // 偏移采样
        sampleTex[i] = texture(screenTexture, (TexCoords.st + offsets[i])).rgb;
    }

    vec3 color = vec3(0.0);
    // 对每个片段卷积
    for(int i = 0; i < 9; i++) {
        color += sampleTex[i] * kernel[i];
    }
    FragColor = vec4(color, 1.0);
} 