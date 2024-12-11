/*
#version 450

layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 vn;
layout(location = 2) in vec2 vt;

uniform mat4 modelMatrix;

out vec2 vt_out;

void main () {
	 gl_Position = modelMatrix * vec4(vp, 1.0);
	 vt_out = vt;
}
*/



#version 450
uniform mat4 modelMatrix;
uniform mat4 projectMatrix;
uniform mat4 viewMatrix;
out vec3 vertexColor;
out vec4 ex_worldPosition;
out vec3 ex_worldNorm;
layout(location = 0) in vec3 vp; // pozice
layout(location = 1) in vec3 vn; // normala
layout(location = 2) in vec2 vt; // textura

out vec2 vt_out;

void main() {
    vertexColor = vn; // Use vertex normal as color
    gl_Position = projectMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0); 
    ex_worldPosition = modelMatrix * vec4(vp, 1.0f);  // Prevod z lokalniho souradneho systemu do globalniho
    ex_worldNorm = normalize(mat3(transpose(inverse(modelMatrix))) * vn);
    vt_out = vt;
}