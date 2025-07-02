#version 410 core
out vec4 fColor;

in vec2 uv;

uniform sampler2D depthTexture;

const float offset = 1.0 / 200.0;
vec2 offsets[9] = vec2[](
    vec2(-offset,  offset),
    vec2( 0.0f,    offset),
    vec2( offset,  offset),
    vec2(-offset,  0.0f),  
    vec2( 0.0f,    0.0f),  
    vec2( offset,  0.0f),  
    vec2(-offset, -offset),
    vec2( 0.0f,   -offset),
    vec2( offset, -offset) 
);
float kernel[9] = float[](
    -1, -1, -1,
    -1,  8, -1,
    -1, -1, -1
);

void main()
{ 
    // Post process effect
    vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(depthTexture, uv.st + offsets[i]));
    }
    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; i++) {
        if (i == 4) continue;
        if (sampleTex[i].r > sampleTex[4].r) col += 1.0 / 8.0;
    }
    fColor = vec4(col, 1.0);
}