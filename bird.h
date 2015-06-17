#pragma once 

#include "glm/glm.hpp"
#include "col.h"
#include "tex.h"
#include "pew.h"
#include "bullet.h"
#include "material.h"
#include <memory>

using namespace std;

class Bird {
	public:
		Bird(const GLuint texture, const vector<GLuint> texs);
		void flap();
		unique_ptr<Bullet> fire(Material a);
		void update(double deltaTime);
		void draw();
		Circle getCollider();
		glm::vec3 getPosition();
		void reset();
	private:
		glm::vec3 position, velocity, gravity;
		float size, lastPitch;
		Circle collider;
		const GLuint texture;
		const vector<GLuint> bullettex;
		void init();
};
