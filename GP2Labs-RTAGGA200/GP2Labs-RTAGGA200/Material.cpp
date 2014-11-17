#include "Material.h"
#include "Component.h"
#include "Shader.h"

#include <gl\glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <gl\GLU.h>
#include <SDL_ttf.h>
#include <glm/glm.hpp>

using namespace std;

using glm::mat4;
using glm::vec4;

Material::Material()
{
	m_ShaderProgram = -1;
	m_Type = "Material";
	m_AmbientColor = vec4(0.5f, 0.5f, 0.5f, 1.0f);
	m_DiffuseColor = vec4(0.75f, 0.75f, 0.75f, 1.0f);
}

Material::~Material()
{
	destroy();
}

void Material::destroy()
{
	glDeleteProgram(m_ShaderProgram);
}

bool Material::loadShader(const string& vertexShader, const string& fragmentShader)
{
	GLuint vertexShaderProgram = 0;
	std::string vsPath = vertexShader;
	vertexShaderProgram = loadShaderFromFile(vsPath, VERTEX_SHADER);

	GLuint fragmentShaderProgram = 0;
	std::string fsPath = fragmentShader;
	fragmentShaderProgram = loadShaderFromFile(fsPath, FRAGMENT_SHADER);

	m_ShaderProgram = glCreateProgram();

	glAttachShader(m_ShaderProgram, vertexShaderProgram);
	glAttachShader(m_ShaderProgram, fragmentShaderProgram);
	glLinkProgram(m_ShaderProgram);
	checkForLinkErrors(m_ShaderProgram);

	//now we can delete the VS & FS Programs
	glDeleteShader(vertexShaderProgram);
	glDeleteShader(fragmentShaderProgram);

	glBindAttribLocation(m_ShaderProgram, 0, "vertexPosition");
	glBindAttribLocation(m_ShaderProgram, 1, "vertexNormals");
	glBindAttribLocation(m_ShaderProgram, 2, "vertexTexCoords");
	glBindAttribLocation(m_ShaderProgram, 3, "vertexColor");

	return true;
}

void Material::Bind()
{
	glUseProgram(m_ShaderProgram);
}

GLint Material::getUniformLocation(const string& name)
{
	GLint MVPLocation = glGetUniformLocation(m_ShaderProgram, name.c_str());

	return MVPLocation;
}

vec4& Material::getAmbientColor()
{
	return m_AmbientColor;
}

void Material::setAmbientColor(float r, float g, float b, float a)
{
	m_AmbientColor = vec4(r, g, b, a);
}

vec4& Material::getDiffuseColor()
{
	return m_DiffuseColor;
}

void Material::setAmbientColor(float r, float g, float b, float a)
{
	m_DiffuseColor = vec4(r, g, b, a);
}