#ifndef OBSTACLE_H_
#define OBSTACLE_H_
		
#pragma once

#include "col.h"
#include <memory>

using namespace std;

float clamp(float n, float lower, float upper);

class Obstacle {
	public:
		Obstacle(unique_ptr<Rect> collider);
		bool collides(const Circle & circle);
		bool inside(const Rect & rect);
	private:
		unique_ptr<Rect> collider;
};

#endif
