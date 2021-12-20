#include "Bomb.h"
#include <iostream>
using namespace std;
void Bomb::place(int x, int y)
{
	this->x = x;
	this->y = y;
	rect->setPosition(this->x, this->y);
	rect->setSize(Vector2f(16, 16));
}


void Bomb::start()
{
	activated = true;
}

void Bomb::update(float delta_time)
{
	if (activated)
	{
		timer += delta_time;
		if (timer >= delay)
		{
			explode();
		}
	}
}
Bomb::Bomb(Scenario *scenario, DamageReciever * r): scenario(scenario)
{
	damage_recievers = r;
	t.loadFromFile("bomb.png");
	anim.setTexture(t);
	anim.setTextureRect(IntRect(0, 0, 32, 32));
	rect = new RectangleShape();
	rect->setFillColor(Color::Red);

}

bool Bomb::isUsed()
{
	return used;
}

void Bomb::explode()
{
	used = true;
	int w = scenario->getCellWidth();


	scenario->fireCell(x, y);
	scenario->fireCell(x + w, y);
	scenario->fireCell(x - w, y);
	scenario->fireCell(x, y - w);
	scenario->fireCell(x, y + w);

	damage_recievers->applyDamage(x, y, damage);
	damage_recievers->applyDamage(x + w, y, damage);
	damage_recievers->applyDamage(x - w, y, damage);
	damage_recievers->applyDamage(x, y - w, damage);
	damage_recievers->applyDamage(x, y + w, damage);


	timer = 0;
	activated = false;
}

void Bomb::draw(sf::RenderWindow &window)
{
	if (activated)
	{


		//rect->setSize(Vector2f(16, 16));
		//rect->setPosition(this->x - 8, this->y - 8);
		anim.setScale(0.5,0.5);
		anim.setPosition(this->x - 8, this->y - 8);
		window.draw(anim);
		//window.draw(*rect);
	}
}

sf::Vector2f Bomb::getPivotPosition()
{
	sf::Vector2f temp = rect->getSize();
	return position + sf::Vector2f(temp.x / 2, temp.y / 2);
}
