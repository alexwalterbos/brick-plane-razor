#pragma once

#include "glm/glm.hpp"
#include "tex.h"
#include "col.h"

class Bullet 
{
	public:
		Bullet(const GLuint texture, glm::vec3 pos, glm::vec3 vel);
		void draw();
		void update(double deltaTime);
		Circle* getCollider();
		glm::vec3 getPosition();
	private:
		glm::vec3 position, velocity;
		float rotation;
		Circle* collider;
		const GLuint texture;
};

