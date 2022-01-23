#version 330 core
layout (location = 0) in vec2 vPos;

out vec2 texcoord;

uniform vec2 position;
uniform vec2 size;
uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

void main()
{
	// Deriving the texture coordinates from the vPos
	texcoord = (vPos / 2.0) + 0.5;
    gl_Position = projection * view * model * vec4(vPos, 0.0, 1.0);
}