#version 410 core
out vec4 fColor;
  
in vec2 uv;

uniform sampler2D screenTexture;

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

void main()
{ 
    // Post process effect
    vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(screenTexture, uv.st + offsets[i]));
    }
    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; i++)
        col += sampleTex[i] * kernel[i];
    float avg = (col.x + col.y + col.z) / 3.0;
    col = 1 - vec3(avg, avg, avg);
    
    // Original color
    vec3 orgColor = vec3(texture(screenTexture, uv));
    fColor = vec4(orgColor, 1.0);

    // vec3 ps3brown = vec3(144.0, 120.0, 90.0) / 255.0 + 0.2;
    // fColor = vec4(orgColor * ps3brown, 1.0);
}