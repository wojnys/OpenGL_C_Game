#ifndef APPLICATION_H
#define APPLICATION_H

#include <random>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Models.h"
#include "ShaderProgram.h"
#include "AppFragmentShader.h"
#include "AppVertexShader.h"
#include <vector>
#include "Scene.h"
#include "DrawableObject.h"
#include "Controller.h"
#include "ShaderLoader.h"
#include "Light.h"
#include "SceneManager.h"
#include "SceneFactory.h"
#include "ShaderProgramFactory.h"
#include "ShaderProgramManager.h"
#include "TextureManager.h"
#include "ModelManager.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "DirectionLight.h"
#include "LightManager.h"
#include <windows.h>

class Application {
private:
    GLFWwindow* window;
    GLuint VBO, VAO;
    std::vector<ShaderProgram*> shaderProgram;
    std::vector<DrawableObject*> drawableObjects;
    ShaderProgramManager* shaderProgramManager;
    TextureManager* textureManager;
	ModelManager* modelManager;
	LightManager* lightManager;

    glm::vec3 cameraPos;
    glm::vec3  cameraFront;
    glm::vec3 cameraUp;

public:
    Application();
    ~Application();
    void initialization();
    void createShaders();
    void createTextures();
    void createModels();
    void createLights();
    void run();
    static void error_callback(int error, const char* description);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void window_focus_callback(GLFWwindow* window, int focused);
    static void window_size_callback(GLFWwindow* window, int width, int height);
    static void window_iconify_callback(GLFWwindow* window, int iconified);
    static void cursor_callback(GLFWwindow* window, double x, double y);
    static void button_callback(GLFWwindow* window, int button, int action, int mode);
    static float generateRandomFloatNumber(float bottomBoundary, float upBoundary);

    std::vector<Scene*> scenes;
    Controller* controller;
    double x, y;
    GLfloat depth;
    GLuint index;
    int newy;

    Camera* camera;
};

#endif

