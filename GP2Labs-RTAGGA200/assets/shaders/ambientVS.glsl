#version 150

in vec3 vertexPosition;

out vec4 vertexColorOut;

uniform mat4 MVP;
uniform vec4 ambientMaterialColor;
uniform vec4 ambientLightColor;

void main()
{
	vertexColorOut = ambientMaterialColor*ambientLightColor;
	gl_Position = MVP * vec4(vertexPosition, 1.0);
}