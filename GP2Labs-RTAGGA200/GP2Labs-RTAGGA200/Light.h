#ifndef LIGHT_H
#define LIGHT_H

using namespace std;

#include <glm/glm.hpp>
using glm::mat4;
using glm::vec4;
using glm::vec3;

#include "Component.h"

class Light :public Component
{
	public:
		Light();
		~Light();

		vec4& getLightDiffuse();
		vec3& getLightDirection();

		void setLightDiffuse(float r, float g, float b, float a);
		void setLightDirection(float x, float y, float z);
	private:
		vec4 m_LightDiffuseColor;
		vec3 m_LightDirection;
	protected:
};

#endif