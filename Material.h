#pragma once
#include <glm/glm.hpp>

class Material {
public:
    // Constructor with default coefficients
    Material(glm::vec4 ambient = glm::vec4(0.1f), glm::vec4 diffuse = glm::vec4(0.8f), glm::vec4 specular = glm::vec4(0.5f), float shininess = 32.0f)
        : ra(ambient), rd(diffuse), rs(specular), shininess(shininess) {}

    // Setters
    void setAmbient(glm::vec4 ambient) { ra = ambient; }
    void setDiffuse(glm::vec4 diffuse) { rd = diffuse; }
    void setSpecular(glm::vec4 specular) { rs = specular; }
    void setShininess(float shininessValue) { shininess = shininessValue; }

    // Getters
    glm::vec4 getAmbient() const { return ra; }
    glm::vec4 getDiffuse() const { return rd; }
    glm::vec4 getSpecular() const { return rs; }
    float getShininess() const { return shininess; }

private:
    glm::vec4 ra; // Ambient coefficient
    glm::vec4 rd; // Diffuse coefficient
    glm::vec4 rs; // Specular coefficient
    float shininess; // Shininess factor for specular highlight
};

