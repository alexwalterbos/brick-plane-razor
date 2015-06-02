uniform sampler2D tex;

in Data {
	vec2 texCoord;
} DataIn;

void main(void) {
	gl_FragColor = texture2D(tex, texCoord);
}
