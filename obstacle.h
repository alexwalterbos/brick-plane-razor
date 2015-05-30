#pragma once

#include "col.h"

class Obstacle {
	public:
		Obstacle();
		bool collides(Bird* bird);
	private:
		const Rect* collider;
		float clamp(float n, float lower, float upper);
};
