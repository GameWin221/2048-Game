#version 330 core
layout (location = 0) in vec4 vPos;

out vec2 texcoord;

uniform mat4 projection;
uniform mat4 model;

void main()
{
    texcoord = vPos.zw;
    gl_Position = projection * model * vec4(vPos.xy, 0.0, 1.0);
}