#include "bird.h"
#include <stdlib.h>
#include <iostream>
#include <math.h>

Bird::Bird(const Texture& texture):
	texture(texture)
{
	position = vec2<double>(0,0);
	velocity = vec2<double>(0,0);
}

void Bird::flap()
{
	//TODO handle flap state
	std::cout << "FLAP" <<std::endl;
}

void Bird::update(double deltaTime)
{
	std::cout << "Bird got update with timing " << deltaTime  <<std::endl;
	std::cout << "Position: " << position.x << " " << position.y <<std::endl;
	std::cout << "Velocity: " << velocity.x << " " << velocity.y  <<std::endl;
	std::cout << "Length both: " << position.length() << " " << velocity.length()  <<std::endl;
	//TODO handle actual flap consequence here
}

void Bird::draw()
{
	//TODO pretty bird here
	glBegin(GL_TRIANGLES);
        glColor3f(0, 0, 1);
        glVertex3f(position.x, position.y-0.05, 0);
        glVertex3f(position.x + 0.2, position.y, 0);
        glVertex3f(position.x, position.y+0.05, 0);
        glEnd();
}

Circle Bird::getBoundary()
{
	return boundary;
}
