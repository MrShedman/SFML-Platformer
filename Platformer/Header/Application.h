#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Level.h>

#include <ResourceHolder.hpp>
#include <ResourceIdentifiers.hpp>
#include <StateStack.hpp>

class Application
{
private:

	sf::RenderWindow window;

	TextureHolder mTextures;
	FontHolder mFonts;
	LevelHolder mLevels;

	StateStack mStateStack;

	static const sf::Time timePerFrame;
	
	void loadResources();
	void getInput();
	void update(sf::Time dt);
	void render();

public:

	void run();
	Application(unsigned int width, unsigned int height);
};