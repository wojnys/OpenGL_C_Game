#include "Application.h"
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <SOIL.h>

#include "skycube.h"
#include "plain_texture.h"

#define GLM_ENABLE_EXPERIMENTAL

Application::Application() {
    this->cameraPos = glm::vec3(10.0f, 10.0f, 10.0f);
    this->cameraFront = glm::vec3(10.0f, 10.0f, 10.0f);
    this->cameraUp = glm::vec3(0.0f, 10.0f, 0.0f);
    this->camera = new Camera(cameraPos, cameraFront, cameraUp, -90.0f, 0.0f, 45.0f);
}
Application::~Application() {
    std::cout << "APP was destroyed";
}

void Application::error_callback(int error, const char* description) { fputs(description, stderr); }

float Application::generateRandomFloatNumber(float bottomBoundary, float upBoundary) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(bottomBoundary, upBoundary);

    return dis(gen);
}

void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void Application::window_focus_callback(GLFWwindow* window, int focused) {
    //printf("window_focus_callback \n");
}

void Application::window_iconify_callback(GLFWwindow* window, int iconified) {
    //printf("window_iconify_callback \n"); 
}

void Application::window_size_callback(GLFWwindow* window, int width, int height) {
    printf("resize %d, %d \n", width, height);
    glViewport(0, 0, width, height);
}

void Application::cursor_callback(GLFWwindow* window, double cx, double cy) {
    // Access the Application instance using the window user pointer
    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    cout << "TEST" << endl;
    if (app) {
        app->x = cx;
        app->y = cy;
        printf("cursor_callback: x = %f, y = %f\n", cx, cy);
    }
}

void Application::button_callback(GLFWwindow* window, int button, int action, int mode) {
    if (action == GLFW_PRESS) {
        // Access the Application instance using the window user pointer
        Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
        if (app) {
            int width, height;
            glfwGetFramebufferSize(window, &width, &height);
            GLbyte color[4];
            GLfloat depth = 0;
            GLuint index = 0;

            // Convert Y-coordinate to OpenGL's coordinate system
            int newy = height - app->y - 1;

            // Read pixel data at the cursor position
            glReadPixels(app->x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
            glReadPixels(app->x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
            glReadPixels(app->x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

            printf("Clicked on pixel %f, %f, color %02hhx%02hhx%02hhx%02hhx, depth % f, stencil index % u\n", app->x, app->y, color[0], color[1], color[2], color[3], depth, index);
        }
    }
}


void Application::initialization() {
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        exit(EXIT_FAILURE);
    }

    this->window = glfwCreateWindow(1000, 1000, "ZPG", NULL, NULL);

    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glEnable(GL_DEPTH_TEST); //Z-buffer
    glEnable(GL_CULL_FACE); // delete back side of the object


    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_callback);
    glfwSetMouseButtonCallback(window, button_callback);
    glfwSetWindowFocusCallback(window, window_focus_callback);
    glfwSetWindowIconifyCallback(window, window_iconify_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);

    glewExperimental = GL_TRUE;
    glewInit();

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    float ratio = width / (float)height;
    glViewport(0, 0, width, height);
}

void Application::createShaders() {
    this->shaderProgramManager = new ShaderProgramManager();
    this->shaderProgramManager->createShaderProgram("blinn", "vertex_shader_blinn.glsl", "fragment_shader_blinn.glsl"); // 0
    this->shaderProgramManager->createShaderProgram("phong", "vertex_shader_phong.glsl", "fragment_shader_phong.glsl"); // 1
    this->shaderProgramManager->createShaderProgram("lambert", "vertex_shader_lambert.glsl", "fragment_shader_lambert.glsl"); // 2
    this->shaderProgramManager->createShaderProgram("constant", "vertex_shader_constant.glsl", "fragment_shader_constant.glsl"); // 3
    this->shaderProgramManager->createShaderProgram("blinn_multiple_lights", "vertex_shader_blinn.glsl", "fragment_shader_blinn_multiple_lights.glsl"); // 4
    this->shaderProgramManager->createShaderProgram("spotlight", "vertex_shader_blinn.glsl", "fragment_shader_spotlight.glsl"); // 5
    this->shaderProgramManager->createShaderProgram("directionallight", "vertex_shader_blinn.glsl", "fragment_shader_directional_light.glsl"); // 6
    this->shaderProgramManager->createShaderProgram("textures", "vertex_texture.glsl", "fragment_texture.glsl"); // 7
    this->shaderProgramManager->createShaderProgram("skycube textures", "vertex_shader_skycube.glsl", "fragment_shader_skycube.glsl"); // 8
    this->shaderProgramManager->createShaderProgram("blender", "vertex_shader_blender_object.glsl", "fragment_shader_blender_object.glsl"); // 9
}

void Application::createTextures() {
    // textureManager
    textureManager = new TextureManager();
    const char* cubeFaces[6] = { "posx.jpg", "negx.jpg", "posy.jpg", "negy.jpg", "posz.jpg", "negz.jpg" };
    textureManager->loadCubeMap("skycube", cubeFaces);

    textureManager->loadTexture2D("grass", "grass.png");
    textureManager->loadTexture2D("wooden_fence", "wooden_fence.png");
    textureManager->loadTexture2D("house", "house.png");
    textureManager->loadTexture2D("zombie", "zombie.png");
    textureManager->loadTexture2D("tree", "tree.png");
    textureManager->loadTexture2D("grass_teren", "grass_teren.png");
}

void Application::createModels() {
	modelManager = new ModelManager();
	modelManager->loadModel("triangle", triangle, sizeof(triangle), GL_TRIANGLES, 0, sizeof(triangle) / sizeof(float), ModelEnums::Model);
	modelManager->loadModel("tree", tree, sizeof(tree), GL_TRIANGLES, 0, sizeof(tree) / sizeof(float), ModelEnums::Model);
	modelManager->loadModel("plain", plain, sizeof(plain), GL_TRIANGLES, 0, sizeof(plain) / sizeof(float), ModelEnums::Model);
	modelManager->loadModel("bushes", bushes, sizeof(bushes), GL_TRIANGLES, 0, sizeof(bushes) / sizeof(float), ModelEnums::Model);
	modelManager->loadModel("sphere", sphere, sizeof(sphere), GL_TRIANGLES, 0, sizeof(sphere) / sizeof(float), ModelEnums::Model);
	modelManager->loadModel("plain_texture", plain_texture, sizeof(plain_texture), GL_TRIANGLES, 0, sizeof(plain_texture) / sizeof(float), ModelEnums::TextureModel);
	modelManager->loadModel("skycube", skycube, sizeof(skycube), GL_TRIANGLES, 0, sizeof(skycube) / sizeof(float), ModelEnums::SkyCubeTextureModel);
	modelManager->loadModel("skycube_test", skycube, sizeof(skycube), GL_TRIANGLES, 0, sizeof(skycube) / sizeof(float), ModelEnums::Model);

    // load model for blender
    modelManager->loadBlenderModel("house_blender_model", "house.obj", ModelEnums::BlenderModel);
    modelManager->loadBlenderModel("login", "login.obj", ModelEnums::BlenderModel);
    modelManager->loadBlenderModel("zombie", "zombie.obj", ModelEnums::BlenderModel);
    modelManager->loadBlenderModel("tree_blender", "tree.obj", ModelEnums::BlenderModel);
    modelManager->loadBlenderModel("teren_blender", "teren.obj", ModelEnums::BlenderModel);

    // attach shader to camera
    camera->attach(shaderProgramManager->getShaderProgram(0));
    camera->attach(shaderProgramManager->getShaderProgram(1));
    camera->attach(shaderProgramManager->getShaderProgram(2));
    camera->attach(shaderProgramManager->getShaderProgram(3));
    camera->attach(shaderProgramManager->getShaderProgram(4));
    camera->attach(shaderProgramManager->getShaderProgram(5));
    camera->attach(shaderProgramManager->getShaderProgram(6));
    camera->attach(shaderProgramManager->getShaderProgram(7));
    camera->attach(shaderProgramManager->getShaderProgram(8));
    camera->attach(shaderProgramManager->getShaderProgram(9));
}

void Application::createLights() {
    lightManager = new LightManager();
    auto pointLight1 = new PointLight(glm::vec3(15.0f, 5.0f, 14.0f), glm::vec4(1.0f, 0.0, 0.0, 1.0f), 1.0f);
    auto pointLight3 = new PointLight(glm::vec3(25.0f, 2.0f, 4.0f), glm::vec4(1.0f, 1.0, 0.0, 1.0f), 1.0f);
    auto pointLight2 = new PointLight(glm::vec3(10.0f, 7.0f, 10.0f), glm::vec4(0.385, 0.647, 0.812, 1.0), 1.0);
    auto pointLight4 = new PointLight(glm::vec3(-6.0f, 20.0f, 10.0f), glm::vec4(0.385, 0.647, 0.812, 1.0), 1.0);


    auto directionLight = new DirectionLight(glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

    lightManager->addLight(pointLight1);
    lightManager->addLight(pointLight3);
    lightManager->addLight(pointLight2);
    lightManager->addLight(pointLight4);

    lightManager->addLight(directionLight);

    lightManager->attach(shaderProgramManager->getShaderProgram(0));
    lightManager->attach(shaderProgramManager->getShaderProgram(1));
    lightManager->attach(shaderProgramManager->getShaderProgram(2));
    lightManager->attach(shaderProgramManager->getShaderProgram(3));
    lightManager->attach(shaderProgramManager->getShaderProgram(4));
    lightManager->attach(shaderProgramManager->getShaderProgram(5));
    lightManager->attach(shaderProgramManager->getShaderProgram(6));
}

void Application::run() {
    SceneManager* sceneManager = new SceneManager();

    for (int i = 0; i < 10; i++) {
        auto scene = SceneFactory::createScene(i, window, camera, shaderProgramManager, textureManager, modelManager, lightManager);
        if (!scene) {
            break;
        }
        scene->setSceneIndex(i);
        sceneManager->addScene(scene);
    }
    int currentSceneIndex = 0;
    sceneManager->switchToScene(currentSceneIndex);

    glEnable(GL_DEPTH_TEST); //Z-buffer
    glEnable(GL_CULL_FACE);  

    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    
    // Z buffer has value 1 - when buffer is empty
    // When Z buffer has lower then 1 (so some value is in Z buffer)
    // Unproject is good for setting points where our model will be running (we wil select the position)

    int displaySkyBox = 1;

    while (!glfwWindowShouldClose(window)) {
         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		
        if (displaySkyBox == 1) {
			sceneManager->renderSkyCubeScene();
        }

        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
            std::cout << "SKYBOX CHANGED VISIBILITY";
            if (displaySkyBox == 0) {
                displaySkyBox = 1;
            }
            else {
                displaySkyBox = 0;
            }
            Sleep(300);
        }

        glClear(GL_DEPTH_BUFFER_BIT);

        sceneManager->renderCurrentScene();

        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
            if (currentSceneIndex < sceneManager->getSceneCount() - 1) {
                currentSceneIndex++;
            }
            else {
                currentSceneIndex = 0;
            }
            sceneManager->switchToScene(currentSceneIndex);
            Sleep(300);
        }

        // put the stuff we’ve been drawing onto the display
        glfwSwapBuffers(window);
        // update other events like input handling
        glfwPollEvents();
    }

    sceneManager->clear();

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}