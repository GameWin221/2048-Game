#version 330 core

out vec4 FragColor;

in vec2 texcoord;

uniform sampler2D screenTexture;

const float vignetteR = 3.0;

void main()
{ 
    vec3 color = texture(screenTexture, texcoord).rgb;
    
    vec2 screenSize = textureSize(screenTexture, 0); 
    vec2 screenMiddle = screenSize / 2.0f;
    vec2 screenCoord = gl_FragCoord.xy / screenSize;

    float dist = length(abs(vec2(0.5f) - screenCoord));

    color *= 1.0f - pow(dist, vignetteR);

    FragColor = vec4(color, 1.0f);
}