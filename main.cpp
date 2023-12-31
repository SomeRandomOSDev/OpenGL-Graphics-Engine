//#include "imgui.h"
//#include "imgui-SFML.h"
#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "util.hpp"
#include "shaders.hpp"
#include "draw.hpp"
#include "Camera.hpp"
#include "meshes.hpp"
#include "Object.hpp"

int main()
{
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 0; // 2
    settings.attributeFlags = sf::ContextSettings::Attribute::Default;

    sf::RenderWindow window(vm, "OpenGL Graphics Engine", sf::Style::Fullscreen, settings);
    window.setVerticalSyncEnabled(false);
    /*window.setFramerateLimit(60);*/

    window.setActive(true);

    ////////////////////////////////////////////////////////////////////////////////////////////////

    GLuint init = glewInit();
    if (init != GLEW_OK)
    {
        window.close();
        std::cout << "Error: " << glewGetErrorString(init) << std::endl;
        while (true);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_FRAMEBUFFER_SRGB);

    glClearColor(0, 0, 0, 0);

    ////////////////////////////////////////////////////////////////////////////////////////////////

    GLuint shadersID = LoadShaders("resources/Shaders/main.vert", "resources/Shaders/main.frag");
    if (shadersID == 0)
    {
        window.close();
        while (true);
    }
    glUseProgram(shadersID);
    std::cout << "Linked !" << std::endl;

    ////////////////////////////////////////////////////////////////////////////////////////////////

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    std::vector<Object> scene;

    Object cube(Mesh("resources/Meshes/Chess/rook.obj", shadersID));
    scene.push_back(cube);

    scene.push_back(cube);

    ////////////////////////////////////////////////////////////////////////////////////////////////

    Camera viewportCamera(
    90.f, vm.width / (float)vm.height, glm::vec3(0, 0, 3), glm::vec3(0, 0, 0));

    ////////////////////////////////////////////////////////////////////////////////////////////////

    bool running = true;
    sf::Clock frameTimer, deltaClock;
    float deltaTime = 1, FPS = 0;
	unsigned int freeCamFrames = 0;

    while (running)
    {
        deltaTime = frameTimer.getElapsedTime().asSeconds();
        FPS = 1 / deltaTime;
        frameTimer.restart();

        sf::Event event;
        while (window.pollEvent(event))
        {
            //ImGui::SFML::ProcessEvent(window, event);
            if (event.type == sf::Event::Closed)
                running = false;
            else if (event.type == sf::Event::Resized)
                glViewport(0, 0, event.size.width, event.size.height);
        }

        /*ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Hello, world!");
        ImGui::Button("Look at this pretty button");
        ImGui::End();*/

        std::cout << "FPS: " << round(FPS) << "\r";

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            running = false;

        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            freeCamFrames++;
            if (freeCamFrames == 1)
                sf::Mouse::setPosition(screenCenter);
            window.setMouseCursorVisible(false);
            viewportCamera.handleFreeCam(deltaTime, 0.25f, 4);
        }
        else
        {
            freeCamFrames = 0;
            window.setMouseCursorVisible(true);
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Render(scene, viewportCamera);

        //ImGui::SFML::Render(window);

        window.display();
    }
    window.close();

    return 0;
}