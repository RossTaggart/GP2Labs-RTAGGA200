#include "Light.h"


Light::Light()
{
	m_Type = "Light";
	m_LightDiffuseColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_LightDirection = vec3(0.5f, 0.5f, 0.5f);
}

Light::~Light()
{

}

vec4& Light::getLightDiffuse()
{
	return m_LightDiffuseColor;
}

vec3& Light::getLightDirection()
{
	return m_LightDirection;
}

void Light::setLightDiffuse(float r, float g, float b, float a)
{
	m_LightDiffuseColor = vec4(r, g, b, a);
}

void Light::setLightDirection(float x, float y, float z)
{
	m_LightDirection = vec3(x, y, z);
}