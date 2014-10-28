#include "Mesh.h"
#include "Component.h"
#include "Vertex.h"

#include <gl\glew.h>
//maths headers
#include <glm/glm.hpp>
using glm::mat4;
using glm::vec3;
using glm::vec2;

void Mesh::init()
{
	glGenVertexArrays(1, &m_VAO);
	glGenVertexArrays(1, &m_VBO);
	glGenVertexArrays(1, &m_EBO);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)sizeof(vec3));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)(sizeof(vec3) + sizeof(vec2)));
}

void Mesh::destroy()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_EBO);
	glDeleteBuffers(1, &m_VBO);

}

void Mesh::copyIndexData(int count, int stride, void** data)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*stride, data, GL_STATIC_DRAW);
	m_IndexCount = count;
}

void Mesh::copyVertexData(int count, int stride, void** data)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, count*stride, data, GL_STATIC_DRAW);
	m_VertexCount = count;
}

void Mesh::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBindVertexArray(m_VAO);

}

GLuint Mesh::getIndex()
{
	return m_IndexCount;
}

GLuint Mesh::getVertex()
{
	return m_VertexCount;
}