#include <Application.h>
#include <cmath>

#include <State.hpp>
#include <GameState.hpp>
#include <MenuState.hpp>
#include <PauseState.hpp>
#include <SettingsState.hpp>
#include <LevelSelectionState.h>
#include <MusicPlayer.hpp>
#include <SoundPlayer.hpp>

#include <icon.c>

const sf::Time Application::timePerFrame = sf::seconds(1.f / 60.f);

Application::Application(unsigned int width, unsigned int height)
	:
	mSettings(true, 0, false, false),
	mTextures(),
	mFonts(),
	mStateStack(State::Context(window, mTextures, mFonts, mLevels, mMusic, mSounds, mSettings, mEffects)),
	mStatisticsText(),
	mStatisticsUpdateTime(),
	mStatisticsNumFrames(0)
{
	if (!mParser.loadFile("settings.ini"))
	{
		std::cout << "Error loading settings file!" << std::endl;
	}

	int w = width;
	int h = height;
	mParser.get("width", w);
	mParser.get("height", h);
	mParser.get("fullscreen", mSettings.fullScreen);
	mParser.get("vSync", mSettings.vSync);
	int mVolume = 100;
	int sVolume = 100;
	mParser.get("mvolume", mVolume);
	mParser.get("svolume", sVolume);
	mMusic.setVolume(mVolume);
	mSounds.setVolume(sVolume);

	sf::VideoMode mode(w, h, sf::VideoMode::getFullscreenModes()[0].bitsPerPixel);

	if (!mode.isValid())
	{
		std::vector<sf::VideoMode> validModes = getValidVideoModes();
		
		auto low = std::lower_bound(validModes.begin(), validModes.end(), mode);

		low--;

		mode.bitsPerPixel = low->bitsPerPixel;
		mode.width = low->width;
		mode.height = low->height;
	}

	sf::Uint32 style = mSettings.fullScreen ? sf::Style::Fullscreen : sf::Style::Close;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	window.create(mode, "Platformer", style, settings);

	window.setKeyRepeatEnabled(mSettings.keyRepeat);
	window.setVerticalSyncEnabled(mSettings.vSync);

	window.setIcon(icon_image.width, icon_image.height, icon_image.pixel_data);

	loadResources();

	mStatisticsText.setFont(mFonts.get(Fonts::Main));
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(30u);
	mStatisticsText.setColor(sf::Color::Yellow);

	mStateStack.registerState<MenuState>(States::Menu);
	mStateStack.registerState<LevelSelectionState>(States::LevelSelection);
	mStateStack.registerState<SettingsState>(States::Settings);
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
			close();
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

	window.setView(window.getDefaultView());
	window.draw(mStatisticsText);
	
	window.display();
}

void Application::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (window.isOpen())
	{
		sf::Time dt;
		dt = clock.restart();
		timeSinceLastUpdate += dt;
	
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;

			getInput();
			update(timePerFrame);

			if (mStateStack.isEmpty())
			{
				close();
			}
		}

		updateStatistics(dt);
		render();		
	}
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
}

void Application::updateStatistics(sf::Time dt)
{
	mStatisticsUpdateTime += dt;
	mStatisticsNumFrames += 1;

	if (mStatisticsUpdateTime >= sf::seconds(1.f))
	{
		mStatisticsText.setString("FPS: " + toString(mStatisticsNumFrames));

		mStatisticsUpdateTime -= sf::seconds(1.f);
		mStatisticsNumFrames = 0;
	}
}

void Application::close()
{
	mParser.set("width", static_cast<int>(window.getSize().x));
	mParser.set("height", static_cast<int>(window.getSize().y));
	mParser.set("fullscreen", mSettings.fullScreen);
	mParser.set("vSync", mSettings.vSync);
	mParser.set("mvolume", mMusic.getVolume());
	mParser.set("svolume", mSounds.getVolume());

	window.close();
}