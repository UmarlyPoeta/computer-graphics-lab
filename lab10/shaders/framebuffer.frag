#version 330 core
out vec4 FragColor;

in vec2 texCoords;

uniform sampler2D screenTexture;
uniform vec2 texelSize;
uniform float kernel[9];
uniform int filterMode;

vec2 offsets[9] = vec2[](
    vec2(-1.0,  1.0), vec2( 0.0,  1.0), vec2( 1.0,  1.0),
    vec2(-1.0,  0.0), vec2( 0.0,  0.0), vec2( 1.0,  0.0),
    vec2(-1.0, -1.0), vec2( 0.0, -1.0), vec2( 1.0, -1.0)
);

void main()
{
    if (filterMode == 0)
    {
        FragColor = texture(screenTexture, texCoords);
        return;
    }

    vec3 color = vec3(0.0);
    for (int i = 0; i < 9; ++i)
    {
        vec2 offset = offsets[i] * texelSize;
        color += texture(screenTexture, texCoords + offset).rgb * kernel[i];
    }

    FragColor = vec4(color, 1.0);
}
