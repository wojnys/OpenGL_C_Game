#version 330
in vec4 ex_worldPosition;
in vec3 vertexColor;
out vec4 out_Color;

uniform vec3 lightPosition;
uniform vec4 lightColor;    
uniform vec3 viewPos;

void main(void) {
    float specularStrength = 0.5;

    // Calculate light direction
    vec3 lightDir = normalize(lightPosition - vec3(ex_worldPosition));  
    
    // Calculate view direction
    vec3 viewDir = normalize(viewPos - vec3(ex_worldPosition)); 
    
    vec3 reflectDir = reflect(-lightDir, normalize(vertexColor));
    
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    
    vec3 specular = specularStrength * spec * lightColor.rgb;
    
    // Diffuse (calc shadows)
    float dot_product = max(dot(lightDir, normalize(vertexColor)), 0.0);
    vec3 diffuse = dot_product * lightColor.rgb;
    
    // Ambient - color without the light source
    vec3 ambient = vec3(0.1, 0.1, 0.1);
    
    vec3 result = ambient + diffuse + specular;
    out_Color = vec4(result, lightColor.a);  // Use lightColor.a for alpha
}
