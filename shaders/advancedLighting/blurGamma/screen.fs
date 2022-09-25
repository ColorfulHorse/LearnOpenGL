#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
uniform bool gamma;

uniform sampler2D screenTexture;


void main()
{
    const float offset = 1 / 600.0;
    const int col = 50;
    const int size = col * col;
    vec3 color = vec3(0.0);
    for(int i = 0; i < col; i++) {
        for(int j = 0; j < col; j++) {
            // 偏移采样
            vec3 peice = texture(screenTexture, vec2(TexCoords.s + (i-col/2)*offset, TexCoords.t - (j-col/2)*offset)).rgb;
            // if(gamma) {
            //     color += pow(peice, vec3(2.2));   
            // } else {
            //     color += peice;   
            // }
            color += (peice/vec3(size));
        }
    }
    if(gamma) {
       color = pow(color, vec3(1.0/2.2));    
    }
    FragColor = vec4(color, 1.0);
}