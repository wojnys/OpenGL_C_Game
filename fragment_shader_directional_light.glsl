#version 330 core

uniform vec3 viewPos;


in vec4 ex_worldPosition;
in vec3 ex_worldNorm;
out vec4 out_Color;

uniform vec4 LightColor;

uniform vec3 LightDirection;
uniform vec4 materialAmbient;
uniform vec4 materialDiffuse;
uniform vec4 materialSpecular;
uniform float materialShininess;


void main()
{
    
    // Ambient
    vec4 ambient = materialAmbient;
    
    // Diffuse
    vec3 norm = normalize(ex_worldNorm);
    vec3 lightDir = normalize(-LightDirection);
    float diff = max(dot(norm, lightDir), 0.0);

    vec4 diffuse = materialDiffuse * diff * LightColor;
    
    // Specular
    vec3 viewDir = normalize(viewPos - vec3(ex_worldPosition));
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), materialShininess);

    vec4 specular = materialSpecular * spec * LightColor;
    
    out_Color =(ambient + diffuse + specular) * LightColor;
    
}