#ifndef COL_H_
#define COL_H_

#include "glm/glm.hpp"

struct Rect {
	glm::vec2 min, max;
};

struct Circle {
	//Center position
	glm::vec2 center;
	float radius;
};

#endif
