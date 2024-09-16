#include"EBO.h"


//EBO::EBO(GLuint* indices, GLsizeiptr size)
EBO::EBO(std::vector<GLuint>& indices)
{
	glGenBuffers(1, &ID);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID); //bind VBO specifying it is gl_array_buffer

	//pass the vertices to the Buffer(VBO) in GPU
	//voxel
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
	//lowpoly
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
}

void EBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete()
{
	glDeleteBuffers(1, &ID);
}