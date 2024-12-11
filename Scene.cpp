#include "Scene.h"
#include "SpotLight.h"
#include "PointLight.h"
#include "DirectionLight.h"
#include "Material.h"
#include "ModelEnums.h"
#include "Application.h"
#include "BezierData.h"

Scene::Scene(GLFWwindow* window, Camera* camera, ShaderProgramManager* shaderProgramManager,TextureManager* textureManager, ModelManager* modelManager, LightManager* lightManager) {
    this->window = window;
    this->deltaTime = 0.0f;
    this->lastFrame = 0.0f;
    this->camera = camera;
    this->shaderProgramManager = shaderProgramManager;
	this->textureManager = textureManager;
	this->modelManager = modelManager;
    this->frameCount = 0;
	this->commandsEnum = CommandEnum::NONE;
    this->lightManager = lightManager;

    material = new Material(glm::vec4(0.247f, 0.199f, 0.074f, 1), // Ambient
        glm::vec4(0.751f, 0.606f, 0.226f, 1), // Diffuse
        glm::vec4(0.628f, 0.555f, 0.366f, 1), // Specular
        51.2f); ;

    this->controller = new Controller(window, camera, lightManager);

    this->init();
}

void Scene::init() {
    // Set the user pointer to the controller of the first scene
    glfwSetWindowUserPointer(window, this->getController());

    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
        Controller* controller = static_cast<Controller*>(glfwGetWindowUserPointer(window));
        if (controller) {
            controller->mouseCallback(window, xpos, ypos);
        }
     });
    // enabled cursor
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Scene::addDrawableObject(DrawableObject* drawableObject) {
    this->drawableObjects.push_back(drawableObject);
}

Controller* Scene::getController() {
    return this->controller;
}

void Scene::cursor_callback(GLFWwindow* window, double cx, double cy) {
    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (app) {
        app->x = cx;
        app->y = cy;
    }
}

glm::ivec2 getResolution(GLFWwindow* window) {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);  // Get the framebuffer size
    return glm::ivec2(width, height); 
}

void Scene::button_callback(GLFWwindow* window, int button, int action, int mode) {
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

            app->depth = depth;
            app->index = index;
            app->newy = newy;

            printf("Clicked on pixel %f, %f, color %02hhx%02hhx%02hhx%02hhx, depth % f, stencil index % u\n", app->x, app->y, color[0], color[1], color[2], color[3], depth, index);

        }
    }
}

void Scene::render() {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    frameCount++;

    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (app->index > 0) {
        if (commandsEnum == CommandEnum::REMOVE) {
            this->removeDrawableObjectFromScene(app);
        } if (commandsEnum == CommandEnum::INSERT) {
            this->addDrawableObjectToScene(app, false);
        } if (commandsEnum == CommandEnum::BEZIN) {
            this->addDrawableObjectToScene(app, true);
        }
    }

    if (currentFrame - lastTime >= 1.0f) {
        float fps = frameCount / (currentFrame - lastTime);
        std::cout << "FPS: " << fps << std::endl;
        frameCount = 0;
        lastTime = currentFrame;
    }

    // R - remove objects
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        glfwSetCursorPosCallback(window, cursor_callback);
        glfwSetMouseButtonCallback(window, button_callback);
		commandsEnum = CommandEnum::REMOVE;
    }

    // I - insert objects
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        glfwSetCursorPosCallback(window, cursor_callback);
        glfwSetMouseButtonCallback(window, button_callback);
        commandsEnum = CommandEnum::INSERT;
    }

    // B - add zombie bezin curves
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        glfwSetCursorPosCallback(window, cursor_callback);
        glfwSetMouseButtonCallback(window, button_callback);
        commandsEnum = CommandEnum::BEZIN;
    }

    // I need to again turn on mouse cursor for viewing in the scene
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        this->init();
        commandsEnum = CommandEnum::NONE;
    }

    this->controller->processInput(deltaTime);

    glDisable(GL_CULL_FACE);
    if (drawableObjects[0]->getNameOfObject() == "skycubeBackground") {
        drawableObjects[0]->clearAllTransformations();

        glm::mat4 viewMatrixInverse = glm::inverse(camera->getCamera());
        glm::vec3 cameraPosition = glm::vec3(viewMatrixInverse[3]);
        cout << "Camera position: " << cameraPosition.x << " " << cameraPosition.y << " " << cameraPosition.z << endl;
        drawableObjects[0]->addTransformation(std::make_shared<Translate>(cameraPosition.x, cameraPosition.y, cameraPosition.z));
    }

    int objectID = 1;
    for (auto& drawable : this->drawableObjects) {
        drawable->setObjectID(objectID); // Set objectID for stencil  
        objectID++;
        drawable->draw();

        // Not solution - I did not have time to update it
        if(sceneIndex == 1) shaderProgramManager->getShaderProgram(6)->setDirectionalLight(lightManager->getLights(EventType::DirectionLight), material);
        if(sceneIndex == 3)  shaderProgramManager->getShaderProgram(5)->setSpotLight(camera, material);
        if (sceneIndex == 4)  shaderProgramManager->getShaderProgram(4)->setPointLight(lightManager->getLights(EventType::PointLight));
        if(sceneIndex == 2 || sceneIndex == 5)   shaderProgramManager->getShaderProgram(0)->setLight();
        if (sceneIndex == 6) {
            shaderProgramManager->getShaderProgram(0)->setLight();
            shaderProgramManager->getShaderProgram(1)->setLight();
            shaderProgramManager->getShaderProgram(2)->setLight();
        }

    }
    glEnable(GL_CULL_FACE);
}

void Scene::removeDrawableObjectFromScene(Application* app) {
    auto it = std::find_if(drawableObjects.begin(), drawableObjects.end(), [&](const auto& obj) {
        return obj->getObjectID() == app->index;
     });

    // app->index != 1 means that skybox cannot be removed
    if (it != drawableObjects.end() && app->index != 1) {
        printf("Object was deleted stencil index % u\n", app->index);
        drawableObjects.erase(it);
        app->index = 0;
    }
}

void Scene::addDrawableObjectToScene(Application* app, bool withBezinCurve) {
    glm::vec3 screenX = glm::vec3(app->x, app->newy, app->depth);
    glm::ivec2 resolution = getResolution(window);
	cout << "resolution R: " << resolution.x << " " << resolution.y << endl;
    glm::vec4 viewPort = glm::vec4(0, 0, resolution.x, resolution.y);
    glm::mat4 view = camera->getCamera();
    glm::mat4 projection = camera->getProjection();
    glm::vec3 pos = glm::unProject(screenX, view, projection, viewPort);

    printf("unProject [%f,%f,%f]\n", pos.x, pos.y, pos.z);

    if (withBezinCurve == true) {
		DrawableObject* zombie = new DrawableObject(modelManager->getModelPair("zombie"), shaderProgramManager->getShaderProgram(9), textureManager->getTexture("zombie"));
        
		glm::vec3 offestPosition = glm::vec3(pos.x, pos.y, pos.z);
		zombie->addTransformation(std::make_shared<BezinCurve>(A, B, 0.5, 0.1, offestPosition));
        zombie->addTransformation(std::make_shared<Scale>(3.0f, 3.0f, 3.0f));
		drawableObjects.push_back(zombie);

		app->index = 0;
    }
    else {
        DrawableObject* tree = new DrawableObject(modelManager->getModelPair("tree_blender"), shaderProgramManager->getShaderProgram(7), textureManager->getTexture("tree"));
        tree->addTransformation(std::make_shared<Translate>(pos.x, pos.y, pos.z));
        tree->addTransformation(std::make_shared<Scale>(0.3, 0.3, 0.3));
        drawableObjects.push_back(tree);

        app->index = 0;
    }
}

void Scene::setSceneIndex(int sceneIndex) {
	this->sceneIndex = sceneIndex;
}

void Scene::clear() {
    for (auto& drawable : drawableObjects) {
        delete drawable;
    }
    drawableObjects.clear();

    delete controller;
    controller = nullptr;
}

