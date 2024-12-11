// blinn
#version 330
in vec4 ex_worldPosition;
in vec3 vertexColor;
out vec4 out_Color;
in vec3 ex_worldNorm;

uniform vec3 lightPosition;
uniform vec4 lightColor;
uniform vec3 viewPos;

void main(void) {
    float specularStrength = 0.5;

    // Calculate light direction
    vec3 lightDir = normalize(lightPosition - vec3(ex_worldPosition));

    vec3 viewDir = normalize(viewPos - vec3(ex_worldPosition));

    vec3 halfwayDir = normalize(lightDir + viewDir);

    float spec = pow(max(dot(normalize(ex_worldNorm), halfwayDir), 0.0), 32.0); 

    vec3 specular = specularStrength * spec * lightColor.rgb;

    float dot_product = max(dot(lightDir, normalize(ex_worldNorm)), 0.0); // uses normal

    vec3 diffuse = dot_product * lightColor.rgb;

    vec3 ambient = vec3(0.1, 0.1, 0.1);

    vec3 result = ambient + diffuse + specular;

    out_Color = vec4(result, lightColor.a);
} 