#include "bird.h"
#include <GLFW/glfw3.h>
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <cmath>

Bird::Bird(const GLuint texture):
	texture(texture)
{
	init();
}
void Bird::init()
{
	position = glm::vec3(0.f, 0.f, 0.f);
	velocity = glm::vec3(1.f, 0.f, 0.f);
	gravity = glm::vec3(0.f, -0.0005f, 0.f);

	collider = new Circle();
	collider->center = glm::vec2(position.x, position.y);
	collider->radius = 0.1f;

}

void Bird::flap()
{
	//TODO handle flap state
	
	//velocity = glm::vec3(0.f, 0.03f, 0.f);
	velocity.y=0.03f;
}

void Bird::update(double deltaTime)
{
	velocity += gravity;
	position += velocity * (float)deltaTime;
	collider->center = glm::vec2(position.x, position.y);
}

void Bird::draw()
{
	glDepthMask(GL_FALSE);

	// Pitch (forward tilt in planespeak) calculation.
	float pitch = (float) atan(velocity.y)*5000; // TODO Trial-and-error value
	pitch = fmax(pitch, -90.f);
	pitch = (pitch + lastPitch*3)/4; // To smooth out the transition. Not effective on flap yet.

	glm::mat4 result = glm::mat4(1.0f);
	result = glm::translate(result, position);
	result = glm::rotate(result, pitch, glm::vec3(0.0f, 0.f, 1.f));
	result = glm::scale(result, glm::vec3(0.5f));

	glLoadMatrixf(glm::value_ptr(result));
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvf(GL_TEXTURE_2D,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glDepthMask(GL_FALSE);

	glBegin(GL_QUADS);
	glTexCoord2f(0.f,1.f); glVertex3f(-1.f, 1.f, 0.f);
    	glTexCoord2f(1.f,1.f); glVertex3f( 1.f, 1.f, 0.f);
	glTexCoord2f(1.f,0.f); glVertex3f( 1.f, -1.f, 0.f);
	glTexCoord2f(0.f,0.f); glVertex3f(-1.f, -1.f, 0.f);
	glEnd();
	glPopMatrix();
	
	glBindTexture(GL_TEXTURE_2D, 0);
	glDepthMask(GL_TRUE);
}

void Bird::reset()
{
	init();
}

glm::vec3 Bird::getPosition()
{
	return position;
}

Circle* Bird::getCollider()
{
	return collider;
}
