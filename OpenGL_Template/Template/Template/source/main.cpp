#include "GL\glew.h"
#include "GL\wglew.h"
//glew has to go first.
#include "GLFW\glfw3.h"
#include <vector>
#include <string>
#include <fstream>
#include <time.h>

GLuint CreateShader(GLenum a_ShaderType, const char* a_strShaderFile);

GLuint CreateProgram(const char* a_vertex, const char* a_frag);

float* getOrtho(float left, float right, float bottom, float top, float a_fNear, float a_fFar);

struct Vertex
{
	float positions[4];
	float colors[4];
};
Vertex* myShape = new Vertex[3];
Vertex* StarShapes = new Vertex[25];



int main()
{
	srand(time(nullptr));
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

	//Vertex values
	/*	const float vertexPositions[] =
	{
		1024 / 2.0, 720 / 2.0 + 10.0f, 0.0f, 1.0f,
		1024 / 2.0 - 5.0f, 1024 / 2.0 - 5.0f, 0.0f, 1.0f,
		1024 / 2.0f + 5.0f, 720 / 2.0f - 10.0f, 0.0f, 1.0f,
	};

	const float vertexColors[] =
	{
		1.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 0.5f,
		0.0f, 0.0f, 1.0f, 1.0f,
	};*/
	//create shader program
	GLuint uiProgramFlat = CreateProgram("VertexShader.glsl", "FlatFragmentShader.glsl");

	//find the position of the matrix variable in the shader so we can send info there later
	GLuint MatrixIDFlat = glGetUniformLocation(uiProgramFlat, "MVP");

	//set up the mapping of the screen to pixel co-ordinates. 
	float* orthographicProjection = getOrtho(0, 1024, 0, 720, 0, 100);

	//setting up vertices
	myShape[0].positions[0] = 1024 / 2.0;
	myShape[0].positions[1] = 720 / 2.0 + 10.0f;
	myShape[1].positions[0] = 1024 / 2.0 - 5.0f;
	myShape[1].positions[1] = 720 / 2.0 - 10.0f;
	myShape[2].positions[0] = 1024 / 2.0f + 5.0f;
	myShape[2].positions[1] = 720 / 2.0f - 10.0f;
	for (int i = 0; i < 3; i++)
	{
		myShape[i].positions[2] = 0.0f;
		myShape[i].positions[3] = 1.0f;
		myShape[i].colors[0] = 0.0f;
		myShape[i].colors[1] = 0.0f;
		myShape[i].colors[2] = 1.0f;
		myShape[i].colors[3] = 1.0f;
	};

	// setting up star vertices
	for (int i = 0; i < 25; i++)
	{
		StarShapes[i].positions[0] = rand() % 1024;
		StarShapes[i].positions[1] = rand() % 720;
		StarShapes[i].positions[2] = 0.0f;
		StarShapes[i].positions[3] = 1.0f;
		StarShapes[i].colors[0] = 0.0f;
		StarShapes[i].colors[1] = 0.0f;
		StarShapes[i].colors[2] = 1.0f;
		StarShapes[i].colors[3] = 1.0f;
	};
	
	//create ID for a VBO
	GLuint uiVBO;
	glGenBuffers(1, &uiVBO);
	GLuint uiVBOS;
	glGenBuffers(1, &uiVBOS);

	//check if stars succeeded
	if (uiVBOS != 0)
	{
		//bind VBO
		glBindBuffer(GL_ARRAY_BUFFER, uiVBOS);

		//allocate space on graphics card
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* 25, NULL, GL_STATIC_DRAW);

		//get pointer to allocate space on graphics card
		GLvoid* vSBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

		//copy to graphics card
		memcpy(vSBuffer, StarShapes, sizeof(Vertex)* 25);

		//unmap and unbind
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	//check it succeeded
	if (uiVBO != 0)
	{
		//bind VBO
		glBindBuffer(GL_ARRAY_BUFFER, uiVBO);

		//allocate space on graphics card
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* 3, NULL, GL_STATIC_DRAW);

		//get pointer to allocate space on graphics card
		GLvoid* vBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

		//copy to graphics card
		memcpy(vBuffer, myShape, sizeof(Vertex)* 3);

		//unmap and unbind
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	//loop until the user closes the window
	while (!glfwWindowShouldClose(window))
	{
		//draw code goes here
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//enable Shaders
		glUseProgram(uiProgramFlat);

		glBindBuffer(GL_ARRAY_BUFFER, uiVBOS);

		//send our orthographic projection info to the shader
		glUniformMatrix4fv(MatrixIDFlat, 1, GL_FALSE, orthographicProjection);

		//enable vertex array state
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		//specify where our vertex array is
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float)*4));

		//glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
		//glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(float)* 4));

		//draw to screen
		glDrawArrays(GL_POINTS, 0, 25);
		
		glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float)* 4));

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		//swap front and back buffers
		glfwSwapBuffers(window);

		//poll for and process events
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

float* getOrtho(float left, float right, float bottom, float top, float a_fNear, float a_fFar)
{
	//to correspond with mat4 in the shader
	float* toReturn = new float[12];
	toReturn[0] = 2.0 / (right - left);;
	toReturn[1] = toReturn[2] = toReturn[3] = toReturn[4] = 0;
	toReturn[5] = 2.0 / (top - bottom);
	toReturn[6] = toReturn[7] = toReturn[8] = toReturn[9] = 0;
	toReturn[10] = 2.0 / (a_fFar - a_fNear);
	toReturn[11] = 0;
	toReturn[12] = -1 * ((right + left) / (right - left));
	toReturn[13] = -1 * ((top + bottom) / (top - bottom));
	toReturn[14] = -1 * ((a_fFar + a_fNear) / (a_fFar - a_fNear));
	toReturn[15] = 1;
	return toReturn;
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