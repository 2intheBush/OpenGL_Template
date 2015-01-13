#include "Stars.h"
#include <time.h>
#include <stdlib.h>

Vertex* MyStarShape = new Vertex[50];

Stars::Stars()
{
	Initialize();
}

void Stars::Initialize()
{

	// setting up star vertices
	for (int i = 0; i < 50; i++)
	{
		
		MyStarShape[i].positions[0] = rand() % 1024;
		MyStarShape[i].positions[1] = rand() % 720;
		MyStarShape[i].positions[2] = 0.0f;
		MyStarShape[i].positions[3] = 1.0f;
		MyStarShape[i].colors[0] = 1.0f;
		MyStarShape[i].colors[1] = 1.0f;
		MyStarShape[i].colors[2] = 1.0f;
		MyStarShape[i].colors[3] = 1.0f;
	};

	glGenBuffers(1, &uiVBO);
	glGenBuffers(1, &uiIBO);
}



void Stars::UpdateVBO_IBO()
{
	//check if vertex buffer succeeded
	if (uiVBO != 0)
	{
		//bind VBO
		glBindBuffer(GL_ARRAY_BUFFER, uiVBO);

		//allocate space on graphics card
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* 50, NULL, GL_STATIC_DRAW);

		//get pointer to allocate space on graphics card
		GLvoid* vSBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

		//copy to graphics card
		memcpy(vSBuffer, MyStarShape, sizeof(Vertex)* 50);

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
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 50 * sizeof(char), NULL, GL_STATIC_DRAW);
		//get pointer to newly allocated space on the graphics card
		GLvoid* iBuffer = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
		//specify the order we'd like to draw our vertices.
		//In this case they are in sequential order
		for (int i = 0; i < 50; i++)
		{
			((char*)iBuffer)[i] = i;
		}
		//unmap and unbind
		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}

void Stars::UpdateDraw()
{
	//bind both buffers
	glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiIBO);

	//specify where our vertex array is
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float)* 4));

	//draw to the screen
	glDrawElements(GL_POINTS, 50, GL_UNSIGNED_BYTE, NULL);

	//unbind buffers 
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Stars::DestroyStars()
{
	for (int i = 0; i < 50; i++)
	{
		delete &MyStarShape[i];
	}
}