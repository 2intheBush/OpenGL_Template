#include "Astroids.h"

TextureVertex* MyAstroidsShape = new TextureVertex[4];

glm::vec4 AstroidValues;

Astroids::Astroids()
{
	Initialize();
}

void Astroids::Initialize()
{
	orthographicProjection = getOrtho(0, 1024, 0, 720, 0, 100);
	height = width = 50, bpp = 4;
	//setting up vertices
	MyAstroidsShape[0].positions[0] = 1024 / 2.0 + 100;
	MyAstroidsShape[0].positions[1] = 720 / 2.0;
	MyAstroidsShape[1].positions[0] = 1024 / 2.0 + 100;
	MyAstroidsShape[1].positions[1] = 720 / 2.0 + 50.0f;
	MyAstroidsShape[2].positions[0] = 1024 / 2.0f + 150.0f;
	MyAstroidsShape[2].positions[1] = 720 / 2.0f + 50.0f;
	MyAstroidsShape[3].positions[0] = 1024 / 2.0f + 150.0f;
	MyAstroidsShape[3].positions[1] = 720 / 2.0f;

	MyAstroidsShape[0].u = 0.0f;
	MyAstroidsShape[0].v = 1.0f;
	MyAstroidsShape[1].u = 0.0f;
	MyAstroidsShape[1].v = 0.0f;
	MyAstroidsShape[2].u = 1.0f;
	MyAstroidsShape[2].v = 0.0f;
	MyAstroidsShape[3].u = 1.0f;
	MyAstroidsShape[3].v = 1.0f;

	for (int i = 0; i < 4; i++)
	{
		MyAstroidsShape[i].positions[2] = 0.0f;
		MyAstroidsShape[i].positions[3] = 1.0f;
		MyAstroidsShape[i].colors[0] = 1.0f;
		MyAstroidsShape[i].colors[1] = 1.0f;
		MyAstroidsShape[i].colors[2] = 1.0f;
		MyAstroidsShape[i].colors[3] = 1.0f;
	}
	uiTextureID = loadTexture("resources\\images\\Astroid.png",width, height, bpp);
	
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
		glBufferData(GL_ARRAY_BUFFER, sizeof(TextureVertex)* 4, NULL, GL_STATIC_DRAW);

		//get pointer to allocate space on graphics card
		GLvoid* vSBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

		//copy to graphics card
		memcpy(vSBuffer, MyAstroidsShape, sizeof(TextureVertex)* 4);

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
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(char), NULL, GL_STATIC_DRAW);
		//get pointer to newly allocated space on the graphics card
		GLvoid* iBuffer = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
		//specify the order we'd like to draw our vertices.
		//In this case they are in sequential order
		for (int i = 0; i < 4; i++)
		{
			((char*)iBuffer)[i] = i;
		}
		//unmap and unbind
		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}

void Astroids::UpdateDraw(GLuint uniformLocation, GLuint shaderProgram)
{
	glUseProgram(shaderProgram);
	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, orthographicProjection);

	//bind texture
	glBindTexture(GL_TEXTURE_2D, uiTextureID);
	glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiIBO);
	
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(TextureVertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(TextureVertex), (void*)(sizeof(float)* 4));
	//now we have UVs, we need to send that info to the graphics card
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(TextureVertex), (void*)(sizeof(float)* 8));

	//draw to the screen
	glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_BYTE, NULL);

	//unbind buffers 
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}