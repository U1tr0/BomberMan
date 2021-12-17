#pragma once
#include <SFML/Graphics.hpp>

class GameObject
{

public:
	sf::Vector2f position;
	virtual ~GameObject(){}
	virtual void draw(sf::RenderWindow &window) = 0;
	virtual void update(float dt) = 0;
};