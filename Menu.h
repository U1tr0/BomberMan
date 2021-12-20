#include <SFML/Graphics/RenderWindow.hpp>
#include "imgui.h"
#include "imgui-sfml.h"
#pragma once

class Menu {
public:
	void play();
	void exit();
	void update(sf::Time& dt);
	Menu(sf::RenderWindow& window, class Engine* engine);
private:
	sf::RenderWindow* window;
	Engine* engine;
	ImFont* font1;
};
