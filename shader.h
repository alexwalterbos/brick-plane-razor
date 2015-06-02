#pragma once

#include <fstream>
#include <GLFW/glfw3.h>

using namespace std;

class Shader {
	private:
		GLuint vertex_shader, geometry_shader, fragment_shader, prog;
		GLuint compile(GLuint type, string file_name);
	public:
		Shader(string vertex_file, string fragment_file);
		Shader(string vertex_file, string fragment_file, string geometry_file);
		~Shader();
		void useProgram();
};
