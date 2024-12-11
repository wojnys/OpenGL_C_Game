#include "ShaderProgram.h"
#include "GenerateRandomPosition.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "DirectionLight.h"
#include "TextureCubeMap.h"
#include <iostream>
#include <glm/gtc/random.hpp>

//Model matrix : defines position, rotation and scale of the vertices of the model in the world.
//View matrix : defines position and orientation of the "camera".
//Projection matrix : Maps what the "camera" sees to NDC, taking care of aspect ratio and perspective.

ShaderProgram::ShaderProgram(GLuint shaderProgramID) {
	this->shaderProgram = shaderProgramID;
}

void ShaderProgram::useProgram() {
	glUseProgram(this->shaderProgram);
}

void ShaderProgram::setPointLight(std::vector<LightInterface*> lights) {
	for (int i = 0; i < lights.size(); i++) {
		const PointLight* pointLight = dynamic_cast<const PointLight*>(lights[i]);

		std::string positionName = "lights[" + std::to_string(i) + "].position";
		std::string colorName = "lights[" + std::to_string(i) + "].color";

		GLint positionLoc = glGetUniformLocation(this->shaderProgram, positionName.c_str());
		GLint colorLoc = glGetUniformLocation(this->shaderProgram, colorName.c_str());

		glUniform3fv(positionLoc, 1, glm::value_ptr(pointLight->getPosition()));
		glUniform4fv(colorLoc, 1, glm::value_ptr(pointLight->getColor()));
	}
}
void ShaderProgram::setSpotLight(Camera* cameraM, Material* material) {
	glm::vec3 cameraFront = cameraM->getCameraFront();

	glm::mat4 viewMatrixInverse = glm::inverse(cameraM->getCamera()); // convert camera viewMatrix into world space
	glm::vec3 cameraPosition = glm::vec3(viewMatrixInverse[3]); // Extract the translation part

	glUniform3fv(glGetUniformLocation(shaderProgram, "LightPosition"), 1, glm::value_ptr(cameraPosition));
	glUniform3fv(glGetUniformLocation(shaderProgram, "LightDirection"), 1, glm::value_ptr(cameraFront));

	float cutoffAngle = glm::radians(7.5f); 
	glUniform1f(glGetUniformLocation(shaderProgram, "cutoff"), cos(cutoffAngle));

	glUniform4fv(glGetUniformLocation(shaderProgram, "LightColor"), 1, glm::value_ptr(glm::vec4(1.0, 1.0, 1.0, 1.0)));

	glUniform4fv(glGetUniformLocation(shaderProgram, "materialAmbient"), 1, glm::value_ptr(material->getAmbient()));

	glUniform4fv(glGetUniformLocation(shaderProgram, "materialDiffuse"), 1, glm::value_ptr(material->getDiffuse()));

	glUniform4fv(glGetUniformLocation(shaderProgram, "materialSpecular"), 1, glm::value_ptr(material->getSpecular()));

	glUniform1f(glGetUniformLocation(shaderProgram, "materialShininess"), material->getShininess());
}

void ShaderProgram::setDirectionalLight(std::vector<LightInterface*> lights, Material* material) {
	for (int i = 0; i < lights.size(); i++) {
		const DirectionLight* directionLlight = dynamic_cast<const DirectionLight*>(lights[i]);

		glUniform3fv(glGetUniformLocation(shaderProgram, "LightDirection"), 1, glm::value_ptr(directionLlight->getDirection()));

		glUniform4fv(glGetUniformLocation(shaderProgram, "LightColor"), 1, glm::value_ptr(directionLlight->getColor()));

		glUniform4fv(glGetUniformLocation(shaderProgram, "materialAmbient"), 1, glm::value_ptr(material->getAmbient()));

		glUniform4fv(glGetUniformLocation(shaderProgram, "materialDiffuse"), 1, glm::value_ptr(material->getDiffuse()));

		glUniform4fv(glGetUniformLocation(shaderProgram, "materialSpecular"), 1, glm::value_ptr(material->getSpecular()));

		glUniform1f(glGetUniformLocation(shaderProgram, "materialShininess"), material->getShininess());

		glm::mat4 viewMatrixInverse = glm::inverse(viewMatrix); // convert camera viewMatrix into world space
		glm::vec3 cameraPosition = glm::vec3(viewMatrixInverse[3]); // Extract the translation part
		GLuint viewPosLoc = glGetUniformLocation(this->shaderProgram, "viewPos");
		glUniform3fv(viewPosLoc, 1, glm::value_ptr(cameraPosition));
	}
}

void ShaderProgram::setLight() {
	glUniform1f(glGetUniformLocation(shaderProgram, "intensity"), 10.0f);
	GLuint lightPositionLoc = glGetUniformLocation(this->shaderProgram, "lightPosition");
	glUniform3fv(lightPositionLoc, 1, glm::value_ptr(lightPosition));

	GLuint lightColorLoc = glGetUniformLocation(this->shaderProgram, "lightColor");
	glUniform4fv(lightColorLoc, 1, glm::value_ptr(lightColor));

	glm::mat4 viewMatrixInverse = glm::inverse(viewMatrix); // convert camera viewMatrix into world space
	glm::vec3 cameraPosition = glm::vec3(viewMatrixInverse[3]); // Extract the translation part
	GLuint viewPosLoc = glGetUniformLocation(this->shaderProgram, "viewPos");
	glUniform3fv(viewPosLoc, 1, glm::value_ptr(cameraPosition));
}

void ShaderProgram::update(EventType eventType, const void* data) {
	//if (eventType == EventType::Light) {
	//	const Light* light = static_cast<const Light*>(data);
	//	this->lightPosition = light->getPosition();
	//	this->lightColor = light->getColor();
	//}
	if (eventType == EventType::Camera) {
		const Camera* camera = static_cast<const Camera*>(data);
		this->viewMatrix = camera->getCamera();
		this->projectionMatrix = camera->getProjection();
	}
	else if (eventType == EventType::PointLight) {
		const PointLight* pointLight = static_cast<const PointLight*>(data);
		this->lightPosition = pointLight->getPosition();
		this->lightColor = pointLight->getColor();
	}	
	//else if (eventType == EventType::SpotLight) {
	//	const SpotLight* spotLight = static_cast<const SpotLight*>(data);
	//	this->lightPosition = spotLight->getPosition();
	//	this->lightColor = spotLight->getColor();
	//}
}

void ShaderProgram::makeTransformationForMultipleObjects(glm::mat4 modelMatrix) {
	GLuint transformLoc;

	transformLoc = glGetUniformLocation(this->shaderProgram, "modelMatrix");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	this->setViewProjectionMatrices(this->viewMatrix, this->projectionMatrix);
}

void ShaderProgram::setViewProjectionMatrices(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
	GLuint viewLoc = glGetUniformLocation(this->shaderProgram, "viewMatrix");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	GLuint projectionLoc = glGetUniformLocation(this->shaderProgram, "projectMatrix");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
}


GLint ShaderProgram::setTexture(BaseTexture* texture, TextureEnums type) {
	// Dynamic cast to Texture or CubeSkyTexture

	if (type == TextureEnums::Texture) {
		Texture* textureCasted  = dynamic_cast<Texture*>(texture);

		GLint idTU = glGetUniformLocation(shaderProgram, "textureUnitID");
		glUniform1i(idTU, textureCasted->getTextureNumberUnit()); // set TU 
		return idTU;
	}
	else if (type == TextureEnums::CubeMapTexture) {
		CubeMapTexture* textureCasted = dynamic_cast<CubeMapTexture*>(texture);

		GLint idTU = glGetUniformLocation(shaderProgram, "textureUnitID");
		glUniform1i(idTU, textureCasted->getTextureNumberUnit()); // set TU 
		return idTU;
	}
}


