#include "obstacle.h"
#include <stdlib.h>

Obstacle::Obstacle(unique_ptr<Rect> rect)
{
	collider = move(rect);
}

bool Obstacle::collides(const Circle & circle)
{
	// Find the closest point to the circle within the rectangle
	float closestX = clamp(circle.center.x, collider->min.x, collider->max.x);
	float closestY = clamp(circle.center.y, collider->min.y, collider->max.y);

	// Calculate the distance between the circle's center and this closest point
	float distanceX = circle.center.x - closestX;
	float distanceY = circle.center.y - closestY;

	// If the distance is less than the circle's radius, an intersection occurs
	float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);
	return distanceSquared < (circle.radius * circle.radius);
}

//Checks whether any part of the Obstacle's collider is inside the Rect argument
bool Obstacle::inside(const Rect & rect)
{
	return !(collider->max.x < rect.min.x
			|| rect.max.x < collider->min.x
			|| collider->max.y < rect.min.y
			|| rect.max.y < collider->min.y);
}

float clamp(float n, float lower, float upper) {
	return std::max(lower, std::min(n, upper));
}
