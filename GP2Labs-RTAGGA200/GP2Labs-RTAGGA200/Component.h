#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

using namespace std;

class GameObject;

class Component
{
	public:
		Component();
		virtual ~Component();
		
		virtual void init();
		virtual void update();
		virtual void render();
		virtual void destroy();

		const string& getType();
		void toggleActive();
		bool isActive();

	private:
		GameObject* getParent();
		void setParent(GameObject *parent);
	protected:
		string m_Type;
		bool m_Active;
		GameObject * m_Parent;
};

#endif