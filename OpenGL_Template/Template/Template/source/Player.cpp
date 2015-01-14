#include "Player.h"

Vertex* MyShape = new Vertex[3];

Player::Player()
{
	Initialize();
}

void Player::Initialize()
{
	//setting up vertices
	MyShape[0].positions[0] = 1024 / 2.0;
	MyShape[0].positions[1] = 720 / 2.0 + 10.0f;
	MyShape[1].positions[0] = 1024 / 2.0 - 5.0f;
	MyShape[1].positions[1] = 720 / 2.0 - 10.0f;
	MyShape[2].positions[0] = 1024 / 2.0f + 5.0f;
	MyShape[2].positions[1] = 720 / 2.0f - 10.0f;
	for (int i = 0; i < 3; i++)
	{
		MyShape[i].positions[2] = 0.0f;
		MyShape[i].positions[3] = 1.0f;
		MyShape[i].colors[0] = 0.0f;
		MyShape[i].colors[1] = 0.0f;
		MyShape[i].colors[2] = 1.0f;
		MyShape[i].colors[3] = 1.0f; 
	};

	glGenBuffers(1, &uiVBO);
	glGenBuffers(1, &uiIBO);
}



void Player::UpdateVBO_IBO()
{
	//check if vertex buffer succeeded
	if (uiVBO != 0)
	{
		//bind VBO
		glBindBuffer(GL_ARRAY_BUFFER, uiVBO);

		//allocate space on graphics card
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* 3, NULL, GL_STATIC_DRAW);

		//get pointer to allocate space on graphics card
		GLvoid* vSBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

		//copy to graphics card
		memcpy(vSBuffer, MyShape, sizeof(Vertex)* 3);

		//unmap and unbind
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	//check if Index buffer succeeded
	if (uiIBO != 0)
	{
		//bind IBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiIBO);
		//allocate space for index info on the graphics card
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(char), NULL, GL_STATIC_DRAW);
		//get pointer to newly allocated space on the graphics card
		GLvoid* iBuffer = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
		//specify the order we'd like to draw our vertices.
		//In this case they are in sequential order
		for (int i = 0; i < 3; i++)
		{
			((char*)iBuffer)[i] = i;
		}
		//unmap and unbind
		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}

void Player::UpdateDraw()
{
	//bind both buffers
	glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiIBO);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	//specify where our vertex array is
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float)* 4));

	//draw to the screen
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, NULL);

	//unbind buffers 
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}