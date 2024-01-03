#version 330 core

layout (location = 0) in vec3 vertPosModelSpace;
layout (location = 1) in vec2 vertexUV;
layout (location = 2) in vec3 vertexNormal;

uniform mat4 _M;
uniform mat4 _V;
uniform mat4 _P;

out vec3 fragPos_CAMSPACE;
out vec2 UV;
out vec4 normal_wrong;
out mat4 MVP;
out vec3 fragPos;

void main()
{
	MVP = _P * _V * _M;
	gl_Position = MVP * vec4(vertPosModelSpace, 1);
	fragPos_CAMSPACE = vec3(gl_Position);
	fragPos = vec3(_M * vec4(vertPosModelSpace, 1));

	UV = vertexUV;
	normal_wrong = mat4(transpose(inverse(_M))) * vec4(vertexNormal, 0);  
}