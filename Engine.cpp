#include "Engine.h"
#include <SFML/Graphics.hpp>
#include "Scenario.h"
#include "Player.h"
#include "Spawner.h"
#include <Windows.h>
using namespace sf;

void Engine::run()
{


	int scrX = GetSystemMetrics(SM_CXSCREEN);
	int scrY = GetSystemMetrics(SM_CYSCREEN);
	Clock clock;
	clock.restart();
	Scenario map;
	Player pl(&map);
	Spawner spawner(&map, this);
	map.generateMatrix();
	RenderWindow window(VideoMode(scrX, scrY), "BomberMan");

	game_objects.push_back(&map);
	game_objects.push_back(&pl);
	damage_recievers.push_back(&pl);
	spawner.spawn();

	while (window.isOpen())
	{
		Time dt = clock.restart();
		float delta_time = dt.asSeconds();
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::W)) { pl.moveUp(); }
		else if (Keyboard::isKeyPressed(Keyboard::A)) { pl.moveLeft(); }
		else if (Keyboard::isKeyPressed(Keyboard::S)) { pl.moveDown(); }
		else if (Keyboard::isKeyPressed(Keyboard::D)) { pl.moveRight(); }
		if (Keyboard::isKeyPressed(Keyboard::Space)) { pl.placeBomb(); }

		window.clear(Color::White);

		update(delta_time);

		render(window);

		window.display();
	}

}

void Engine::add(GameObject *o)
{
	game_objects.push_back(o);
}

void Engine::remove(GameObject * go)
{
	for (auto it = game_objects.begin(); it != game_objects.end(); it++)
	{
		if ((*it) == go)
		{
			game_objects.erase(it);
			return;
		}
	}
}


void Engine::update(float dt)
{
	for (auto e : game_objects)
	{
		e->update(dt);
	}
}

void Engine::render(sf::RenderWindow &window)
{
	for (auto e : game_objects)
	{
		e->draw(window);
	}
}
