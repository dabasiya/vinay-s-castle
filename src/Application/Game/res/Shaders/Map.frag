#version 330 core

out vec4 Fragcolor;

uniform vec3 lightpos;

in vec3 normal;
in vec2 texcoords;
in vec3 fragpos;


uniform sampler2D tex;
uniform sampler2D normaltex;

uniform vec3 camerapos;

in mat3 TBN;



void main() {
	
	float ambient = 0.4;

	vec3 lightdir = normalize(lightpos - fragpos);
	vec3 normaldata = texture(normaltex, texcoords).rgb;
	normaldata = normaldata * 2 - 1.0;
	normaldata = TBN * normaldata;
	float diffuse = max(0.0,dot(normaldata,lightdir));

	

	vec4 color4 = texture(tex,texcoords);
	if(color4.a == 0.0)
		discard;
	vec3 color = vec3(color4.rgb) * (ambient + diffuse);
	Fragcolor = vec4(color,color4.a);
	
}