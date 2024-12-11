#version 330 core

uniform vec3 viewPos;

in vec4 ex_worldPosition;
in vec3 ex_worldNorm;
out vec4 out_Color;

uniform vec4 LightColor;
uniform vec3 LightPosition;
uniform vec3 LightDirection;

uniform vec4 materialAmbient;
uniform vec4 materialDiffuse;
uniform vec4 materialSpecular;
uniform float materialShininess;

uniform float cutoff; 

void main() {
    vec3 lightPosition = LightPosition;
    vec3 lightVector = normalize(lightPosition - vec3(ex_worldPosition));
    float diff = max(dot(normalize(lightVector), normalize(ex_worldNorm)), 0.0);
    
    vec4 ambient = materialAmbient;
    vec4 diffuse;

    // Spotlight cutoff
    float spot = dot(normalize(LightDirection), -lightVector);
    if (spot < cutoff) {
        diff = 0;   
    } else {
        
        // diffuse
        diffuse = diff * materialDiffuse * LightColor;   

        // Homogenni slozka - 1.0 pro 3D prostor
        float distance = length(vec4(lightPosition, 1.0f) - ex_worldPosition);
        float constant = 1.0f;   // Keep at 1.0 for consistent base intensity.
        float linear = 0.005f;    
        float quadratic = 0.0001f; 
  
        float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));

        diffuse *= attenuation;
        ambient *= attenuation;
    }

    // Map spot intensity for smooth edge falloff
    spot = clamp((spot - cutoff) / (1.0 - cutoff), 0.0, 1.0);

    float backgroundOpacity = 0.19;
    out_Color = (backgroundOpacity + (diffuse + ambient) * spot) * LightColor;
}
