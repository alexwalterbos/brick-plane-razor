#pragma once

#include <GLFW/glfw3.h>

class Shader {
	private:
		GLuint vertex_shader, geometry_shader, fragment_shader, prog;
		template <int N> GLuint compile(GLuint type, char const *(&source)[N]);
	public:
		template <int N, int M> Shader(GLchar const * (&v_source)[N], GLchar const *(&f_source)[M]);
		template <int N, int M, int O> Shader(GLchar const * (&v_source)[N], GLchar const *(&f_source)[M], GLchar const * (&g_source)[O]);
		~Shader();
};
