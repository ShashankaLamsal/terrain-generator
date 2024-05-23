#include <glad/glad.h>
#include <glfw3.h>
#include <stdlib.h>
#include <iostream>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>



#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"texture.h"

  //TRIANGLE
/*
GLfloat vertices[] =
{                   // coordinate                       ||              colors      
    -0.5f       ,-0.5f * float(sqrt(3)) / 3         ,0.0f,      0.647f, 0.165f, 0.165f,        //bottom left   :0
    0.5f        ,-0.5f * float(sqrt(3)) / 3         ,0.0f,      0.180f, 0.545f, 0.341f,        //bottom right  :1
    0.0f        ,(0.5f * float(sqrt(3)) * 2) / 3    ,0.0f,      0.275f, 0.510f, 0.706f,        //top          :2

    -0.5f / 2   ,0.5f * float(sqrt(3)) / 6          ,0.0f,      0.647f, 0.165f, 0.165f,        //inner left   :3
    0.5f / 2    ,0.5f * float(sqrt(3)) / 6          ,0.0f,      0.180f, 0.545f, 0.341f,        //inner right  :4
    0.0f        ,-0.5f * float(sqrt(3)) / 3         ,0.0f,       0.275f, 0.510f, 0.706f        //inner bottom    :5

};
*/

//SQUARE
GLfloat vertices[] =
{             // coordinate       ||              colors        ||    texture relation
    -0.5f       ,0.0f      ,-0.5f    ,      0.275f, 0.510f, 0.706f,    0.0f,0.0f,      //bottom left   :0
    0.5f        ,0.0f     , -0.5f    ,      0.180f, 0.545f, 0.341f,    1.0f,0.0f,      //bottom right  :1
    0.5f        ,0.0f      ,0.5f    ,      0.275f, 0.510f, 0.706f,    1.0f,1.0f,      //top  right    :2
    -0.5f       ,0.0f      ,0.5f    ,      0.180f, 0.545f, 0.341f,    0.0f,1.0f,      //  top left    :3
    0.0f       ,0.8f      ,0.0f   ,      0.180f, 0.545f, 0.341f,    0.0f,1.0f         //top pyramid: 4

};

GLuint indices[] = {

    0,3,2,  //upper left triangle
    0,2,1,  //lower right triangle
    0,1,4,
    1,2,4,
    2,3,4,
    3,0,4
    
};

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    int height = 800, width = 800;

    //creatinf glfw window context
    GLFWwindow* window =glfwCreateWindow(width, height,"Display Window", NULL, NULL);

    //check if window has been created
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl ;
        glfwTerminate();
        return -1;
    }
    //use the created window
    glfwMakeContextCurrent(window);

    gladLoadGL(); //load the required components of GL

    glViewport(0, 0, width, height);
    
    Shader shaderProgram("default.vert", "default.frag");
    //create references for Vertex Array Object and Vertex Buffer Object
    // for vram use, ARRAY_BUFFER MOVING DATA FROM RAM TO VRAM
    //added EBO for indices

    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices,sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));


    // linking VBO attributes such as colors, co-ordinates and texture ratio to the  VAO
    VAO1.LinkAttrib(VBO1, 0, 3,  GL_FLOAT, 8 * sizeof(float), (void*) 0);
    VAO1.LinkAttrib(VBO1, 1, 3,  GL_FLOAT, 8 * sizeof(float), (void*) (3*sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2,  GL_FLOAT, 8 * sizeof(float), (void*) (6*sizeof(float)));


    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    //getting a uniform value called scale
    GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");


    
    std::string texPath = "/Resources Files/textures/";
    
    //naming the texture
    Texture tameCat("cat_.bmp", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    tameCat.texUnit(shaderProgram, "tex0", 0);

    float rotation = 0.0f;
    double prevTime = glfwGetTime();

    glEnable(GL_DEPTH_TEST);
    //MAIN WHILE LOOP
    while (!glfwWindowShouldClose(window))
    {

        glClearColor(0.4f, 0.4f, 0.4f, 1.0f);

        //clear the back buffer and assign new color to it AS WELL AS  clearing the depth buffer everytime
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //telling opengl to use this shader program
        shaderProgram.Activate();

        //basic timer
        double crntTime = glfwGetTime();
        if (crntTime - prevTime >= 1/30)
        {
            rotation += 0.05f;
            prevTime = crntTime;
        }

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 proj = glm::mat4(1.0f);

        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));

        view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
        proj = glm::perspective(glm::radians(45.0f),(float)(800/800), 0.1f, 100.0f);   //perspective with FOV, Res and nearplane-farplane
       
        int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));


        //assigning value to the  uniform SCALE 's location (uniID)
        glUniform1f(uniID, 0.1f);

        tameCat.Bind();
        VAO1.Bind();    
        
        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
        //glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);

        glfwPollEvents(); //poll for GLFW events
    }

    //deleting objects before program termination
    VAO1.Delete();
    VBO1.Delete();
    tameCat.Delete();

    //EBO1.Delete();
    shaderProgram.Delete();


    //delete window before ending the program
    glfwDestroyWindow(window);

    //terminate glfw
    glfwTerminate();
    return 0;
}