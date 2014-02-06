#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <SpriteState.h>
#include <PlayerSprite.h>
#include <TileMap.h>
#include <ParticleSystem.h>
#include <CollisionSystem.h>
    
class Game
{
private:

	sf::RenderWindow window;
	sf::View view;
	
	PlayerSprite player;

	TileMap map;

	CollisionSystem collision;

	sf::Texture texture;
	sf::Sprite background;

	void getInput();
	void update();
	void render();
	void clean();

public:

	void run();
	Game(unsigned int width, unsigned int height);
};