#ifndef CAMERA_H
#define CAMERA_H

#include "Component.h"

#include <glm/glm.hpp>
using glm::mat4;
using glm::vec3;
using glm::vec2;
using glm::mat4;

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
	public:
		void setPosition(vec3 position);
		void setLookAt(vec3 lookAt);
		void setUp(vec3 up);
		void setFOV(float FOV);
		void setAspectRatio(float aspectRatio);
		void setNearClip(float nearClip);
		void setFarClip(float farClip);
		mat4 getViewMatrix();
		mat4 getProjectionMatrix();
		void update();
	private:
		vec3 m_Position;
		vec3 m_LookAt;
		vec3 m_Up;
		float m_FOV;
		float m_AspectRatio;
		float m_NearClip;
		float m_FarClip;
		mat4 m_ViewMatrix;
		mat4 m_ProjectionMatrix;
	protected:
};

#endif