#version 410 core
out vec4 fColor;

in vec2 uv;

uniform sampler2D positionTexture;
uniform sampler2D normalTexture;
uniform sampler2D noiseTexture;
uniform mat4 projection, view;

// const vec3 samples[64] = vec3[](
//     vec3(-0.4281, -0.0732, -0.2924),
//     vec3( 0.3719, -0.0513, -0.3765),
//     vec3(-0.0983,  0.2760, -0.0711),
//     vec3( 0.2265,  0.4397,  0.3256),
//     vec3( 0.0432, -0.0675, -0.0671),
//     vec3( 0.3291, -0.2651,  0.8002),
//     vec3(-0.1615,  0.7610,  0.4255),
//     vec3(-0.2672, -0.1822,  0.9141),
//     vec3( 0.1429, -0.9493, -0.0635),
//     vec3( 0.7692,  0.3265, -0.2647),
//     vec3(-0.6608, -0.2536, -0.5197),
//     vec3( 0.0185,  0.1260,  0.1496),
//     vec3(-0.2226,  0.0451, -0.9736),
//     vec3( 0.0512,  0.4542, -0.7701),
//     vec3(-0.9165, -0.0826,  0.0863),
//     vec3(-0.0551, -0.9857,  0.0812),
//     vec3( 0.8233,  0.2115,  0.1056),
//     vec3( 0.4291,  0.5842,  0.5899),
//     vec3(-0.0876,  0.6695, -0.5177),
//     vec3(-0.4194,  0.3135,  0.6643),
//     vec3( 0.1485, -0.6870,  0.2733),
//     vec3(-0.6702,  0.4586,  0.1529),
//     vec3(-0.1044, -0.2764,  0.2243),
//     vec3( 0.5793, -0.5939,  0.1070),
//     vec3( 0.3769, -0.4983, -0.6804),
//     vec3( 0.2064, -0.0781,  0.4735),
//     vec3( 0.6402,  0.3018, -0.6404),
//     vec3(-0.3615,  0.1984, -0.4283),
//     vec3(-0.1689, -0.6643, -0.5998),
//     vec3(-0.4947, -0.7472,  0.0491),
//     vec3( 0.0532, -0.4801, -0.0780),
//     vec3( 0.3086,  0.0832, -0.8701),
//     vec3(-0.5571,  0.1290,  0.6315),
//     vec3( 0.2458, -0.1398,  0.9485),
//     vec3(-0.7652,  0.0318, -0.4704),
//     vec3(-0.3689,  0.8280, -0.1892),
//     vec3(-0.0871, -0.1948, -0.1591),
//     vec3( 0.4426, -0.7652, -0.1836),
//     vec3(-0.2718,  0.5037,  0.4092),
//     vec3( 0.6942, -0.1782,  0.4048),
//     vec3( 0.1280, -0.3168,  0.7521),
//     vec3(-0.5271, -0.5523,  0.5662),
//     vec3( 0.0467,  0.9064,  0.1879),
//     vec3(-0.8980, -0.2279, -0.2224),
//     vec3( 0.8529, -0.4607, -0.1225),
//     vec3( 0.2060,  0.2564,  0.3234),
//     vec3( 0.5236,  0.7820,  0.1372),
//     vec3(-0.3333, -0.4058, -0.0499),
//     vec3( 0.4235,  0.0460,  0.1877),
//     vec3( 0.0152, -0.6332,  0.7302),
//     vec3(-0.2210, -0.9036, -0.2815),
//     vec3( 0.4938,  0.5050, -0.5925),
//     vec3(-0.0489,  0.2402, -0.6292),
//     vec3(-0.5958, -0.1534,  0.2471),
//     vec3( 0.3457, -0.8430,  0.3055),
//     vec3( 0.0875,  0.7011,  0.4928),
//     vec3(-0.6325,  0.7194, -0.0416),
//     vec3( 0.2896, -0.2657, -0.2831),
//     vec3(-0.7775, -0.5093, -0.1035),
//     vec3( 0.1432,  0.1740, -0.2228),
//     vec3( 0.6113, -0.0879, -0.5157),
//     vec3(-0.4415,  0.0988,  0.1470),
//     vec3( 0.1182,  0.3567, -0.8431),
//     vec3(-0.2591, -0.1267,  0.3259)
// );
const vec3 samples[16] = vec3[](
    vec3( 0.034,  0.023, 0.018),
    vec3(-0.051,  0.042, 0.036),
    vec3( 0.072, -0.031, 0.058),
    vec3(-0.023, -0.068, 0.081),
    vec3( 0.091,  0.087, 0.112),
    vec3(-0.102,  0.034, 0.147),
    vec3( 0.048, -0.121, 0.183),
    vec3(-0.067,  0.098, 0.224),
    vec3( 0.143, -0.052, 0.271),
    vec3(-0.128, -0.143, 0.318),
    vec3( 0.094,  0.176, 0.372),
    vec3(-0.183,  0.067, 0.429),
    vec3( 0.201, -0.098, 0.491),
    vec3(-0.076,  0.214, 0.558),
    vec3( 0.167, -0.189, 0.634),
    vec3(-0.221,  0.124, 0.712)
);
const int numSamples = 16;

struct AmbientLight
{
    float ssaoBias;
    float ssaoRadius;
};
uniform AmbientLight ambientLight;

void main()
{ 
    vec3 position = texture(positionTexture, uv).xyz;
    vec3 normal = normalize(texture(normalTexture, uv).xyz);

    vec3 randomVec = texture(noiseTexture, uv * 10).xyz * 2.0 - 1.0;
    vec3 tangent = normalize(randomVec - normal * dot(randomVec, normal));
    vec3 bitangent = cross(normal, tangent);
    mat3 TBN = mat3(tangent, bitangent, normal);

    float occlusion = 0.0;
    float wsum = 0.0;
    for (int i = 0; i < numSamples; ++i) {
        vec3 sampleVec = TBN * normalize(samples[i]);
        vec3 samplePos = position + sampleVec * ambientLight.ssaoRadius;


        vec4 sampleProj = projection * vec4(samplePos, 1.0);
        sampleProj.xy /= sampleProj.w;
        vec2 sampleUV = sampleProj.xy * 0.5 + 0.5;
        float sampleDepth = texture(positionTexture, sampleUV).z;

        float dist = abs(position.z - sampleDepth);
        float rangeCheck = smoothstep(0.0, 1.0, ambientLight.ssaoRadius / dist);
        // if (dist < ambientLight.ssaoRadius)
        occlusion += (sampleDepth >= (samplePos.z + ambientLight.ssaoBias) ? 1.0 : 0.0) * rangeCheck;
    }
    occlusion = 1.0 - (occlusion / float(numSamples));

    fColor = vec4(vec3(pow(occlusion, 1.0)), 1.0);
}