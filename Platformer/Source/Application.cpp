#include <Application.h>
#include <cmath>

#include <State.hpp>
#include <GameState.hpp>
#include <MenuState.hpp>
#include <PauseState.hpp>


Application::Application(unsigned int width, unsigned int height)
	:
	window(sf::VideoMode(width, height), "Platformer", sf::Style::Default, sf::ContextSettings(32, 24, 8, 4, 2)),
	mTextures(),
	mFonts(),
	mStateStack(State::Context(window, mTextures, mFonts, mLevels))
{
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);
	window.setVerticalSyncEnabled(true);

	mFonts.load(Fonts::Main, "Fonts/Sansation.ttf");

	mTextures.load(Textures::MenuBackground, "Textures/MenuBackground.png");
	mTextures.load(Textures::GameBackground, "Textures/GameBackground.png");
	mTextures.load(Textures::TileMap, "Textures/terrain.png");
	mTextures.load(Textures::PlayerStanding, "Textures/standing.png");
	mTextures.load(Textures::PlayerRunning, "Textures/running.png");
	mTextures.load(Textures::PlayerJumping, "Textures/jumping.png");
	mTextures.load(Textures::PlayerFalling, "Textures/falling.png");

	mLevels.load(Levels::Level001, "Levels/001.txt");
	mLevels.load(Levels::Level002, "Levels/002.txt");

	mStateStack.registerState<MenuState>(States::Menu);
	mStateStack.registerState<GameState>(States::Game);
	mStateStack.registerState<PauseState>(States::Pause);

	mStateStack.pushState(States::Menu);
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

void Application::update()
{
	mStateStack.update();

	if (mStateStack.isEmpty())
	{
		window.close();
	}
}

void Application::render()
{
	window.clear(sf::Color(153, 217, 234));

	mStateStack.draw();
	
	window.display();
}

void Application::clean()
{
	window.close();
}

void Application::run()
{
	while (window.isOpen())
	{
		getInput();
		update();
		render();		
	}

	clean();
}