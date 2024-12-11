#version 450

uniform mat4 modelMatrix;
uniform mat4 projectMatrix;
uniform mat4 viewMatrix;

layout(location = 0) in vec3 vp;  // position
layout(location = 1) in vec3 vn;  // normal
layout(location = 2) in vec2 vt;  // texture space
layout(location = 3) in vec3 ts;  // tangent space


out vec2 uv;

void main () {
	 uv = vt;
	 gl_Position = projectMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0); 
	 
}
