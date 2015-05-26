#include "bird.h"
#include <stdlib.h>
#include <iostream>

Bird::Bird(const Texture& texture):
	texture(texture)
{
}

void Bird::flap()
{
	//TODO handle flap state
}

void Bird::update(double deltaTime)
{
	std::cout << "Bird got update with timing " << deltaTime  <<std::endl;
	//TODO handle actual flap consequence here
}

void Bird::draw()
{
	//TODO pretty bird here
}

Circle Bird::getBoundary()
{
	return boundary;
}
