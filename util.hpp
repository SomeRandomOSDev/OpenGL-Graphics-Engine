#pragma once

#include <SFML/Graphics.hpp>

namespace
{
	sf::VideoMode vm = sf::VideoMode::getDesktopMode();
	sf::Vector2i screenCenter = sf::Vector2i(vm.width / 2, vm.height / 2);

#define PI 3.14159265358979323846f
#define TAU (2 * PI)
}