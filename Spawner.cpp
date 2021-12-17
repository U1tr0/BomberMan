#include "Spawner.h"
#include <vector>
using namespace std;
using namespace sf;
void Spawner::spawn()
{
	int n = 5;

	int counter = 0;
	vector<Vector2i> used_positions;

	for (int i = scene->getColumns()-1; i >=0; i--)
	{
		for (int j = scene->getRows() - 1; j >=0; j--)
		{
			if (scene->getBlock(i, j) == Scenario::BLOCK_TYPE::GROUND)
			{
				int chance = rand() % 100;

				for (auto p : used_positions)
				{
					if (p.x == i && p.y == j)
						continue;
				}

				if (chance < 10)
				{
					auto enemy = new Enemy(scene, engine);
					enemy->position.x = i * 32;
					enemy->position.y = j * 32;
					used_positions.push_back(Vector2i(i, j));
					engine->add(enemy);

					counter++;
					if (counter >= n)
						return;
				}
			}
		}
	}

}
