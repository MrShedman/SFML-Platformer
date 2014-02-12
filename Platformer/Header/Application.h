#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <ResourceHolder.hpp>
#include <ResourceIdentifiers.hpp>
#include <StateStack.hpp>

class Application
{
private:

	sf::RenderWindow window;
	sf::View view;
	/*
	PlayerSprite player;

	TileMap map;

	CollisionSystem collision;

	sf::Texture texture;
	sf::Sprite background;
	*/
	TextureHolder mTextures;
	FontHolder mFonts;

	StateStack mStateStack;

	void getInput();
	void update();
	void render();
	void clean();

public:

	void run();
	Application(unsigned int width, unsigned int height);
};