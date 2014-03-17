#include <Application.h>
#include <cmath>

#include <State.hpp>
#include <GameState.hpp>
#include <MenuState.hpp>
#include <PauseState.hpp>
#include <SettingsState.hpp>
#include <MusicPlayer.hpp>
#include <SoundPlayer.hpp>

#include <icon.c>

const sf::Time Application::timePerFrame = sf::seconds(1.f / 60.f);

Application::Application(unsigned int width, unsigned int height)
	:
	window(sf::VideoMode(width, height), "Platformer", sf::Style::Close, sf::ContextSettings(32, 24, 8, 4, 2)),
	mTextures(),
	mFonts(),
	mStateStack(State::Context(window, mTextures, mFonts, mLevels, mMusic, mSounds))
{
	window.setKeyRepeatEnabled(false);
	window.setVerticalSyncEnabled(true);

	window.setIcon(icon_image.width, icon_image.height, icon_image.pixel_data);

	loadResources();

	mStateStack.registerState<MenuState>(States::Menu);
	mStateStack.registerState<GameState>(States::Game);
	mStateStack.registerState<PauseState>(States::Pause);
	mStateStack.registerState<SettingsState>(States::Settings);

	mStateStack.pushState(States::Menu);
}

void Application::loadResources()
{
	mFonts.load(Fonts::Main, "Fonts/Sansation.otf");

	mTextures.load(Textures::MenuBackground, "Textures/MenuBackground.png");
	mTextures.load(Textures::TileMap, "Textures/terrain.png");
	mTextures.load(Textures::PlayerStanding, "Textures/standing.png");
	mTextures.load(Textures::PlayerRunning, "Textures/running.png");
	mTextures.load(Textures::PlayerJumping, "Textures/jumping.png");
	mTextures.load(Textures::PlayerFalling, "Textures/falling.png");
	mTextures.load(Textures::PlayerClimbing, "Textures/climbingvertical.png");
	mTextures.load(Textures::PlayerDying, "Textures/dying.png");
	mTextures.load(Textures::HealthBar, "Textures/hearts.png");

	mLevels.load(Levels::Level001, "Levels/001.txt");
	mLevels.load(Levels::Level002, "Levels/002.txt");
	mLevels.load(Levels::Level003, "Levels/003.txt");
}

void Application::getInput()
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}

		mStateStack.handleEvent(event);
	}
}

void Application::update(sf::Time dt)
{
	mStateStack.update(dt);
}

void Application::render()
{
	window.clear();

	mStateStack.draw();
	
	window.display();
}

void Application::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time dt;

	while (window.isOpen())
	{
		dt = clock.restart();
		timeSinceLastUpdate += dt;
	
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;

			getInput();
			update(timePerFrame);

			if (mStateStack.isEmpty())
			{
				window.close();
			}
		}

		render();		
	}
}