#include "pew.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

Pew::Pew(const GLuint texture, glm::vec3 pos):
	texture(texture)
{
	position = pos;
}

void Pew::draw()
{
	glDepthMask(GL_FALSE);
	glm::mat4 result = glm::mat4(1.0f);
	result = glm::translate(result, position);
	result = glm::scale(result, glm::vec3(0.2f));
	
	glLoadMatrixf(glm::value_ptr(result));
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvf(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glDepthMask(GL_FALSE);

	glBegin(GL_QUADS);
	glTexCoord2f(0.f,1.f); glVertex3f(-1.f, 0.5f, 0.f);
    	glTexCoord2f(1.f,1.f); glVertex3f( 1.f, 0.5f, 0.f);
	glTexCoord2f(1.f,0.f); glVertex3f( 1.f, -0.5f, 0.f);
	glTexCoord2f(0.f,0.f); glVertex3f(-1.f, -0.5f, 0.f);
	glEnd();
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, 0);
	glDepthMask(GL_TRUE);
}

