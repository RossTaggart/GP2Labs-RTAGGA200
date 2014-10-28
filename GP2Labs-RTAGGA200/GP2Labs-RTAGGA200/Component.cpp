#include "Component.h"

#include <string>

using namespace std;

Component::Component()
{
	m_Type = "Component";
	m_Active = true;
}

Component::~Component()
{

}

void Component::init(){}

void Component::update(){}

void Component::render(){}

void Component::destroy(){}

const string& Component::getType()
{
	return m_Type;
}

bool Component::isActive()
{
	return m_Active;
}