#pragma once
#include "GL\glew.h"
#include "GL\wglew.h"
//glew has to go first.
#include "GLFW\glfw3.h"

struct Vertex
{
	float positions[4];
	float colors[4];
};

class BaseClass
{
protected:
	BaseClass(){};
	~BaseClass(){};

public:

};

