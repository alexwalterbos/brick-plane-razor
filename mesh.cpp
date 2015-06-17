#include "mesh.h"
#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>
#include "glm/ext.hpp"

Mesh::Mesh(){}

void Mesh::draw()
{
	glBegin(GL_TRIANGLES);
	for (size_t i=0;i<vertices.size();++i)
	{
		Vertex vert = vertices[i];
		glVertex3fv(glm::value_ptr(vert.p));
		glNormal3fv(glm::value_ptr(vert.n));
		glTexCoord2f(vert.t.x, vert.t.y);
	}
	glEnd();
}

bool Mesh::loadMesh(const char * filename)
{
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;

	FILE * file = fopen(filename, "r");
	if( file == NULL )
	{
	    cout << "Impossible to open the file!" << endl;
	    return false;
	}
	
	while( 1 )
	{
		char lineHeader[128];
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; 	
		if ( strcmp( lineHeader, "v" ) == 0 )
		{
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
			temp_vertices.push_back(vertex);
		}
		else if ( strcmp( lineHeader, "vt" ) == 0 )
		{
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y );
			temp_uvs.push_back(uv);
		}
		else if ( strcmp( lineHeader, "vn" ) == 0 )
		{
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
			temp_normals.push_back(normal);
		}
		else if ( strcmp( lineHeader, "f" ) == 0 )
		{
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
			if (matches != 9){
				cout << "File can't be parsed" << endl;
				return false;
			}
		
			for(size_t i = 0; i < 3; ++i) 
			{
				Vertex vert = Vertex(temp_vertices[vertexIndex[i]-1], temp_normals[normalIndex[i]-1], temp_uvs[uvIndex[i]-1]);
				vertices.push_back(vert);
			}

		}
	}
	
	fclose(file);
	
	return true;
}
