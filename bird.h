#pragma once 

#include "glm/glm.hpp"
#include "col.h"
#include "tex.h"
#include "pew.h"
#include <memory>

using namespace std;

class Bird {
	public:
		Bird(const GLuint texture);
		void flap();
		unique_ptr<Pew> fire();
		void update(double deltaTime);
		void draw();
		Circle* getCollider();
		glm::vec3 getPosition();
		void reset();
	private:
		glm::vec3 position, velocity, gravity;
		float size, lastPitch;
		Circle* collider;
		const GLuint texture;
		void init();
};
