#include "tex.h"
#include <SOIL/SOIL.h>
#include <stdlib.h>
#include <iostream>
#include <stdexcept>
using namespace std;

GLuint loadTextureFromFile(char const* fileName)
{
	//Normal implementation, which suffers from inverted y-coordinates. Included for documentation reasons
//	GLuint texture;
//	glGenTextures(1, &texture);
//
//	glBindTexture(GL_TEXTURE_2D,texture);
// 
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
// 
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
// 
//	int width, height, channels;
//	unsigned char* image = SOIL_load_image(fileName, &width, &height, &channels, SOIL_LOAD_RGBA);
// 
//	if (!image) {
//		cout << "Failed to load texture: " << sizeof(image) << endl;
//	}
// 
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
// 
//	SOIL_free_image_data(image);
//	glBindTexture(GL_TEXTURE_2D,0);
//	
//	return texture;

	GLuint tex_2d = SOIL_load_OGL_texture(fileName, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
			SOIL_FLAG_POWER_OF_TWO
			| SOIL_FLAG_MULTIPLY_ALPHA
			| SOIL_FLAG_COMPRESS_TO_DXT
			| SOIL_FLAG_INVERT_Y
			);

	glBindTexture(GL_TEXTURE_2D, 0);
	if(tex_2d == 0) 
	{
		throw std::invalid_argument("Failed to load texture");
	}

    	return tex_2d;
}

