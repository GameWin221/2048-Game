#version 330 core

out vec4 FragColor;

in vec2 texcoord;

uniform vec3 color;

uniform sampler2D mainTexture;

void main()
{
	FragColor = texture(mainTexture, texcoord) * vec4(color, 1.0f);
}