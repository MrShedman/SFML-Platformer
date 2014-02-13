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
	sf::View view;

	TextureHolder mTextures;
	FontHolder mFonts;
	LevelHolder mLevels;

	StateStack mStateStack;

	void getInput();
	void update();
	void render();
	void clean();

public:

	void run();
	Application(unsigned int width, unsigned int height);
};