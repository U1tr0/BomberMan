#include "Scenario.h"
Scenario::Scenario() {
}

Scenario::~Scenario() {

}

void Scenario::generateMatrix() {
	srand(time(NULL));

	for (int i = 0; i < columns; i++)
		for (int j = 0; j < rows; j++)
			colliders[i][j] = nullptr;

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
		map[position_x / cell_width][position_y / cell_width] = BLOCK_TYPE::FIRED;

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
	Texture tex;
	tex.loadFromFile("tileset.png");
	Sprite anim;
	anim.setTexture(tex);
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++) {
			BLOCK_TYPE x = map[i][j];
			switch (x)
			{
			case Scenario::BLOCK_TYPE::GROUND:
				//rectangle.setFillColor(Color::Green);
				anim.setTextureRect(IntRect(32, 0, 32, 32));
				anim.setPosition(i * cell_width, j * cell_width);
				window.draw(anim);
				break;
			case Scenario::BLOCK_TYPE::BREAKABLE:
				//rectangle.setFillColor(Color::Blue);
				anim.setTextureRect(IntRect(64, 32, 32, 32));
				anim.setPosition(i * cell_width, j * cell_width);
				window.draw(anim);
				break;
			case Scenario::BLOCK_TYPE::UNBREAKABLE:
				//rectangle.setFillColor(Color::Black);
				anim.setTextureRect(IntRect(64, 0, 32, 32));
				anim.setPosition(i * cell_width, j * cell_width);
				window.draw(anim);
				break;

			case Scenario::BLOCK_TYPE::FIRED:
				rectangle.setPosition(i * 32, j * 32);
				rectangle.setFillColor(Color::Yellow);
				window.draw(rectangle);
				break;
			default:
				break;
			}

			//rectangle.setPosition(i * cell_width, j * cell_width);
			//window.draw(rectangle);
			
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

