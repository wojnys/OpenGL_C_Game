/* #version 450
uniform mat4 modelMatrix;
uniform mat4 projectMatrix;
uniform mat4 viewMatrix;

layout(location = 0) in vec3 vp; // pozice

out vec3 fragmentLocalPosition;

void main() {
    gl_Position = projectMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0); 
   
    fragmentLocalPosition =  (projectMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0f)).xyz; 
} */


#version 450
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectMatrix;

layout(location = 0) in vec3 vp; // Vertex position in local space

out vec3 fragmentLocalPosition;

void main() {
    // Transform vertex position to clip space
    gl_Position = projectMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);

    fragmentLocalPosition = (projectMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0)).xyz;
}

