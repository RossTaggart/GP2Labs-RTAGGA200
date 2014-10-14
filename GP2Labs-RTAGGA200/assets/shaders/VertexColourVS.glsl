#version 150

in vec3 vertexPosition;
in vec4 vertexColor;

out vec4 vertexColorOut;

uniform mat4 MVP;

void main()
{
	vertexColorOut = vertexColor;
	gl_Position = MVP * vec4(vertexPosition, 1.0);
}