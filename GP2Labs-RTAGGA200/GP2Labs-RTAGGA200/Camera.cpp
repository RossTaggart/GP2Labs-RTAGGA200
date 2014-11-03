#include "Camera.h"
#include "Component.h"
#include "GameObject.h"
#include "Transform.h"

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

Camera::Camera()
{
	m_Type = "Camera";
	m_LookAt = vec3(0.0f, 0.0f, 0.0f);
	m_Up = vec3(0.0f, 1.0f, 0.0f);
	m_NearClip = 0.1f;
	m_FarClip = 100.0f;
	m_FOV = 45.0f;
	m_AspectRatio = 16.0f / 9.0f;
	m_ViewMatrix = mat4();
	m_ProjectionMatrix = mat4();

}

Camera::~Camera()
{

}

void Camera::setPosition(vec3 position)
{
	m_Position = position;
}

void Camera::setLookAt(vec3 lookAt)
{
	m_LookAt = lookAt;
}

void Camera::setUp(vec3 up)
{
	m_Up = up;
}

void Camera::setFOV(float FOV)
{
	m_FOV = FOV;
}

void Camera::setAspectRatio(float aspectRatio)
{
	m_AspectRatio = aspectRatio;

}

void Camera::setFarClip(float farClip)
{
	m_FarClip = farClip;
}

void Camera::setNearClip(float nearClip)
{
	m_NearClip = nearClip;
}

mat4 Camera::getViewMatrix()
{
	return m_ViewMatrix;
}

mat4 Camera::getProjectionMatrix()
{
	return m_ProjectionMatrix;
}

void Camera::update()
{
	m_Position = m_Parent->getTransform()->getPosition();
	//m_ProjectionMatrix = glm::ortho(0.0f, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT, 0.0f, 0.1f, 100.0f);
	m_ProjectionMatrix = glm::perspective(m_FOV, m_AspectRatio, m_NearClip, m_FarClip);
	//m_ViewMatrix = glm::lookAt(vec3(0.0f, 0.0f, 5.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	m_ViewMatrix = glm::lookAt(m_Position, m_LookAt, m_Up);
}