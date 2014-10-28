#include "Mesh.h"
#include "Component.h"

#include <gl\glew.h>

void Mesh::init()
{

}

void Mesh::destroy()
{

}

void Mesh::copyIndexData(int count, int stride, void** data)
{

}

void Mesh::copyVertexData(int count, int stride, void** data)
{

}

void Mesh::Bind()
{

}

GLuint Mesh::getIndex()
{
	return m_IndexCount;
}

GLuint Mesh::getVertex()
{
	return m_VertexCount;
}