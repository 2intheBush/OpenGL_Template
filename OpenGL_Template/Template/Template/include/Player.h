#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "BaseClass.h"

class Player
{
public:
	Player();
	~Player(){};
	


	void Initialize();
	void UpdateVBO_IBO();
	void UpdateDraw();
	void DestroyPlayer();
	
	GLuint uiVBO;
	GLuint uiIBO;


};

#endif