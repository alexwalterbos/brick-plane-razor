#include "bird.h"
#include <GLFW/glfw3.h>
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/ext.hpp"
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <ctime>

Bird::Bird(const GLuint texture):
	texture(texture)
{
	position = glm::vec3(0.f, 0.f, 0.f);
	velocity = glm::vec3(0.f, 0.f, 0.f);
	time = 0.0;
}

void Bird::flap()
{
	//TODO handle flap state
}

void Bird::update(double deltaTime)
{
	time += deltaTime;
	velocity.y = cos(time)/100;

	position += velocity;
}

void Bird::draw()
{
	glDepthMask(GL_FALSE);


	glm::mat4 identity = glm::mat4(1.0f);
	glm::mat4 result = identity;
	result = glm::translate(result, position);
	result = glm::rotate(result, (float) atan(velocity.y)*5000, glm::vec3(0.0f, 0.f, 1.f));
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

glm::vec3 Bird::getPosition()
{
	return position;
}

Circle Bird::getBoundary()
{
	return boundary;
}
