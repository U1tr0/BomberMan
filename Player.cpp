#include "Player.h"
#include <iostream>
using namespace std;
Player::Player(Scenario *scenario): scenario(scenario) {
	bomb = new Bomb(scenario, this);
	bombs.reserve(20);
	collider = new BoxCollider(FloatRect(position.x + collider_width / 2, position.y + collider_height / 2, collider_width, collider_height));
	t.loadFromFile("player.png");
	anim.setTexture(t);
	anim.setTextureRect(IntRect(sprite_width, sprite_height, sprite_width, sprite_height));
	return_back();
}

Player::~Player() {
	delete collider;
}

void Player::moveLeft()
{
	dx -= speed;
	animRow = 3;
	anim.setTextureRect(IntRect((int)currentFrame * 32, animRow * 32, sprite_width, sprite_height));
}

void Player::moveRight()
{
	dx += speed;
	animRow = 1;
	anim.setTextureRect(IntRect((int)currentFrame * 32, animRow * 32, sprite_width, sprite_height));
}

void Player::moveUp()
{
	dy -= speed;
	animRow = 2;
	anim.setTextureRect(IntRect((int)currentFrame * 32, animRow * 32, sprite_width, sprite_height));
}

void Player::moveDown()
{
	dy += speed;
	animRow = 0;
	anim.setTextureRect(IntRect((int)currentFrame * 32, animRow * 32, sprite_width, sprite_height));
}


void Player::placeBomb()
{
	if (timer >= reload_time)
	{

		auto bomb = new Bomb(scenario, {this});
		bombs.push_back(bomb);
		bomb->place(position.x + sprite_width / 2, position.y + sprite_height / 2);
		bomb->start();
		timer = 0.0f;
	}

}

void Player::draw(sf::RenderWindow &window)
{
	for (auto e : bombs)
	{
		e->draw(window);
	}
	collider->draw(window);
	window.draw(anim);
}

void Player::update(float dt)
{
	timer += dt;
	currentFrame += 8 * dt;
	if (currentFrame > 3) { currentFrame = 0; }
	position.x += dx * dt;

	if (bombs.size())
	{
		for (auto it = bombs.begin(); it != bombs.end(); it++)
		{
			auto temp = *it;
			if (temp->isUsed())
			{
				//delete temp;
				//bombs.erase(it);
			}
			else
			{
				temp->update(dt);
			}
		}
	}

	collider->setPosition(position.x + collider_width / 2, position.y + collider_height / 2);


	for (size_t i = 0; i < scenario->getColumns(); i++)
	{
		for (size_t j = 0; j < scenario->getRows(); j++)
		{
			BoxCollider *result = scenario->getCollidersMij(i, j);
			if (result)
			{
				if (collider->intersects(*result))
				{
					position.x -= dx * dt;
					break;
				}
			}
		}
	}

	position.y += dy * dt;
	collider->setPosition(position.x + collider_width / 2, position.y + collider_height / 2);


	for (size_t i = 0; i < scenario->getColumns(); i++)
	{
		for (size_t j = 0; j < scenario->getRows(); j++)
		{
			BoxCollider *result = scenario->getCollidersMij(i, j);
			if (result)
			{
				if (collider->intersects(*result))
				{
					position.y -= dy * dt;
					break;
				}
			}
		}
	}

	anim.setPosition(position.x, position.y);

	dx = 0;
	dy = 0;

	int curr_x;
	int curr_y;
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++) {
			Scenario::BLOCK_TYPE x = scenario->getBlock(i, j);
			switch (x)
			{
			case Scenario::BLOCK_TYPE::FIRED:
				curr_x = collider->position.x / 32;
				curr_y = collider->position.y / 32;
				if (curr_x == i && curr_y == j)
					die();
				break;

			default:
				break;
			}

		}
	}
}

bool Player::check_collistion_x()
{
	int curr_x = position.x / 32;
	int curr_y = position.y / 32;

	if (scenario->getCollidersMij(curr_x - 1, curr_y)->intersects(*collider))
		return true;
	if (scenario->getCollidersMij(curr_x + 1, curr_y)->intersects(*collider))
		return true;

	return false;
}

bool Player::check_collistion_y()
{
	int curr_x = position.x / 32;
	int curr_y = position.y / 32;

	if (scenario->getCollidersMij(curr_x, curr_y)->intersects(*collider))
		return true;
	if (scenario->getCollidersMij(curr_x, curr_y)->intersects(*collider))
		return true;

	return false;
}

void Player::die()
{
	hp -= 1;
	return_back();	
}

void Player::return_back()
{
	position.x = 35;
	position.y = 35;
}

void Player::applyDamage(float x, float y, float damage)
{

}
