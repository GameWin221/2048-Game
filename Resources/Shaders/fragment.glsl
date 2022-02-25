#version 330 core

out vec4 FragColor;

in vec2 texcoord;

uniform vec3 color;
uniform float opacity;

uniform sampler2D mainTexture;
uniform vec2 textureTiling;

void main()
{
	FragColor = texture(mainTexture, texcoord * textureTiling) * vec4(color, opacity);
}