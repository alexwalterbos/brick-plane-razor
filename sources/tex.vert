#version 120

layout(location=0) in vec3 position;
layout(location=1) in vec2 texCoord;

out Data {
	vec2 texCoord;
} DataOut;

int main() {
	DataOut.texCoord = texCoord;
	gl_position = ftransform();	
}
