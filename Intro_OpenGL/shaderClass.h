#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<string.h>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

std::string get_file_contents(const char* filename);

class Shader
{
	public:

		GLuint ID;

		//builds the shader program from 2 different shader files
		Shader(const char* vertexFile, const char* fragmentFile);

		void Activate();
		void Delete();

	private:

		// checks if different Shaders have compiled properly
		void compileErrors(unsigned int shader, const char* type);



};

#endif
