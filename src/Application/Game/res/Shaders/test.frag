#version 330 core

in vec2 texcoords;

uniform sampler2D tex;

out vec4 Fragcolor;

void main() {
	//float depthValue = texture(tex, texcoords).r;
	//Fragcolor = vec4(vec3(depthValue), 1.0);
	float value = texture(tex, texcoords).r;
	Fragcolor = vec4(vec3(value),1.0f);
}