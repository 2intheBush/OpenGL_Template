#include "Astroids.h"

Vertex* MyAstroidsShape = new Vertex[6];

Astroids::Astroids()
{
	Initialize();
}

void Astroids::Initialize()
{
	//setting up vertices
	MyAstroidsShape[0].positions[0] = 1024 / 2.0;
	MyAstroidsShape[0].positions[1] = 720 / 2.0;
	MyAstroidsShape[1].positions[0] = 1024 / 2.0 - 20.0f;
	MyAstroidsShape[1].positions[1] = 720 / 2.0 - 10.0f;
	MyAstroidsShape[2].positions[0] = 1024 / 2.0f + 20.0f;
	MyAstroidsShape[2].positions[1] = 720 / 2.0f + 5.0f;
	MyAstroidsShape[3].positions[0] = 1024 / 2.0f + 20.0f;
	MyAstroidsShape[3].positions[1] = 720 / 2.0f;
	MyAstroidsShape[4].positions[0] = 1024 / 2.0f + 20.0f;
	MyAstroidsShape[4].positions[1] = 720 / 2.0f + 10.f;
	MyAstroidsShape[5].positions[0] = 1024 / 2.0f - 10.0f;
	MyAstroidsShape[5].positions[1] = 720 / 2.0f + 20.0f;
	for (int i = 0; i < 6; i++)
	{
		MyAstroidsShape[i].positions[2] = 0.0f;
		MyAstroidsShape[i].positions[3] = 1.0f;
		MyAstroidsShape[i].colors[0] = 0.0f;
		MyAstroidsShape[i].colors[1] = 0.0f;
		MyAstroidsShape[i].colors[2] = 1.0f;
		MyAstroidsShape[i].colors[3] = 1.0f;
	}
	glGenBuffers(1, &uiVBO);
	glGenBuffers(1, &uiIBO);
}



void Astroids::UpdateVBO_IBO()
{
	//check if vertex buffer succeeded
	if (uiVBO != 0)
	{
		//bind VBO
		glBindBuffer(GL_ARRAY_BUFFER, uiVBO);

		//allocate space on graphics card
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* 6, NULL, GL_STATIC_DRAW);

		//get pointer to allocate space on graphics card
		GLvoid* vSBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

		//copy to graphics card
		memcpy(vSBuffer, MyAstroidsShape, sizeof(Vertex)* 6);

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
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(char), NULL, GL_STATIC_DRAW);
		//get pointer to newly allocated space on the graphics card
		GLvoid* iBuffer = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
		//specify the order we'd like to draw our vertices.
		//In this case they are in sequential order
		for (int i = 0; i < 6; i++)
		{
			((char*)iBuffer)[i] = i;
		}
		//unmap and unbind
		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}

void Astroids::UpdateDraw()
{
	//bind both buffers
	glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiIBO);

	//specify where our vertex array is
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float)* 4));

	//draw to the screen
	glDrawElements(GL_TRIANGLE_FAN, 6, GL_UNSIGNED_BYTE, NULL);

	//unbind buffers 
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}