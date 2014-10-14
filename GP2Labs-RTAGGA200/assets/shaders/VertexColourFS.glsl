#version 150

out vec4 FragColor;
in  vec4 vertexColorOut;
void main()
{
	FragColor = vertexColorOut;
}