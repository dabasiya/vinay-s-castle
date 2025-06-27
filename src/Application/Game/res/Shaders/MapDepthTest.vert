#version 330 core

layout (location = 0) in vec3 apos;

uniform mat4 cameramat;

out vec2 texcoords;

void main() {
	gl_Position = cameramat * vec4(apos, 1.0f);
}