#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/glad.h>



class VBO
{
	public:
		GLuint ID;

		//constructor that generates the VBO and links it to the vertices
		VBO(GLfloat* vertices, GLsizeiptr size);

		void Bind();
		void Unbind();
		void Delete();
};


#endif