#version 150

in vec3 vertexPosition;
in vec3 vertexNormals;

out vec4 vertexColorOut;

uniform mat4 MVP;
uniform mat4 Model;

uniform vec3 lightDirection;

uniform vec4 ambientMaterialColor;
uniform vec4 ambientLightColor;
uniform vec4 diffuseMaterialColor;
uniform vec4 diffuseLightColor;

void main()
{
	vec3 worldNorm = normalize(Model*vec4(vertexNormals, 0.0f)).xyz;
	float diffuseTerm = dot(worldNorm, lightDirection);
	vertexColorOut = ((ambientMaterialColor*ambientLightColor) + (diffuseMaterialColor*diffuseLightColor*diffuseTerm));
	gl_Position = MVP * vec4(vertexPosition, 1.0);
}