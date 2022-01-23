#version 330

out vec4 FragColor;

in vec2 texcoord;

uniform vec3 color;
uniform mat4 transform;

uniform sampler2D mainTexture;

void main()
{
	FragColor = texture(mainTexture, texcoord) * vec4(color, 1.0f);
}