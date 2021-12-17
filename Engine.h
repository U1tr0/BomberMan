#pragma once
#include "GameObject.h"
#include <vector>
#include "DamageReciever.h"
using namespace std;
class Engine
{
public:
	void run();
	void add(GameObject*);
	void remove(GameObject*);
private:
	vector<GameObject *> game_objects;
	vector<DamageReciever *> damage_recievers;
	void update(float dt);
	void render(sf::RenderWindow &window);
};

