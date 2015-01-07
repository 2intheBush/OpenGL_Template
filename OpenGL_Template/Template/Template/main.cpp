#include "GL\glew.h"
#include "GL\wglew.h"
//glew has to go first.
#include "GLFW\glfw3.h"
#include "MathLib.h"
#include <vector>
#include <string>
#include <fstream>

GLuint CreateShader(GLenum a_ShaderType, const char* a_strShaderFile);

GLuint CreateProgram(const char* a_vertex, const char* a_frag);

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
	
	const float vertexPositions[] =
	{
		1024 / 2.0, 720 / 2.0 + 10.0f, 0.0f, 1.0f,
		1024 / 2.0 - 5.0f, 720 / 2.0f - 10.0f, 0.0f, 1.0f,
		1024 / 2.0f + 5.0f, 720 / 2.0f - 10.0f, 0.0f, 1.0f,
	};

	const float vertexColors[] =
	{
		1.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 0.5f,
		0.0f, 0.0f, 1.0f, 1.0f,
	};
	//create shader program
	GLuint uiProgramFlat = CreateProgram("VertexShader.glsl", "FlatFragmentShader.glsl");

	//find the position of the matrix variable in the shader so we can send info there later
	GLuint MatrixIDFlat = glGetUniformLocation(uiProgramFlat, "MVP");

	//set up the mapping of the screen to pixel co-ordinates. Try changing these values to see what happens.
	float* orthographicProjection = Matrix4::GetOrtho(0, 1024, 0, 720, 0, 100);

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

GLuint CreateShader(GLenum a_eShaderType, const char *a_strShaderFile)
{
	std::string strShaderCode;
	//open shader file
	std::ifstream shaderStream(a_strShaderFile);
	//if that worked ok, load file line by line
	if (shaderStream.is_open())
	{
		std::string Line = "";
		while (std::getline(shaderStream, Line))
		{
			strShaderCode += "\n" + Line;
		}
		shaderStream.close();
	}

	//convert to cstring
	char const *szShaderSourcePointer = strShaderCode.c_str();

	//create shader ID
	GLuint uiShader = glCreateShader(a_eShaderType);
	//load source code
	glShaderSource(uiShader, 1, &szShaderSourcePointer, NULL);

	//compile shader
	glCompileShader(uiShader);

	//check for compilation errors and output them
	GLint iStatus;
	glGetShaderiv(uiShader, GL_COMPILE_STATUS, &iStatus);
	if (iStatus == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(uiShader, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(uiShader, infoLogLength, NULL, strInfoLog);

		const char *strShaderType = NULL;
		switch (a_eShaderType)
		{
		case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
		case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
		}

		fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
		delete[] strInfoLog;
	}

	return uiShader;
}

GLuint CreateProgram(const char *a_vertex, const char *a_frag)
{
	std::vector<GLuint> shaderList;

	shaderList.push_back(CreateShader(GL_VERTEX_SHADER, a_vertex));
	shaderList.push_back(CreateShader(GL_FRAGMENT_SHADER, a_frag));

	//create shader program ID
	GLuint uiProgram = glCreateProgram();

	//attach shaders
	for (auto shader = shaderList.begin(); shader != shaderList.end(); shader++)
		glAttachShader(uiProgram, *shader);

	//link program
	glLinkProgram(uiProgram);

	//check for link errors and output them
	GLint status;
	glGetProgramiv(uiProgram, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(uiProgram, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(uiProgram, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}

	for (auto shader = shaderList.begin(); shader != shaderList.end(); shader++)
	{
		glDetachShader(uiProgram, *shader);
		glDeleteShader(*shader);
	}

	return uiProgram;
}