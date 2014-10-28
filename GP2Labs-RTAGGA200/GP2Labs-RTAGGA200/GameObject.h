#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <vector>

class Component;

using namespace std;

class GameObject
{
	public:
		void init();
		void update();
		void render();
		void destroy();
		const string getName();
		void setName(const std::string& name);
		void addComponent(Component* component);
	private:
		string m_Name;
		vector<Component*> m_Components;
	protected:
};

#endif