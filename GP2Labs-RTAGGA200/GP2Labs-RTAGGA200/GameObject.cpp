#include "GameObject.h"
#include "Component.h"
#include "Mesh.h"
#include "Material.h"
#include "Camera.h"
#include "Transform.h"

#include <string>
#include <vector>

using namespace std;

GameObject::GameObject()
{
	m_Name = "GameObject";
	m_Camera = NULL;
	m_Mesh = NULL;
	m_Material = NULL;
	m_Transform = NULL;
	m_Parent = NULL;
}

GameObject::~GameObject()
{
	destroy();
}

void GameObject::init()
{
	for (auto iter = m_Components.begin(); iter != m_Components.end(); iter++)
	{
		(*iter)->init();

	}

	for (auto iterChild = m_Children.begin(); iterChild != m_Children.end(); iterChild++)
	{
		(*iterChild)->init();

	}
}

void GameObject::update()
{
	for (auto iter = m_Components.begin(); iter != m_Components.end(); iter++)
	{
		(*iter)->update();
	}

	for (auto iterChild = m_Children.begin(); iterChild != m_Children.end(); iterChild++)
	{
		(*iterChild)->update();

	}
}

void GameObject::render()
{
	for (auto iter = m_Components.begin(); iter != m_Components.end(); iter++)
	{
		(*iter)->render();
	}

	for (auto iterChild = m_Children.begin(); iterChild != m_Children.end(); iterChild++)
	{
		(*iterChild)->render();

	}
}

void GameObject::destroy()
{
	auto iter = m_Components.begin();
	while (iter != m_Components.end())
	{
		(*iter)->destroy();
		if ((*iter))
		{
			delete(*iter);
			(*iter) = NULL;
			iter = m_Components.erase(iter);
		}
		else
		{
			iter++;
		}
	}
	m_Components.clear();

	auto iterChild = m_Children.begin();
	while (iterChild != m_Children.end())
	{
		(*iterChild)->destroy();
		if ((*iterChild))
		{
			delete(*iterChild);
			(*iterChild) = NULL;
			iterChild = m_Children.erase(iterChild);
		}
		else
		{
			iterChild++;
		}
	}
	m_Children.clear();
}

const std::string GameObject::getName()
{
	return m_Name;
}

void GameObject::setName(const std::string& name)
{
	m_Name = name;
}

void GameObject::addComponent(Component* component)
{
	component->setParent(this);
	m_Components.push_back(component);
}

Mesh* GameObject::getMesh()
{
	return m_Mesh;
}

void GameObject::setMesh(Mesh * mesh)
{
	m_Mesh = mesh;
	addComponent(m_Mesh);
	
}

Material* GameObject::getMaterial()
{
	return m_Material;
}

void GameObject::setMaterial(Material* material)
{
	m_Material = material;
	addComponent(m_Material);
}

Camera* GameObject::getCamera()
{
	return m_Camera;
}

void GameObject::setCamera(Camera* camera)
{
	m_Camera = camera;
	addComponent(m_Camera);
}

Transform* GameObject::getTransform()
{
	return m_Transform;
}

void GameObject::setTransform(Transform* transform)
{
	m_Transform = transform;
	addComponent(m_Transform);
}

GameObject* GameObject::getParent()
{
	return m_Parent;
}

void GameObject::setParent(GameObject* parent)
{
	m_Parent = parent;
}

void GameObject::addChild(GameObject* child)
{
	m_Children.push_back(child);
}

int GameObject::getChildCount()
{
	return m_Children.size();
}

GameObject* GameObject::getChild(int index)
{
	if (index < m_Children.size())
	{
		return m_Children.at(index);
	}
}