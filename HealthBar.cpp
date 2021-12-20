#include "HealthBar.h"

HealthBar::HealthBar()
{
	t.loadFromFile("bmpMejoras.png");
	anim.setTexture(t);
	anim.setTextureRect(sf::IntRect(0, 64, 16, 16));
	anim.setScale(2, 2);
}

void HealthBar::decreaseHP()
{
	hp--;
}

void HealthBar::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < hp; i++) {
		anim.setPosition(605 - 40 * (i + 1), 0);
		window.draw(anim);
	}
}

void HealthBar::update(float dt)
{
}

int HealthBar::getCurHP()
{
	return hp;
}

void HealthBar::resetHP()
{
	hp = 3;
}

sf::Vector2f HealthBar::getPivotPosition()
{
	return sf::Vector2f();
}
