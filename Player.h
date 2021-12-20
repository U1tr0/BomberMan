#pragma once
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include "Scenario.h"
#include <math.h>
#include "Bomb.h"
#include "BoxCollider.h"
#include <vector>
#include "GameObject.h"
#include "DamageReciever.h"
#include <queue>
#include "HealthBar.h"
enum class Directions{up, down, right, left, non};
using namespace sf;
class Player : public GameObject, public DamageReciever
{
public:
	Player(class Scenario* scenario);
	~Player();


	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	BoxCollider* collider;
	Bomb *bomb = nullptr;
	void placeBomb();
	std::vector<Bomb *> bombs;
	void die();
	int killsCounter = 0;
	virtual void draw(sf::RenderWindow &window) override;
	virtual void update(float dt) override;

private:
	HealthBar hb;
	int animRow = 1;
	bool check_collistion_x();
	bool check_collistion_y();
	void return_back();
	float reload_time = 1.0f;
	float timer = reload_time+ 1.0f;
	float dx;
	float dy;
	int sprite_width = 32;
	int sprite_height = 32;
	int collider_width = 16;
	int collider_height = 16;
	float currentFrame = 0;
	Directions direction;
	Directions last;
	Sprite anim;
	Texture t;
	Scenario *scenario;
	float speed =150.0f;
	virtual void applyDamage(float x, float y, float damage) override;
	// Унаследовано через GameObject
	virtual sf::Vector2f getPivotPosition() override;
};