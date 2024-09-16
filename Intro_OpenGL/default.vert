#version 330 core

//position coords
layout (location = 0) in vec3 aPos;
// normal position
layout (location = 1) in vec3 aNormal;
//color co-ords
layout (location = 2) in vec3 aColor;


out vec3 color;


uniform mat4 model;

uniform  mat4 camMatrix;

void main()
{
	//for normal vec4 object
 //gl_Position = vec4(aPos.x, aPos.y , aPos.z , 1.0);

 gl_Position = camMatrix*model * vec4 (aPos , 1.0);


 //assigns the data from vertex color to color
 color=aColor;
 //texCoord=aTex;

}