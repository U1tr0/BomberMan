#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include "BoxCollider.h"
#include "Engine.h"
#include "Scenario.h"
class Enemy : public GameObject
{
public:
	virtual void draw(sf::RenderWindow &window) override;
	virtual void update(float dt) override;
	Enemy(Scenario* scene, Engine* engine);
private:
	BoxCollider *collider;
	sf::Vector2f direction;
	Engine *engine = nullptr;
	float width;
	float height;
	Scenario *scene = nullptr;
	sf::RectangleShape *rect = nullptr;

	Sprite anim;
	Texture t;
	int sprite_width = 32;
	int sprite_height = 32;

	float enemy_speed = 80.0f;
};