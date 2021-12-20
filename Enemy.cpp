#include "Enemy.h"
#include "Engine.h"
using namespace sf;
void Enemy::draw(sf::RenderWindow &window)
{
	//rect->setPosition(position );
	//window.draw(*rect);
	sf::RectangleShape shape = sf::RectangleShape(sf::Vector2f(30, 30));

	//shape.setPosition(position.x, position.y);
	//shape.setFillColor(sf::Color::Red);
	//window.draw(shape);


	anim.setTextureRect(IntRect(1 + 16 * animRow + 16 * (int)currentFrame, 0, 16, 16));
	anim.setScale(2, 2);
	window.draw(anim);
	//collider->draw(window);
}

void Enemy::update(float dt)
{
	currentFrame += 8 * dt;
	if (currentFrame > animFrames) { currentFrame = 0; }
	position.x += direction.x *dt* enemy_speed;
	collider->setPosition(position.x + 3, position.y + 3);
	
	
	for (size_t i = 0; i < scene->getColumns(); i++)
	{
		for (size_t j = 0; j < scene->getRows(); j++)
		{
			BoxCollider *result = scene->getCollidersMij(i, j);
			if (result)
			{
				if (collider->intersects(*result))
				{
					position.x -= direction.x * dt * enemy_speed;
					auto dir = rand() % 4;
					switch (dir)
					{
					case 0:
						direction.x = 1;
						direction.y = 0;
						animFrames = 4;
						animRow = 4;
						break;
					case 1:
						direction.x = -1;
						direction.y = 0;
						animFrames = 4;
						animRow = 10;
						break;
					case 2:
						direction.x = 0;
						direction.y = 1;
						animFrames = 2;
						animRow = 1;
						break;
					case 3:
						direction.x = 0;
						direction.y = -1;
						animFrames = 2;
						animRow = 8;
						break;
					}

					break;
				}
			}
		}
	}
	
	position.y += direction.y * dt * enemy_speed;
	collider->setPosition(position.x + 3, position.y + 3);
	
	for (size_t i = 0; i < scene->getColumns(); i++)
	{
		for (size_t j = 0; j < scene->getRows(); j++)
		{
			BoxCollider *result = scene->getCollidersMij(i, j);
			if (result)
			{
				if (collider->intersects(*result))
				{
					position.y -= direction.y * dt * enemy_speed;
					auto dir = rand() % 4;
					switch (dir)
					{
					case 0:
						direction.x = 1;
						direction.y = 0;
						animFrames = 4;
						animRow = 4;
						break;
					case 1:
						direction.x = -1;
						direction.y = 0;
						animFrames = 4;
						animRow = 10;
						break;
					case 2:
						direction.x = 0;
						direction.y = 1;
						animFrames = 2;
						animRow = 1;
						break;
					case 3:
						direction.x = 0;
						direction.y = -1;
						animFrames = 2;
						animRow = 8;
						break;
					}
					break;
				}
			}
		}
	}

	for (int i = 0; i < enemies->size(); i++) {
		Enemy* temp = (*enemies)[i];
		if (temp != this) {
			if (collider->intersects(*temp->collider)) {
				direction = -direction;
				
			}
		}
	}


	int curr_x;
	int curr_y;
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++) {
			Scenario::BLOCK_TYPE x = scene->getBlock(i, j);
			switch (x)
			{
			case Scenario::BLOCK_TYPE::FIRED:
				curr_x = collider->position.x / 32;
				curr_y = collider->position.y / 32;
				if (curr_x == i && curr_y == j)
				{
					engine->remove(this);
					for (auto it = enemies->begin(); it != enemies->end(); it++) {
						if (*it == this) {
							enemies->erase(it);
							break;
						}
					}
					player->killsCounter++;
					delete this;
					return;
				}
				break;

			default:
				break;
			}

		}
	}

	if (collider->intersects(*player->collider)) {
		player->die();
	}
	anim.setPosition(position);
}

Enemy::Enemy(Scenario* scene, Engine* engine, Player* player, std::vector<Enemy*> &enemies) : scene(scene), engine(engine), player(player), enemies(&enemies)
{
	collider = new BoxCollider(sf::FloatRect(0, 0, 24.0f, 24.0f));
	auto dir = rand() % 4;
	t.loadFromFile("enemy.png");
	anim.setTexture(t);
	anim.setTextureRect(IntRect(1, 0, 16, 16));
	anim.setScale(2, 2);

	switch (dir)
	{
	case 0:
		direction.x = 1;
		animFrames = 4;
		animRow = 4;
		break;
	case 1:
		direction.x = -1;
		animFrames = 4;
		animRow = 4;
		break;
	case 2:
		direction.y = 1;
		animFrames = 2;
		animRow = 1;
		break;
	case 3:
		direction.y = -1;
		animFrames = 2;
		animRow = 8;
		break;
	}
}

sf::Vector2f Enemy::getPivotPosition()
{
	return collider->getPivotPosition();
}
