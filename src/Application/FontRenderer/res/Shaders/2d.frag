#version 330 core

in vec2 texcoords;

uniform sampler2D tex;

out vec4 Fragcolor;

void main() {
	Fragcolor = texture(tex,texcoords);
}