#include <GL/glew.h>
#include "shader.h"
#include <string>
#include <stdexcept>

//Source: http://stackoverflow.com/a/2796153/4258911
template <int N>
GLuint Shader::compile(GLuint type, char const *(&source)[N]) 
{
	GLuint shader = glCreateShader(type);
        glShaderSource(shader, N, source, NULL);
        glCompileShader(shader);
        GLint compiled;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled) {
            GLint length;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
            std::string log(length, ' ');
            glGetShaderInfoLog(shader, length, &length, &log[0]);
            throw std::logic_error(log);
            return false;
        }
        return shader;
}

template <int N, int M>
Shader::Shader(GLchar const *(&v_source)[N], GLchar const *(&f_source)[M])
{
	vertex_shader = compile(GL_VERTEX_SHADER, v_source);
        fragment_shader = compile(GL_FRAGMENT_SHADER, f_source);
	geometry_shader = 0;
        prog = glCreateProgram();
        glAttachShader(prog, vertex_shader);
        glAttachShader(prog, fragment_shader);
        glLinkProgram(prog);
}

template <int N, int M, int O> 
Shader::Shader(GLchar const * (&v_source)[N], GLchar const *(&f_source)[M], GLchar const *(&g_source)[O])
{
	vertex_shader = compile(GL_VERTEX_SHADER, v_source);
	geometry_shader = compile(GL_GEOMETRY_SHADER, g_source);
        fragment_shader = compile(GL_FRAGMENT_SHADER, f_source);
        prog = glCreateProgram();
        glAttachShader(prog, vertex_shader);
	glAttachShader(prog, geometry_shader);
        glAttachShader(prog, fragment_shader);
        glLinkProgram(prog);
}

Shader::~Shader()
{
	glDeleteProgram(prog);
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	if(geometry_shader != 0)
	{
		glDeleteShader(geometry_shader);
	}
}
