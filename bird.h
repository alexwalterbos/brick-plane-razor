#pragma once 

#include "vec.h"
#include "col.h"
#include "tex.h"

class Bird {
	public:
		Bird(const Texture& texture);
		void flap();
		void update(double deltaTime);
		void draw();
		Circle getBoundary();
	private:
		vec2<double> position, velocity;
		float size;
		Circle boundary;
		const Texture& texture;
		double posx, posy, velx, vely;
};
