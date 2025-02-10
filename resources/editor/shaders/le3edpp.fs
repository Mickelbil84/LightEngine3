#version 410 core
out vec4 fColor;
  
in vec2 uv;

uniform sampler2D screenTexture;
uniform sampler2D selectedTexture;

uniform int selectedIds[128];

const float offset = 1.0 / 800.0;
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
// float kernel[9] = float[](
//     0, 0, 0,
//     0,  1, 0,
//     0, 0, 0
// );

void main()
{ 
    // Post process effect
    vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
        sampleTex[i] = vec3(texture(selectedTexture, uv.st + offsets[i]));
    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; i++)
        col += sampleTex[i] * kernel[i];
    float avg = abs(col.x + col.y + col.z) / 3.0;
    col = vec3(avg, avg, avg);
    if (col.x > 0.0001) col = vec3(1,1,1);
    
    // Original color
    vec3 orgColor = vec3(texture(screenTexture, uv));

    vec3 finalColor = orgColor * (1.0 - col) + vec3(245.0, 164.0, 83.0) * col / 255.0; // TODO: Move to engine config
    fColor = vec4(finalColor, 1.0);
}