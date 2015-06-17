#pragma once

#include "vertex.h"
#include <vector>

class Mesh {
	public:
		Mesh();
		inline Mesh (const std::vector<Vertex> & v) : vertices (v)  {}
		std::vector<Vertex> vertices;

		bool loadMesh(const char * filename);
		void draw();

};

