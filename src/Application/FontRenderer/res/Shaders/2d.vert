#version 330 core

layout (location = 0) in vec3 apos;
layout (location = 1) in vec2 atexcoords;

uniform mat4 model;
uniform mat4 projection;

out vec2 texcoords;

void main() {
	gl_Position = projection * model * vec4(apos,1.0f);
	texcoords = atexcoords;
}