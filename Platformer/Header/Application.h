#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>

#include <ResourceHolder.hpp>
#include <ResourceIdentifiers.hpp>
#include <StateStack.hpp>

#include <MusicPlayer.hpp>
#include <SoundPlayer.hpp>
#include <LevelFactory.h>
#include <EffectFactory.h>
#include <Settings.h>
#include <SettingsParser.h>

class Application
{
public:
	Application(unsigned int width, unsigned int height);
	
	void						run();

private:

	void						getInput();
	void						update(sf::Time dt);
	void						render();

	void						updateStatistics(sf::Time dt);
	void						loadResources();
	void						close();

private:

	static const sf::Time		timePerFrame;

	sf::RenderWindow			window;
	Settings					mSettings;
	SettingsParser				mParser;

	TextureHolder				mTextures;
	FontHolder					mFonts;
	LevelFactory				mLevels;
	MusicPlayer					mMusic;
	SoundPlayer					mSounds;
	EffectFactory				mEffects;

	StateStack					mStateStack;

	sf::Text					mStatisticsText;
	sf::Time					mStatisticsUpdateTime;
	std::size_t					mStatisticsNumFrames;
};