#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "AppVertexShader.h"
#include "AppFragmentShader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "Light.h"
#include "EventType.h"
#include "ShaderLoader.h"
#include "Material.h"
#include "Texture.h"

class LightDrawableObject;
class LightInterface;

class ShaderProgram : public Observer {
public:
	ShaderProgram(GLuint shaderProgramID);
	void useProgram();
	GLint setTexture(BaseTexture* texture, TextureEnums type);
	void makeTransformationForMultipleObjects(glm::mat4 transform);
	void setViewProjectionMatrices(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
	void update(EventType eventType, const void* data);
	void setLight();
	void setPointLight(std::vector<LightInterface*> lights); // PointLight
	//void setSpotLight(std::vector<LightInterface*> spotLights, Material* material); // SpotLight
	void setSpotLight(Camera* camera, Material* material); // SpotLight
	void setDirectionalLight(std::vector<LightInterface*> lights, Material* material); // DirectionalLight


private:
	GLuint shaderProgram;
	Camera* camera;

	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	glm::vec3 lightPosition;
	glm::vec4 lightColor;

	Light* light;
};

#endif  SHADERPROGRAM_H