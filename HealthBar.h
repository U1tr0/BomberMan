#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
class HealthBar: public GameObject
{
public:
	HealthBar();
	void decreaseHP();
	virtual void draw(sf::RenderWindow& window) override;
	virtual void update(float dt) override;
	int getCurHP();
	void resetHP();
	
private:
	int hp = 3;
	sf::Sprite anim;
	sf::Texture t;

	// Унаследовано через GameObject

	virtual sf::Vector2f getPivotPosition() override;
};

