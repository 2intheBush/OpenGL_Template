#pragma once
#include "GL\glew.h"
#include "GL\wglew.h"
//glew has to go first.
#include "GLFW\glfw3.h"
#include "glm\glm.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include "SOIL.h"


struct TextureVertex
{
	float positions[4];
	float colors[4];
	float u;
	float v;
};

struct Vertex
{
	float positions[4];
	float colors[4];
};

class BaseClass
{
protected:
	BaseClass(){  };
	~BaseClass(){};


public:
	float* orthographicProjection;
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

};

unsigned int loadTexture(const char* a_pFilename, int & a_iWidth, int & a_iHeight, int & a_iBPP);


