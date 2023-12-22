#include <GL/glew.h>
#include <SFML/Window.hpp>
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
    settings.minorVersion = 0;

    sf::Window window(vm, "OpenGL Graphics Engine", sf::Style::Fullscreen, settings);
    window.setVerticalSyncEnabled(true);

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

    glClearColor(0, 0, 0, 0);

////////////////////////////////////////////////////////////////////////////////////////////////
    
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    Mesh cube(&cubeData[0], 12);
    Mesh triangle(&triData[0], 1);
    
////////////////////////////////////////////////////////////////////////////////////////////////

    GLuint shadersID = LoadShaders("Shaders/main.vert", "Shaders/main.frag");
    glUseProgram(shadersID);
    std::cout << "Linked !" << std::endl;
    
////////////////////////////////////////////////////////////////////////////////////////////////

    Camera viewportCamera(
    90.f, vm.width / (float)vm.height, glm::vec3(0, 0, 3), glm::vec3(0, 0, 0));

////////////////////////////////////////////////////////////////////////////////////////////////

    bool running = true;
    sf::Clock frameTimer;
    while (running)
    {
        float deltaTime = frameTimer.getElapsedTime().asSeconds();
        frameTimer.restart();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                running = false;
            else if (event.type == sf::Event::Resized)
                glViewport(0, 0, event.size.width, event.size.height);
        }

        std::cout << deltaTime << std::endl;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			running = false;

        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            window.setMouseCursorVisible(false);
            viewportCamera.handleFreeCam(deltaTime, 0.5f, 5);
        }
        else
            window.setMouseCursorVisible(true);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        DrawMesh(shadersID, cube, viewportCamera);
        DrawMesh(shadersID, triangle, viewportCamera);

        window.display();
    }
    window.close();

    return 0;
}