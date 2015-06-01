#pragma once

#include "glm/glm.hpp"
#include <algorithm>

struct Rect {
	glm::vec2 min, max;
};

struct Circle {
	//Center position
	glm::vec2 center;
	float radius;
};

class Collision {
	public :
		static bool intersects(const Rect & rect, const Circle & circle)
		{
			// Find the closest point to the circle within the rectangle
			float closestX = clamp(circle.center.x, rect.min.x, rect.max.x);
			float closestY = clamp(circle.center.y, rect.min.y, rect.max.y);

			// Calculate the distance between the circle's center and this closest point
			float distanceX = circle.center.x - closestX;
			float distanceY = circle.center.y - closestY;

			// If the distance is less than the circle's radius, an intersection occurs
			float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);
			return distanceSquared < (circle.radius * circle.radius);
		}

		//Checks whether any part of the Obstacle's collider is inside the Rect argument
		static bool intersects(const Rect & rect1, const Rect & rect2)
		{
			return !(rect1.max.x < rect2.min.x
					|| rect2.max.x < rect1.min.x
					|| rect1.max.y < rect2.min.y
					|| rect2.max.y < rect1.min.y);
		}

	private :
		static float clamp(float n, float lower, float upper) {
			return std::max(lower, std::min(n, upper));
		}
};
