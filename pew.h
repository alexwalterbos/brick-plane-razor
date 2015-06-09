#pragma once

#include "glm/glm.hpp"
#include "tex.h"

class Pew {
	public: 
		Pew(const GLuint texture, glm::vec3 pos);
		void draw();
	private: 
		glm::vec3 position;
		const GLuint texture;
};

