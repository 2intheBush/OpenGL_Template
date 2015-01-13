#ifndef _STARS_H_
#define _STARS_H_

#include "BaseClass.h"

class Stars
{
public:
	Stars();
	~Stars(){};
	
	void Initialize();
	void UpdateVBO_IBO();
	void UpdateDraw();
	void DestroyStars();

	GLuint uiVBO;
	GLuint uiIBO;


};

#endif