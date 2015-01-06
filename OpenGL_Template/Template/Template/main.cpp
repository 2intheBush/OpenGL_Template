#include "GL\glew.h"
#include "GL\wglew.h"
#include "GLFW\glfw3.h"


int main()
{
	if (!glfwInit())
	{
		return -1;
	}

	//create a windowed mode window and its OpenGL context
	GLFWwindow* window;
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	//make the window's context current
	glfwMakeContextCurrent(window);

	//Start GLEW
	if (glewInit() != GLEW_OK)
	{
		//OpenGL didn't Start up... Shutdown GLFW and return an error code
		glfwTerminate();
		return -1;
	}
	//loop until the user closes the window
	while (!glfwWindowShouldClose(window))
	{
		//draw code goes here

		//swap front and back buffers
		glfwSwapBuffers(window);

		//poll for and process events
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
