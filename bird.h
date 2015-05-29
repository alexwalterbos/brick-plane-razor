#pragma once 

#include "glm/glm.hpp"
#include "col.h"
#include "tex.h"

class Bird {
	public:
		Bird(const GLuint texture);
		void flap();
		void update(double deltaTime);
		void draw();
		Circle getBoundary();
		glm::vec2 getPosition();
	private:
		glm::vec2 position, velocity;
		float size;
		Circle boundary;
		const GLuint texture;
};
