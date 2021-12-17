#pragma once
#include "Enemy.h"
#include "Scenario.h"
#include "GameObject.h"
#include "Engine.h"
class Spawner
{
public:
	inline Spawner(Scenario* scenario, Engine* engine) : scene(scenario), engine(engine)
	{

	}
	void spawn();

private:
	Scenario *scene;
	Engine *engine;
	
};

