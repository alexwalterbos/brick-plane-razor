#include "bird.h"
#include <GLFW/glfw3.h>
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/ext.hpp"
#include <stdlib.h>
#include <iostream>

Bird::Bird(const GLuint texture):
	texture(texture)
{
	position = glm::vec2(0.f, 0.f);
	velocity = glm::vec2(1.f, 0.f);
}

void Bird::flap()
{
	//TODO handle flap state
}

void Bird::update(double deltaTime)
{
	//TODO handle actual flap consequence here
}

void Bird::draw()
{
	glDepthMask(GL_FALSE);

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0.0f));
	transform = glm::scale(transform, glm::vec3(0.5f));

	glLoadMatrixf(glm::value_ptr(transform));
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

glm::vec2 Bird::getPosition()
{
	return position;
}

Circle Bird::getBoundary()
{
	return boundary;
}
