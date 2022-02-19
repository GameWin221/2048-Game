#version 330 core

out vec4 FragColor;

in vec2 texcoord;

uniform vec3 color;

uniform sampler2D text;

void main()
{    
    float alpha = texture(text, texcoord).r;
    FragColor = vec4(color, alpha);
}