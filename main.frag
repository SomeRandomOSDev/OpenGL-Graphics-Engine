#version 330 core

out vec4 color;

in vec2 UV;

uniform sampler2D albedo;

void main()
{
	color = vec4(texture(albedo, UV).rgb, 1);
}