#include "bullet.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <glm/ext.hpp>
#include <iostream>
#include <cmath>

Bullet::Bullet(const vector<GLuint> textures, const float scale, const Material mat, glm::vec3 pos, glm::vec3 direction):
	scale(scale), textures(textures), material(mat)
{
	position = pos;
	velocity = direction * 5.f;
	rotation = 0.0f;
	collider = Circle();
	collider.center = glm::vec2(position.x, position.y);
	collider.radius = 0.05f;
}

void Bullet::draw()
{
	float pitch = (float) atan2(velocity.y, velocity.x) * 180 / PI;

	glDepthMask(GL_FALSE);
	glm::mat4 result = glm::mat4(1.0f);
	result = glm::translate(result, position);
	result = glm::rotate(result, pitch, glm::vec3(0.0f, 0.0f, 1.0f));
	result = glm::scale(result, glm::vec3(scale));

	glLoadMatrixf(glm::value_ptr(result));
	glBindTexture(GL_TEXTURE_2D, textures[floor(fmod(rotation, 360) / 45)]);

	glTexEnvf(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glDepthMask(GL_FALSE);

	glBegin(GL_QUADS);
	glTexCoord2f(0.f,1.f); glVertex3f(-0.5f,  0.5f, 0.f);
    	glTexCoord2f(1.f,1.f); glVertex3f( 0.5f,  0.5f, 0.f);
	glTexCoord2f(1.f,0.f); glVertex3f( 0.5f, -0.5f, 0.f);
	glTexCoord2f(0.f,0.f); glVertex3f(-0.5f, -0.5f, 0.f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
	glDepthMask(GL_TRUE);
}

void Bullet::update(double deltaTime)
{
	rotation += 360.f * (float) deltaTime * 1.5f; // last term indicates rotations/sec
	position += velocity * (float) deltaTime;
	collider.center = glm::vec2(position.x, position.y);
}

Circle Bullet::getCollider()
{
	return collider;
}

glm::vec3 Bullet::getPosition()
{
	return position;
}

Material Bullet::getMaterial()
{
	return material;
}
