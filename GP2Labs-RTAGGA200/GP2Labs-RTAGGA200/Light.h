#ifndef LIGHT_H
#define LIGHT_H

using namespace std;

#include <glm/glm.hpp>
using glm::mat4;
using glm::vec3;

#include "Component.h"

class Light :public Component
{
	public:
		Light();
		~Light();
	private:
	protected:
};

#endif