#include"VBO.h"


//VBO::VBO(GLfloat* vertices, GLsizeiptr size)
VBO::VBO(std::vector<Vertex>& vertices)
{
	glGenBuffers(1, &ID);

	glBindBuffer(GL_ARRAY_BUFFER, ID); //bind VBO specifying it is gl_array_buffer

	//pass the vertices to the Buffer(VBO)
	//voxel
	//glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	//lowpoly
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

}

void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}




void VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}