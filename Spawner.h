#pragma once
#include "Enemy.h"
#include "Scenario.h"
#include "GameObject.h"
#include "Engine.h"
class Spawner
{
public:
	inline Spawner(Scenario* scenario, Engine* engine, Player* player) : scene(scenario), engine(engine), player(player)
	{

	}
	void spawn();

private:
	Scenario *scene;
	Engine *engine;
	Player *player;

	std::vector<Enemy*> enemies;
	
};

