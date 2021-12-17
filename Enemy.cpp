#include "Enemy.h"
#include "Engine.h"
using namespace sf;
void Enemy::draw(sf::RenderWindow &window)
{
	//rect->setPosition(position );
	//window.draw(*rect);
	sf::RectangleShape shape = sf::RectangleShape(sf::Vector2f(30, 30));

	shape.setPosition(position.x, position.y);
	shape.setFillColor(sf::Color::Red);
	window.draw(shape);


	anim.setPosition(position );
	//window.draw(anim);
	collider->draw(window);
}

void Enemy::update(float dt)
{
	direction = direction;

	
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
						break;
					case 1:
						direction.x = -1;
						direction.y = 0;
						break;
					case 2:
						direction.x = 0;
						direction.y = 1;
						break;
					case 3:
						direction.x = 0;
						direction.y = -1;
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
						break;
					case 1:
						direction.x = -1;
						direction.y = 0;
						break;
					case 2:
						direction.x = 0;
						direction.y = 1;
						break;
					case 3:
						direction.x = 0;
						direction.y = -1;
						break;
					}
					break;
				}
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
					delete this;
					return;
				}
				break;

			default:
				break;
			}

		}
	}
}

Enemy::Enemy(Scenario* scene, Engine* engine) : scene(scene), engine(engine)
{
	collider = new BoxCollider(sf::FloatRect(0, 0, 24.0f, 24.0f));
	auto dir = rand() % 4;
	t.loadFromFile("enemies.png");
	anim.setTexture(t);
	anim.setTextureRect(IntRect(0, 0, 32, 32));

	switch (dir)
	{
	case 0:
		direction.x = 1;
		break;
	case 1:
		direction.x = -1;
		break;
	case 2:
		direction.y = 1;
		break;
	case 3:
		direction.y = -1;
		break;
	}
}
