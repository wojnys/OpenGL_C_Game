#pragma once
#include <vector>
#include "DrawableObject.h"
#include <GLFW/glfw3.h>
#include "Controller.h"
#include "Camera.h"
#include "sphere.h"
#include "plain.h"
#include "plain_texture.h"
#include "tree.h"
#include "bushes.h"
#include "skycube.h"
#include "triangle.h"
#include "GenerateRandomPosition.h"
#include "Light.h"
#include "ShaderProgramManager.h"
#include "LightDrawableObject.h"
#include "LightManager.h"
#include "TextureManager.h"
#include "ModelManager.h"
#include "CommandsEnum.h"

class Application;

class Scene {
public:
	Scene(GLFWwindow* window, Camera* camera, ShaderProgramManager* shaderProgramManager, TextureManager* textureManager, ModelManager* modelManager, LightManager* lightManager);
	void addDrawableObject(DrawableObject* drawableObjects);
	void render();
	void clear();
	Controller* getController();
	void init();
	void setSceneIndex(int sceneIndex);


private:
	static void cursor_callback(GLFWwindow* window, double x, double y);
	static void button_callback(GLFWwindow* window, int button, int action, int mode);

	void removeDrawableObjectFromScene(Application* app);
	void addDrawableObjectToScene(Application* app, bool withBezinCurve);

	CommandEnum commandsEnum;


protected:
	std::vector<DrawableObject*> drawableObjects;
	std::vector<LightDrawableObject*> lightDrawableObjects;

	float deltaTime;
	float lastFrame;
	int frameCount = 0;
	float lastTime = 0.0f;
	GLFWwindow* window;
	Controller* controller;
	Camera* camera;
	ShaderProgramManager* shaderProgramManager;
	LightManager* lightManager;
	LightManager* spotLightManager;
	LightManager* directionLightManager;

	TextureManager* textureManager;
	ModelManager* modelManager;

	std::shared_ptr<Light> light;
	Material* material;
	int sceneIndex;
};

