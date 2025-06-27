#version 330 core

in vec2 texcoords;

uniform sampler2D tex;

uniform float opacity;

out vec4 Fragcolor;

void main() {
	Fragcolor = opacity * texture(tex,texcoords);
}