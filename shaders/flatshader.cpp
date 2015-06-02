#include <GL/glew.h>
#include "flatshader.h"

FlatShader::FlatShader() : Shader(string("sources/tex.vert"), string("sources/tex.frag"))
{
	texLocation = glGetUniformLocation(prog, "tex");
}

void FlatShader::bindAttributes()
{
}

void FlatShader::unbindAttributes()
{

}
