#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <LevelFactory.h>

#include <ResourceHolder.hpp>
#include <ResourceIdentifiers.hpp>
#include <StateStack.hpp>
#include <MusicPlayer.hpp>
#include <SoundPlayer.hpp>
#include <Settings.h>

class Application
{
private:

	Settings mSettings;

	sf::RenderWindow window;

	TextureHolder mTextures;
	FontHolder mFonts;
	LevelFactory mLevels;
	MusicPlayer mMusic;
	SoundPlayer mSounds;

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