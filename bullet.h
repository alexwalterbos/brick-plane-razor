#pragma once

#include "glm/glm.hpp"
#include "tex.h"
#include "col.h"
#include "material.h"

using namespace std;

class Bullet 
{
	public:
		Bullet(const vector<GLuint> texture, const float scale, const Material mat, glm::vec3 pos, glm::vec3 vel);
		void draw();
		void update(double deltaTime);
		Circle getCollider();
		glm::vec3 getPosition();
		Material getMaterial();
	private:
		glm::vec3 position, velocity;
		float rotation;
		const float scale;
		Circle collider;
		const vector<GLuint> textures;
		const Material material;
};

