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
	//collider->draw(window);
	window.draw(anim);
	hb.draw(window);
}

void Player::update(float dt)
{
	timer += dt;
	currentFrame += 8 * dt;
	if (currentFrame > 3) { currentFrame = 0; }
	position.x += dx * dt;

	if (bombs.size())
	{
		auto it = bombs.begin();
		auto temp = *it;
		if (temp->isUsed()) {
			delete temp;
			bombs.erase(it);
		}
	}

	for (auto it = bombs.begin(); it != bombs.end(); it++)
	{
		auto temp = *it;
		temp->update(dt);
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

	collider->setPosition(position.x + collider_width / 2, position.y + collider_height / 2);
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
				curr_x = collider->getPivotPosition().x / scenario->getCellWidth();
				curr_y = collider->getPivotPosition().y / scenario->getCellWidth();
				if (curr_x == i && curr_y == j)
					die();
				break;

			default:
				break;
			}

		}
	}
	if (killsCounter >= 5) {
		killsCounter = 0;
		scenario->generateMatrix();
		return_back();
	}

	hb.update(dt);
}

bool Player::check_collistion_x()
{
	int curr_x = collider->getPivotPosition().x / scenario->getCellWidth();
	int curr_y = collider->getPivotPosition().y / scenario->getCellWidth();
	auto leftCell = scenario->getCollidersMij(curr_x - 1, curr_y);
	auto rightCell = scenario->getCollidersMij(curr_x + 1, curr_y);
	if (leftCell) {
		if (leftCell->intersects(*collider)) {
			return true;
		}
	}
	if (rightCell) {
		if (rightCell->intersects(*collider)) {
			return true;
		}
	}
	
	return false;
}

bool Player::check_collistion_y()
{
	int curr_x = collider->getPivotPosition().x / scenario->getCellWidth();
	int curr_y = collider->getPivotPosition().y / scenario->getCellWidth();
	auto topCell = scenario->getCollidersMij(curr_x, curr_y - 1);
	auto bottomCell = scenario->getCollidersMij(curr_x, curr_y + 1);
	if (topCell) {
		if (topCell->intersects(*collider)) {
			return true;
		}
	}
	if (bottomCell) {
		if (bottomCell->intersects(*collider)) {
			return true;
		}
	}

	return false;
}

void Player::die()
{
	hb.decreaseHP();
	return_back();
	if (hb.getCurHP() == 0) {
		scenario->generateMatrix();
		hb.resetHP();
	}
}

void Player::return_back()
{
	position = scenario->getOriginPosition();
	scenario->fireOff();
}

void Player::applyDamage(float x, float y, float damage)
{

}

sf::Vector2f Player::getPivotPosition()
{
	return collider->getPivotPosition();
}
