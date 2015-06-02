#pragma once

#include <fstream>
#include <GLFW/glfw3.h>

using namespace std;

class Shader {
	private:
		GLuint compile(GLuint type, string file_name);
	protected:
		GLuint prog;
	public:
		Shader(string vertex_file, string fragment_file);
		Shader(string vertex_file, string fragment_file, string geometry_file);
		~Shader();
		void useProgram();
		virtual void bindAttributes() = 0;
		virtual void unbindAttributes() = 0;
};
