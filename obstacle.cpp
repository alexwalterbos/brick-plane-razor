#include "obstacle.h"
#include <stdlib.h>

Obstacle::Obstacle(Rect* rect): collider(rect)
{
}

bool Obstacle::collides(Circle* circle)
{
	// Find the closest point to the circle within the rectangle
	float closestX = clamp(circle.X, collider->min.x, collider->max.x);
	float closestY = clamp(circle.Y, collider->min.y, collider->max.y);

	// Calculate the distance between the circle's center and this closest point
	float distanceX = circle.X - closestX;
	float distanceY = circle.Y - closestY;

	// If the distance is less than the circle's radius, an intersection occurs
	float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);
	return distanceSquared < (circle->radius * circle->radius);
}

float clamp(float n, float lower, float upper) {
  return std::max(lower, std::min(n, upper));
}
