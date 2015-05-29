#include "tex.h"
#include <SOIL/SOIL.h>
#include <stdlib.h>
#include <iostream>
#include <stdexcept>

using namespace std;

GLuint loadTextureFromFile(char const* fileName)
{
	GLuint tex_2d = SOIL_load_OGL_texture(fileName, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
			SOIL_FLAG_POWER_OF_TWO
			| SOIL_FLAG_MIPMAPS
			| SOIL_FLAG_MULTIPLY_ALPHA
			| SOIL_FLAG_COMPRESS_TO_DXT
			| SOIL_FLAG_DDS_LOAD_DIRECT
			| SOIL_FLAG_INVERT_Y
			);

	if(tex_2d == 0) 
	{
		throw std::invalid_argument("Failed to load texture");
	}

    	return tex_2d;
}
