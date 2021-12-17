#pragma once
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <math.h>
#include "GameObject.h"




class BoxCollider : public GameObject
{
private:
	sf::FloatRect rect;

public:
	BoxCollider(sf::FloatRect rect):rect(rect)
	{
	}
	inline bool intersects(const BoxCollider &other)
	{
		return rect.intersects(other.rect);
	}

	inline float getHeight()
	{
		return rect.height;
	}
	inline float getWidth()
	{
		return rect.width;
	}
	inline void setPosition(float x, float y)
	{
		position.x = x;
		position.y = y;
			


		rect.left = x;
		rect.top = y;
	}
	inline virtual  void update(float dt)
	{
	}

	inline virtual void draw(sf::RenderWindow &window)
	{
		sf::RectangleShape shape = sf::RectangleShape(sf::Vector2f(rect.width, rect.height));

		shape.setPosition(rect.left, rect.top);
		shape.setFillColor(sf::Color::Green);
		window.draw(shape);
	}
};