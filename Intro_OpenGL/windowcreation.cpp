#include <glad/glad.h>
#include <glfw3.h>
#include <stdlib.h>
#include <iostream>


// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";


int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    

    //creatinf glfw window context
    GLFWwindow* window =glfwCreateWindow(800,600,"Display Window", NULL, NULL);

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

    glViewport(0, 0, 800, 800);

    GLfloat vertices[] =
    {
        -0.5f, -0.5f * float(sqrt(3)) / 3,0.5f, //bottom left
        0.5f, -0.5f * float(sqrt(3)) / 3,0.5f,  //bottom right
        0.0f, 0.5f ,0.0f    //top

    };

    //create vertex shader and take reference
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); //attaching the vS source(builtin) to vS obj(my creation)

    glCompileShader(vertexShader);  //compiles the shader object to machine code


    // create fragment Shader Object and get its reference
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // attaches Fragment Shader source to the Fragment Shader Object
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

    // Compile the fragment Shader obj into machine code
    glCompileShader(fragmentShader);

    //creating the main shader program
    GLuint shaderProgram = glCreateProgram();


    // attaching both vertexshader and fragment shader to the program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);   //links the shaders into a bundle type stuff, wrapping/linking


    //delete the created shaders (useless after linked)
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    //create references for Vertex Array Object and Vertex Buffer Object
    GLuint VAO,VBO;

    //generate VAO and VBO with 1 object each ?? multiple objects as in multiple batches?-----------------------
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    //make the VAO the CURRENT vertex array
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO); //bind VBO specifying it is gl_array_buffer

    //pass the vertices to the Buffer(VBO)
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices,GL_STATIC_DRAW);

    // Configure the Vertex Attribute so that OpenGL knows how to read the VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //bind both VAO and VBO to 0, so we dont modify the obj we created ??what are we binding, value?----------------------------
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    glClearColor(0.59f, 0.58f, 0.91f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);   //clear color back buffer and assign new color
    glfwSwapBuffers(window);        //sawp front and back buffer

    //MAIN WHILE LOOP
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.59f, 0.58f, 0.91f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);     //tell openglto use the vertex
        glDrawArrays(GL_TRIANGLES, 0, 3);       // object to draw ,starting index, no. of vertices
        glfwSwapBuffers(window);

        glfwPollEvents(); //poll for GLFW events
    }

    //deleting objects before program termination
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);


    //delete window before ending the program
    glfwDestroyWindow(window);

    //terminate glfw
    glfwTerminate();
    return 0;
}