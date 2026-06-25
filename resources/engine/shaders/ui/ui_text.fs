#version 410 core

out vec4 outColor;

uniform sampler2D fontAtlas;
uniform vec4 textColor;
uniform vec2 cropBottomLeft, cropTopRight;

in vec2 texCoord;

void main() {
    vec2 uv = vec2(
        cropBottomLeft.x + texCoord.x * (cropTopRight.x - cropBottomLeft.x),
        cropBottomLeft.y + texCoord.y * (cropTopRight.y - cropBottomLeft.y)
    );
    float alpha = texture(fontAtlas, uv).r;
    outColor = vec4(textColor.rgb, textColor.a * alpha);
}
