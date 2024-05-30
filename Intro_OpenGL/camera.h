#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H


#include <glad/glad.h>
#include <glfw3.h>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include"shaderClass.h"

class Camera
{
	public:
		glm::vec3 Position;
		glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

		int width;
		int height;

		float speed = 1.0f ;
		float sensitivity = 25.0f;
		// to prevent the camera from jumping around when first clicking left click
		bool firstClick = true;

		//camera constructor to set up initial values
		Camera(int width, int height, glm::vec3 Position);
		
		//updates and exports camera matrix to vertex shadder
		void Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform);

		//handles camera input
		void Inputs(GLFWwindow* window);
		
};

#endif