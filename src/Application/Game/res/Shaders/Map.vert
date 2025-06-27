#version 330 core

layout (location = 0) in vec3 apos;
layout (location = 1) in vec3 anormal;
layout (location = 2) in vec2 atexcoords;
layout (location = 3) in vec3 atangent;
layout (location = 4) in vec3 abitangent;

out vec2 texcoords;

out vec3 fragpos;

out vec3 normal;

uniform mat4 cameramat;

out mat3 TBN;


void main() {
	gl_Position = cameramat * vec4(apos,1.0f);
	fragpos = apos;
	texcoords = atexcoords;
	normal = normalize(anormal);
	vec3 T = normalize(atangent);
	vec3 B = normalize(abitangent);
	vec3 N = normal;
	TBN = mat3(T, B, N);
}