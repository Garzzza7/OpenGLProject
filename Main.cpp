#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"



// Vertices coordinates
GLfloat vertices[] =
{
	-0.5f, -0.5f , 0.0f, // Lower left corner
	0.5f, -0.5f , 0.0f, // Lower right corner
	0.0f, 0.5f, 0.0f, // Upper corner
	-0.5f , 0.5f , 0.0f, // Inner left
	0.5f , 0.5f , 0.0f, // Inner right
	0.0f, -0.5f , 0.0f // Inner down
};
GLfloat vertices1[] =
{
	-0.6f, -0.4f , 0.0f, // Lower left corner
	0.1f, -0.6f, 0.0f, // Lower right corner
	0.1f, 0.4f , 0.0f, // Upper corner
	-0.5f, 0.5f, 0.0f, // Inner left
	0.89f , 0.5f, 0.0f, // Inner right
	0.0f, -0.5f , 0.0f // Inner down
};

GLfloat vertices2[] =
{
	1.0f, 1.0f , 1.0f, // Lower left corner
	1.0f, 1.0f , 1.0f, // Lower right corner
	1.0f, 1.0f , 1.0f, // Upper corner
	1.0f, 1.0f , 1.0f, // Inner left
	1.0f, 1.0f , 1.0f, // Inner right
	1.0f, 1.0f , 1.0f // Inner down
};
// Indices for vertices order
GLuint indices[] =
{
	0, 3, 5, // Lower left triangle
	3, 2, 4, // Lower right triangle
	5, 4, 1 // Upper triangle
};
//Function responsible for scaling depending on the window size
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


int main()
{
	// Initialize GLFW
	glfwInit();
	


	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(1000, 1000, "Jebac", NULL, NULL);
	//Calling the scaling functionw
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	std::cout<<glfwVulkanSupported()<<std::endl;
	std::cout << glfwGetVersion << std::endl;
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 1000, y = 1000
	glViewport(0, 0, 1440, 800);



	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");



	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO VAO2;
	VAO VAO3;

	VAO1.Bind();
	VAO2.Bind();
	VAO3.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	VBO VBO2(vertices1, sizeof(vertices1));
	VBO VBO3(vertices2, sizeof(vertices2));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO to VAO
	VAO1.LinkVBO(VBO1, 0);
	VAO2.LinkVBO(VBO2, 0);
	VAO3.LinkVBO(VBO3, 0);
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	VAO2.Unbind();
	VBO2.Unbind();

	VAO3.Unbind();
	VBO3.Unbind();
	



	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		
		// Specify the color of the background
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		VAO2.Bind();
		VAO3.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES,24, GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	VAO2.Delete();
	VBO2.Delete();
	VAO3.Delete();
	VBO3.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}