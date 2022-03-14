#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

int main() 
{
	glfwInit();
	//newcomment

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "Okno", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "piwo" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}
	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;

}