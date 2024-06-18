#include <glad/glad.h>
#include <glfw3.h>
#include <stdlib.h>
#include <iostream>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtc/noise.hpp>
#include<vector>




#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"texture.h"
#include"perlin.h"
#include"camera.h"


GLfloat vertices[] =
{
    // Coordinates        // Colors               // Texture Coordinates
    // Bottom face
    -0.5f, 0.0f, -0.5f,   0.275f, 0.510f, 0.706f,  0.0f, 0.0f, // bottom left
     0.5f, 0.0f, -0.5f,   0.180f, 0.545f, 0.341f,  0.0f, 0.0f, // bottom right
     0.5f, 0.0f,  0.5f,   0.275f, 0.510f, 0.706f,  0.0f, 0.0f, // top right
    -0.5f, 0.0f,  0.5f,   0.180f, 0.545f, 0.341f,  0.0f, 0.0f, // top left

    // Top face
    -0.5f, 1.0f, -0.5f,   0.224f, 0.675f, 0.224f,  0.9f, 0.9f, // bottom left
     0.5f, 1.0f, -0.5f,   0.224f, 0.675f, 0.224f,  1.0f, 0.9f, // bottom right
     0.5f, 1.0f,  0.5f,   0.224f, 0.675f, 0.224f,  1.0f, 1.0f, // top right
    -0.5f, 1.0f,  0.5f,   0.224f, 0.675f, 0.224f,  0.9f, 1.0f, // top left

    // Front face
    -0.5f, 0.0f,  0.5f,   0.180f, 0.545f, 0.341f,  0.0f, 0.0f, // bottom left
     0.5f, 0.0f,  0.5f,   0.275f, 0.510f, 0.706f,  1.0f, 0.0f, // bottom right
     0.5f, 1.0f,  0.5f,   0.275f, 0.510f, 0.706f,  1.0f, 1.0f, // top right
    -0.5f, 1.0f,  0.5f,   0.180f, 0.545f, 0.341f,  0.0f, 1.0f, // top left

    // Back face
    -0.5f, 0.0f, -0.5f,   0.275f, 0.510f, 0.706f,  0.0f, 0.0f, // bottom left
     0.5f, 0.0f, -0.5f,   0.180f, 0.545f, 0.341f,  1.0f, 0.0f, // bottom right
     0.5f, 1.0f, -0.5f,   0.275f, 0.510f, 0.706f,  1.0f, 1.0f, // top right
    -0.5f, 1.0f, -0.5f,   0.180f, 0.545f, 0.341f,  0.0f, 1.0f, // top left

    // Left face
    -0.5f, 0.0f, -0.5f,   0.275f, 0.510f, 0.706f,  0.0f, 0.0f, // bottom left
    -0.5f, 0.0f,  0.5f,   0.180f, 0.545f, 0.341f,  1.0f, 0.0f, // bottom right
    -0.5f, 1.0f,  0.5f,   0.275f, 0.510f, 0.706f,  1.0f, 1.0f, // top right
    -0.5f, 1.0f, -0.5f,   0.180f, 0.545f, 0.341f,  0.0f, 1.0f, // top left

    // Right face
     0.5f, 0.0f, -0.5f,   0.275f, 0.510f, 0.706f,  0.0f, 0.0f, // bottom left
     0.5f, 0.0f,  0.5f,   0.180f, 0.545f, 0.341f,  1.0f, 0.0f, // bottom right
     0.5f, 1.0f,  0.5f,   0.275f, 0.510f, 0.706f,  1.0f, 1.0f, // top right
     0.5f, 1.0f, -0.5f,   0.180f, 0.545f, 0.341f,  0.0f, 1.0f, // top left
};

GLuint indices[] = {
    0, 1, 2, 0, 2, 3,     // bottom face
    4, 5, 6, 4, 6, 7,     // top face
    8, 9, 10, 8, 10, 11,  // front face
    12, 13, 14, 12, 14, 15, // back face
    16, 17, 18, 16, 18, 19, // left face
    20, 21, 22, 20, 22, 23  // right face
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
    GLFWwindow* window = glfwCreateWindow(width, height, "Display Window", NULL, NULL);

    //check if window has been created
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
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

    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));


    // linking VBO attributes such as colors, co-ordinates and texture ratio to the  VAO
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));


    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    

    //naming the texture
    Texture tameCat("grass.bmp", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    tameCat.texUnit(shaderProgram, "tex0", 0);

    //inits the depth buffer
    glEnable(GL_DEPTH_TEST);

    //resolution along with distance from the model
    Camera camera( width, height, glm::vec3(0.0f, 8.0f, 40.0f));

    float radius = 20;
    
    //glm::vec3 cubePositions[1000];
    //IMPLEMENT ARRAYLIST USING VECTOR
    std::vector<glm::vec3> cubePositions(10000);
    std::vector<std::vector<float>> heightMap(width, std::vector<float>(height));
    int cubeSize ;
    int a ;
    cubeSize = 0;
    a = 0;

    

    float height11[10000];
    for (float x = -radius; x <= radius; ++x)
    {
        int b = 0;
        for (float z = -radius; z <= radius; ++z)
        {

            glm::vec2 pos = glm::vec2(a, b) * 0.2f;
            heightMap[a][b] = glm::perlin(pos);
            //heightMap[a][b] = perlin(pos.x, pos.y);

            //float y = rand() % 2;
            float y = heightMap[a][b];
            height11[cubeSize] = y/10;     //temp var for height
            cubePositions[cubeSize] = glm::vec3(x, y, z);
            cubeSize++;

            b++;

        }
        a++;

    }

    //used for visual effect to spawn cubes one by one 
    float elapsedTime = 0.0f;
    float spawnInterval = 0.1f; // Adjust the interval as needed (in seconds)
    unsigned int currentCubeIndex = 0;
    
    //for pulsing animation
    int subDivision = 1;    
    int subMax = 20;
    int pulseFlag = 0;
    float prevTime = 0;


    //MAIN WHILE LOOP
    while (!glfwWindowShouldClose(window))
    {
        //enablkes vsync
        glfwSwapInterval(1);

        glClearColor(0.4f, 0.4f, 0.4f, 1.0f);

        //clear the back buffer and assign new color to it AS WELL AS  clearing the depth buffer everytime
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //telling opengl to use this shader program
        shaderProgram.Activate();
       
        camera.Inputs(window);
        
        camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix"); //passing FOV, Near PLane, Far PLane


        //basic loop to check how many cubes to spawn per frame 
        /*
        float currentTime = glfwGetTime();
        elapsedTime += currentTime;
        
        if (elapsedTime >= spawnInterval && currentCubeIndex < cubeSize)
        {
            currentCubeIndex++;
            elapsedTime = 0.0f; // Reset elapsed time
        }
        */
        /*
        //for pulsing heightmap
        float currentTime = glfwGetTime();
        elapsedTime = currentTime - prevTime;
        if (elapsedTime >= spawnInterval)
        {
            prevTime = currentTime;

            if (pulseFlag==0)
            {
                if (subDivision == subMax)
                    pulseFlag = 1;
                for (unsigned int i = 0; i < cubeSize; i++)
                {
                    cubePositions[i][1] = subDivision * height11[i];


                }
                subDivision++;

                
            }
            else
            {
                if (subDivision == 0)
                    pulseFlag = 0;
                for (unsigned int i = 0; i < cubeSize; i++)
                {
                    cubePositions[i][1] = subDivision * height11[i];


                }
                subDivision--;
            }

            elapsedTime = 0.0f; // Reset elapsed time
        }
        */


        tameCat.Bind();
        VAO1.Bind();


        

        //glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
        //for (unsigned int i = 0; i < sizeof(cubePositions) / sizeof(cubePositions[0]); i++)

        //for (unsigned int i = 0; i < currentCubeIndex; i++) //FOR ONE-BY-ONE RENDER ANIMATION
        for (unsigned int i = 0; i < cubeSize; i++)
        {
            // Create a transformation matrix
            glm::mat4 model = glm::mat4(1.0f);
            

            // rotation
            //float angle =  3*currentTime* glm::radians(360.0f); // 360 degrees per second
            //model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));

            model = glm::translate(model, cubePositions[i]);
            
            // Send the model matrix to the shader
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));

            // Draw the cube
            glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
        }
        //////////////
        

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