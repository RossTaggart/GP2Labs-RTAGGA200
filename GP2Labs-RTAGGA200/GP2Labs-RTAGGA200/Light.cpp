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