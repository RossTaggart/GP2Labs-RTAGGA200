#include "Mesh.h"
#include "Component.h"
#include "Vertex.h"

#include <gl\glew.h>
//maths headers
#include <glm/glm.hpp>
using glm::mat4;
using glm::vec3;
using glm::vec2;

Mesh::Mesh()
{
	m_VertexCount = 0;
	m_IndexCount = 0;
	m_VBO = 0;
	m_EBO = 0;
	m_VAO = 0;
	m_Type = "Mesh";
}

Mesh::~Mesh()
{
	destroy();
}

void Mesh::init()
{
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glGenBuffers(1, &m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)sizeof(vec3));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)(sizeof(vec3) + sizeof(vec3)));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)(sizeof(vec3) + sizeof(vec3) + sizeof(vec2)));
}

void Mesh::destroy()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_EBO);
	glDeleteBuffers(1, &m_VBO);

}

void Mesh::copyIndexData(int count, int stride, void** data)
{
	m_IndexCount = count;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*stride, data, GL_STATIC_DRAW);
	
}

void Mesh::copyVertexData(int count, int stride, void** data)
{
	m_VertexCount = count;
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, count*stride, data, GL_STATIC_DRAW);
}

void Mesh::Bind()
{
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
}

GLuint Mesh::getIndex()
{
	return m_IndexCount;
}

GLuint Mesh::getVertex()
{
	return m_VertexCount;
}