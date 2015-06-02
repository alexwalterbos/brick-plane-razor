#include "shader.h"
#include <GLFW/glfw3.h>

class FlatShader : public Shader {
	public:
		FlatShader();
		void setTexture(GLuint tex);
		virtual void bindAttributes();
		virtual void unbindAttributes();
	private:
		GLuint tex, texLocation;

};
