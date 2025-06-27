#version 330 core

layout (location = 0) in vec3 apos;
layout (location = 2) in vec2 atexcoords;

out vec2 texcoords;

uniform mat4 position;
uniform mat4 rotation;

uniform mat4 extrarotation;

uniform mat4 cameramat;

void main() {
	gl_Position = cameramat * position * extrarotation * rotation * vec4(apos,1.0f);
	texcoords = atexcoords;
}