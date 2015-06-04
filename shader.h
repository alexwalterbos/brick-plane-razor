#pragma once

#include <map>
#include <string>
#include <fstream>
#include <GLFW/glfw3.h>

using namespace std;

class Shader {
	private:
		GLuint compile(GLuint type, string file_name);
		map<string, GLuint> attributeMap;
		map<string, GLuint> uniformMap;
	protected:
		GLuint prog;
	public:
		Shader(string vertex_file, string fragment_file);
		Shader(string vertex_file, string fragment_file, string geometry_file);
		~Shader();
		void use();
		void disable();
		void addAttribute(string attributeLocation);
		void addUniform(string uniformLocation);
		GLuint attribute(string attributeLocation);
		GLuint uniform(string uniformLocation);
};
