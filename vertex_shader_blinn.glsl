#version 330
uniform mat4 modelMatrix;
uniform mat4 projectMatrix;
uniform mat4 viewMatrix;
out vec3 vertexColor;
out vec4 ex_worldPosition;
out vec3 ex_worldNorm;
layout(location = 0) in vec3 vp; 
layout(location = 1) in vec3 vn;

void main() {
    vertexColor = vn; // Use vertex normal as color
    gl_Position = projectMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0); 
    ex_worldPosition = modelMatrix * vec4(vp, 1.0f); 
    ex_worldNorm = normalize(mat3(transpose(inverse(modelMatrix))) * vn);
}