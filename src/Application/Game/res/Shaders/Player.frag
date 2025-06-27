#version 330 core

out vec4 Fragcolor;

in vec2 texcoords;

uniform sampler2D tex;

void main() {
	Fragcolor = texture(tex,texcoords);
}