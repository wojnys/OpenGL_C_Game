#version 330 core

in vec4 ex_worldPosition;
in vec3 ex_worldNormal;
in vec3 vertexColor;
out vec4 out_Color;

uniform vec3 lightPosition;  
uniform vec4 lightColor;   

void main(void) {
    // Calculate light vector and apply lighting logic
    vec3 lightVector = normalize(lightPosition - vec3(ex_worldPosition));
    float dot_product = max(dot(lightVector, normalize(vertexColor)), 0.0);

    vec4 diffuse = dot_product * lightColor;
    
    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
    out_Color = ambient + diffuse;
}