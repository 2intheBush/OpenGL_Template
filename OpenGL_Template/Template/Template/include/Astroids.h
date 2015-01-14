#ifndef _ASTROIDS_H_
#define _ASTROIDS_H_

#include "BaseClass.h"

class Astroids:
	public BaseClass
{
public:
	Astroids();
	~Astroids(){};

	int height, width, bpp;
	void Initialize();
	void UpdateVBO_IBO();
	void UpdateDraw(GLuint uniformLocation, GLuint shaderProgram);
	void DestroyAstroids();

	GLuint uiVBO;
	GLuint uiIBO;
	GLuint uiTextureID;
};

#endif