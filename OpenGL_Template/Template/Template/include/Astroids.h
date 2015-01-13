#ifndef _ASTROIDS_H_
#define _ASTROIDS_H_

#include "BaseClass.h"

class Astroids
{
public:
	Astroids();
	~Astroids(){};


	void Initialize();
	void UpdateVBO_IBO();
	void UpdateDraw();
	void DestroyPlayer();

	GLuint uiVBO;
	GLuint uiIBO;
};

#endif