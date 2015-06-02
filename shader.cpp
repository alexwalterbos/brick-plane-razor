#include <GL/glew.h>
#include "shader.h"
#include <string>
#include <stdexcept>

//Source: http://stackoverflow.com/a/2796153/4258911
GLuint Shader::compile(GLuint type, string path) 
{
	ifstream source_file(path.c_str());

	if(!source_file) 
	{
		throw std::runtime_error(string("Could not load source shader ") + path);
	}

	string shader_string;
	shader_string.assign((istreambuf_iterator<char>(source_file)), istreambuf_iterator<char>());

	GLuint shader = glCreateShader(type);
	const GLchar* source = shader_string.c_str();

        glShaderSource(shader, 1, &source, NULL);
        glCompileShader(shader);

        GLint compiled;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (compiled != GL_TRUE) {
            GLint length;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
            std::string log(length, ' ');
            glGetShaderInfoLog(shader, length, &length, &log[0]);	
            throw std::runtime_error(log);
        }
        return shader;
}

Shader::Shader(string vertex_path, string fragment_path)
{
	vertex_shader = compile(GL_VERTEX_SHADER, vertex_path);
        fragment_shader = compile(GL_FRAGMENT_SHADER, fragment_path);
	geometry_shader = 0;
        prog = glCreateProgram();
        glAttachShader(prog, vertex_shader);
        glAttachShader(prog, fragment_shader);
        glLinkProgram(prog);
}

Shader::Shader(string vertex_path, string fragment_path, string geometry_path)
{
	vertex_shader = compile(GL_VERTEX_SHADER, vertex_path);
	geometry_shader = compile(GL_GEOMETRY_SHADER, geometry_path);
        fragment_shader = compile(GL_FRAGMENT_SHADER, fragment_path);
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

void Shader::useProgram()
{
	if(prog == 0) 
	{
		throw std::runtime_error("No shader program found!");
	}

	glUseProgram(prog);
}
