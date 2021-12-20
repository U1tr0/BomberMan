#include "Engine.h"
#include <SFML/Graphics.hpp>
#include "Scenario.h"
#include "Player.h"
#include "Spawner.h"
#include <Windows.h>
#include "Menu.h"
using namespace sf;

void Engine::run()
{
	Clock clock;
	clock.restart();
	Scenario map;
	Player pl(&map);
	Spawner spawner(&map, this, &pl);
	RenderWindow window(VideoMode(600, 480), "BomberMan");
	Menu menu(window, this);
	game_objects.push_back(&map);
	game_objects.push_back(&pl);
	damage_recievers.push_back(&pl);
	map.spawn = &spawner;
	map.generateMatrix();

	while (window.isOpen())
	{
		
		
		Time dt = clock.restart();
		float delta_time = dt.asSeconds();
		Event event;
		
		while (window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear(Color::Black);

		if (isPlaying) {
			if (Keyboard::isKeyPressed(Keyboard::W)) { pl.moveUp(); }
			else if (Keyboard::isKeyPressed(Keyboard::A)) { pl.moveLeft(); }
			else if (Keyboard::isKeyPressed(Keyboard::S)) { pl.moveDown(); }
			else if (Keyboard::isKeyPressed(Keyboard::D)) { pl.moveRight(); }
			if (Keyboard::isKeyPressed(Keyboard::Space)) { pl.placeBomb(); }
			if (Keyboard::isKeyPressed(Keyboard::G)) { map.generateMatrix(); spawner.spawn(); }
			update(delta_time);
			render(window);
		}
			
		menu.update(dt);				
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
