#version 330 core

layout(location = 0) in vec3 vertPosModelSpace;

uniform mat4 MVP;

void main()
{
	gl_Position.xyz = vertPosModelSpace;
	gl_Position.w =   1;

	gl_Position = MVP * gl_Position;
}