#pragma once

#include "glm/glm.hpp"
#include "tex.h"
#include "col.h"

using namespace std;

class Bullet 
{
	public:
		Bullet(const vector<GLuint> texture, glm::vec3 pos, glm::vec3 vel, const float scale);
		void draw();
		void update(double deltaTime);
		Circle getCollider();
		glm::vec3 getPosition();
	private:
		glm::vec3 position, velocity;
		float rotation;
		const float scale;
		Circle collider;
		const vector<GLuint> textures;
};

