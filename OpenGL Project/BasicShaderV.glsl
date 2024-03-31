#version 330 core
layout(location = 0) in vec3 vPos;
layout(location = 1) in vec2 vUV;
layout(location = 2) in vec3 vNormal;

out vec3 fPos;
out vec2 fUV;
out vec3 fNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(vPos, 1.0f);
	
	fPos = vec3(model * vec4(vPos, 1.0f));
	fUV = vUV;
	fNormal = vNormal;
}