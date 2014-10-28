#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

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

	private:
	protected:
		string m_Type;
		bool m_Active;
};

#endif