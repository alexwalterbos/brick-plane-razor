#pragma once

#include <GLFW/glfw3.h>

class Texture {
	public:
		Texture(GLuint id);
		GLuint getId();
	private:
		GLuint id;
};

Texture loadTextureFromFile(char const* fileName);
