#version 150

in vec2 vertexTexCoordsOut;

out vec4 FragColor;

uniform sampler2D texture();

void main()
{
	FragColor = texture(texture0,vertexTexCoordsOut);
}