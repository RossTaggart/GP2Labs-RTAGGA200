#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include "GameObject.h"

using namespace std;

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

		void setParent(GameObject *parent);
		GameObject* getParent();

	private:
	protected:
		string m_Type;
		bool m_Active;
		GameObject * m_Parent;
};

#endif