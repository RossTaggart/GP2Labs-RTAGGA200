#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>

#include "Component.h"
#include <gl\glew.h>
#include <glm/glm.hpp>

using glm::vec4;

using namespace std;

class Material : public Component
{
	public:
		Material();
		~Material();
		void destroy();
		bool loadShader(const string& vertexShader, const string& fragmentShader);
		void Bind();

		GLint getUniformLocation(const string& name);
		vec4& getAmbientColor();
		vec4& getDiffuseColor();

		void setAmbientColor(float r, float g, float b, float a);
		void setDiffuseColor(float r, float g, float b, float a);
	private:
		GLuint m_ShaderProgram;
		vec4 m_AmbientColor;
		vec4 m_DiffuseColor;
	protected:
};

#endif