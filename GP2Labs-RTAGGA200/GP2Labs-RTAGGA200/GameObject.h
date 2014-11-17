#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <vector>

using namespace std;

class Component;
class Mesh;
class Material;
class Camera;
class Transform;
class Light;

class GameObject
{
	public:
		GameObject();
		~GameObject();

		void init();
		void update();
		void render();
		void destroy();

		const string getName();
		void setName(const std::string& name);
		void addComponent(Component * component);
		void addChild(GameObject* child);

		Mesh* getMesh();
		Material* getMaterial();
		Camera* getCamera();
		Transform* getTransform();
		GameObject* getParent();
		GameObject* getChild(int index);
		Light* getLight();
		int getChildCount();

		void setMesh(Mesh * mesh);
		void setMaterial(Material * material);
		void setCamera(Camera * camera);
		void setTransform(Transform * transform);
		void setParent(GameObject* parent);
		void setLight(Light* light);
	private:
		string m_Name;
		vector<Component*> m_Components;
		Mesh* m_Mesh;
		Material* m_Material;
		Camera* m_Camera;
		Transform* m_Transform;
		GameObject* m_Parent;
		Light* m_Light;
		vector<GameObject*> m_Children;
	protected:
};

#endif