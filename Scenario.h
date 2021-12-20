#pragma once
#include <ctime>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include "BoxCollider.h"
const int rows = 15;
const int columns = 15;
using namespace sf;
class Scenario : public GameObject
{
public:
	enum class BLOCK_TYPE
	{
		GROUND,
		BREAKABLE,
		UNBREAKABLE,
		FIRED
	};

	Scenario();
	~Scenario();
	void generateMatrix();
	BLOCK_TYPE getBlock(int i, int j) const;
	void fireCell(int i, int j);
	BoxCollider* getCollidersMij(int i, int j) const;
	int getColumns() const;
	int getRows() const;
	int getCellWidth() const;
	void fireOff();
	sf::Vector2f getOriginPosition();
	virtual void draw(sf::RenderWindow &window) override;
	virtual void update(float dt) override;
	class Spawner* spawn;

private:
	int cell_width = 32;
	BLOCK_TYPE map[columns][rows];
	BoxCollider *colliders[columns][rows];
	float timer = 0.0f;
	// Унаследовано через GameObject
	virtual sf::Vector2f getPivotPosition() override;
};

