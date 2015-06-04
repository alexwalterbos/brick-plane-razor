#version 120

in vec3 position;
in vec2 texCoord;

uniform mat4 modelview;
uniform mat4 projection;

out Data {
	vec2 texCoord;
} DataOut;

int main() {
	DataOut.texCoord = texCoord;
	gl_position = projection * modelview * vec4(position, 1);
}
