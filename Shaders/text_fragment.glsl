#version 330 core
in vec2 texcoord;
out vec4 color;

uniform sampler2D text;
uniform vec3 textColor;

void main()
{    
    float alpha = texture(text, texcoord).r;

    color = vec4(textColor, alpha);
}