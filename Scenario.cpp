#include "Scenario.h"
#include "Spawner.h"
Scenario::Scenario() {
	for (int i = 0; i < columns; i++)
		for (int j = 0; j < rows; j++)
			colliders[i][j] = nullptr;
}

Scenario::~Scenario() {

}

void Scenario::generateMatrix() {
	srand(time(NULL));
	
	for (int i = 0; i < columns; i++)
		for (int j = 0; j < rows; j++)
			if (colliders[i][j] != nullptr) {
				delete colliders[i][j];
				colliders[i][j] = nullptr;
			}

	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++) {
			if (i == 0 || j == 0 || i == rows - 1 || j == columns - 1) {
				map[i][j] = BLOCK_TYPE::UNBREAKABLE;
				colliders[i][j] = new BoxCollider(FloatRect(i * cell_width, j * cell_width, cell_width, cell_width));
				continue;
			}

			if (i % 2 == 0 && j % 2 == 0) {
				map[i][j] = BLOCK_TYPE::UNBREAKABLE;
				colliders[i][j] = new BoxCollider(FloatRect(i * cell_width, j * cell_width, cell_width, cell_width));
				continue;
			}
			if ((i == 1 && (j == 1 || j == 2)) || (j == 1 && i == 2)) {
				map[i][j] = BLOCK_TYPE::GROUND;
				continue;
			}

			if (rand() % 2 == 0)
			{
				map[i][j] = BLOCK_TYPE::GROUND;
			}
			else
			{
				map[i][j] = BLOCK_TYPE::BREAKABLE;
				colliders[i][j] = new BoxCollider(FloatRect(i * cell_width, j * cell_width, cell_width, cell_width));
			}
		}
	}

	spawn->spawn();
}

Scenario::BLOCK_TYPE Scenario::getBlock(int i, int j) const
{
	return map[i][j];
}

void Scenario::fireCell(int position_x, int position_y)
{
	auto current_type = map[position_x / cell_width][position_y / cell_width];
	if (current_type == Scenario::BLOCK_TYPE::BREAKABLE || current_type == Scenario::BLOCK_TYPE::GROUND)
	{
		delete colliders[position_x / cell_width][position_y / cell_width];
		colliders[position_x / cell_width][position_y / cell_width] = nullptr;
		if (current_type == Scenario::BLOCK_TYPE::BREAKABLE) {
			map[position_x / cell_width][position_y / cell_width] = BLOCK_TYPE::GROUND;
		}
		else {
			map[position_x / cell_width][position_y / cell_width] = BLOCK_TYPE::FIRED;
		}
		timer = 0.0f;
	}
}

BoxCollider *Scenario::getCollidersMij(int i, int j) const
{
	return colliders[i][j];
}

void Scenario::draw(sf::RenderWindow &window) {
	RectangleShape rectangle;
	rectangle.setSize(Vector2f(cell_width, cell_width));
	Texture t1;
	t1.loadFromFile("tileset.png");
	Sprite anim1;
	anim1.setTexture(t1);
	Texture t2;
	Sprite anim2;
	t2.loadFromFile("fire.png");
	anim2.setTexture(t2);
	anim2.setTextureRect(IntRect(32, 32, 16, 16));
	anim2.setScale(2, 2);
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++) {
			BLOCK_TYPE x = map[i][j];
			switch (x)
			{

			case Scenario::BLOCK_TYPE::BREAKABLE:
				//rectangle.setFillColor(Color::Blue);
				anim1.setTextureRect(IntRect(64, 32, 32, 32));
				anim1.setPosition(i * cell_width, j * cell_width);
				window.draw(anim1);
				break;
			case Scenario::BLOCK_TYPE::UNBREAKABLE:
				//rectangle.setFillColor(Color::Black);
				anim1.setTextureRect(IntRect(64, 0, 32, 32));
				anim1.setPosition(i * cell_width, j * cell_width);
				window.draw(anim1);
				break;
			case Scenario::BLOCK_TYPE::GROUND:
				//rectangle.setFillColor(Color::Green);
				anim1.setTextureRect(IntRect(32, 0, 32, 32));
				anim1.setPosition(i * cell_width, j * cell_width);
				window.draw(anim1);
				break;
			case Scenario::BLOCK_TYPE::FIRED:
				
				anim2.setPosition(i * cell_width, j * cell_width);
				anim1.setTextureRect(IntRect(32, 0, 32, 32));
				anim1.setPosition(i * cell_width, j * cell_width);
				window.draw(anim1);
				window.draw(anim2);
				break;
			default:
				break;
			}
		}
	}
}

int Scenario::getColumns() const
{
	return columns;
}

int Scenario::getRows() const
{
	return rows;
}

int Scenario::getCellWidth() const
{
	return cell_width;
}

void Scenario::fireOff()
{
	timer = 2;
}

sf::Vector2f Scenario::getOriginPosition()
{
	return sf::Vector2f(35, 35);
}

void Scenario::update(float dt)
{
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++) {
			BLOCK_TYPE x = map[i][j];
			switch (x)
			{
			case Scenario::BLOCK_TYPE::FIRED:
	
				if (timer >= 1)
				{
					map[i][j] = Scenario::BLOCK_TYPE::GROUND;
				}
				break;
	
			default:
				break;
			}
	
		}
	}
	timer += dt;
}

sf::Vector2f Scenario::getPivotPosition()
{
	return sf::Vector2f();
}

