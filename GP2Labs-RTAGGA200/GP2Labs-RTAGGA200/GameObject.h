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

		Mesh* getMesh();
		void setMesh(Mesh * mesh);
		Material* getMaterial();
		void setMaterial(Material * material);
		Camera* getCamera();
		void setCamera(Camera * camera);
		Transform* getTransform();
		void setTransform(Transform * transform);
	private:
		string m_Name;
		vector<Component*> m_Components;
		Mesh* m_Mesh;
		Material* m_Material;
		Camera* m_Camera;
		Transform* m_Transform;
	protected:
};

#endif