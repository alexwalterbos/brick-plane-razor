#include "tex.h"
#include <SOIL/SOIL.h>

using namespace std;

Texture::Texture(GLuint id) 
{
	this->id = id;
}

GLuint Texture::getId() 
{
	return id;
}

Texture loadTextureFromFile(char const* fileName)
{
	int width, height;
	unsigned char* image = SOIL_load_image(fileName, &width, &height, 0, SOIL_LOAD_RGB);

    	// Generate the OpenGL texture object
    	GLuint textureId;
    	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
    	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
   	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	SOIL_free_image_data(image);
    	return Texture(textureId);
}
