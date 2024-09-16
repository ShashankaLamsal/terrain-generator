#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/glad.h>
#include<glm/glm.hpp>
#include<vector>
struct Vertex {
	glm::vec3 position;  // Vertex position
	glm::vec3 normal;    // Vertex normal
	glm::vec3 color;     // Vertex color (r, g, b)
};
class VBO
{
	public:
		GLuint ID;
		

		//constructor that generates the VBO and links it to the vertices
		//voxel
		// //VBO(GLfloat* vertices, GLsizeiptr size);
		//low-poly
		VBO(std::vector<Vertex>& vertices);

		void Bind();
		void Unbind();
		void Delete();
		
};


#endif