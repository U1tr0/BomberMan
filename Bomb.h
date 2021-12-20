#pragma once
#include "Scenario.h"
#include "GameObject.h"
#include <vector>
#include "DamageReciever.h"
class Bomb : public GameObject
{
public:
	virtual void place(int x, int y);
	virtual  void start();
	int damage = 50;
	virtual  void update(float dt);
	Bomb(Scenario *scenario, DamageReciever * r);
	bool isUsed();
	virtual void explode();
	virtual void draw(sf::RenderWindow &window) override;
protected:
	RectangleShape* rect = nullptr;
	bool used = false;
	sf::Sprite *sprite;
	int x = 0;
	int y = 0;
	Scenario *scenario = nullptr;
	DamageReciever *damage_recievers;
	bool activated = false;
	float delay = 2.0f;
	float timer = 0;
	Sprite anim;
	Texture t;

	// Унаследовано через GameObject
	virtual sf::Vector2f getPivotPosition() override;
};

