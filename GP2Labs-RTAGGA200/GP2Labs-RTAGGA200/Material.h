#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>

#include "Component.h"
#include <gl\glew.h>

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
	private:
		GLuint m_ShaderProgram;
	protected:
};

#endif