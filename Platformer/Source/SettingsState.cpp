#include <SettingsState.hpp>
#include <Utility.h>
#include <ResourceHolder.hpp>
#include <MusicPlayer.hpp>
#include <Slider.h>
#include <Toggle.h>

#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>

#include <icon.c>

SettingsState::SettingsState(StateStack& stack, Context context)
: State(stack, context)
, mGUIContainer()
{
	desiredMode.width = context.window->getSize().x;
	desiredMode.height = context.window->getSize().y;
	desiredMode.bitsPerPixel = 32;

	mBackgroundSprite.setTexture(context.textures->get(Textures::MenuBackground));

	scaleSpriteToFitWindow(mBackgroundSprite, *context.window);

	initializeButtons();
}

void SettingsState::initializeButtons()
{
	mGUIContainer.clear();

	float y = 0.5f * getContext().window->getSize().y;
	float x = 0.5f * getContext().window->getSize().x;

	std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();

	unsigned int bpp = modes.front().bitsPerPixel;
	
	auto end = std::remove_if(modes.begin(), modes.end(), [&](const sf::VideoMode &v)
	{
		return v.bitsPerPixel != bpp;
	});

	std::vector<std::string> resolutions;

	validModes.clear();
	resolutions.clear();

	for (auto i = modes.begin(); i != end; ++i)
	{
		validModes.push_back(sf::VideoMode(i->width, i->height, bpp));
		resolutions.push_back(toString(i->width) + "x" + toString(i->height));
	}
	std::reverse(resolutions.begin(), resolutions.end());
	std::reverse(validModes.begin(), validModes.end());

	std::vector<std::string> mVolume;
	std::vector<std::string> sVolume;
	mVolume.resize(101);
	sVolume.resize(101);
	for (int i = 0; i < 101; ++i)
	{
		mVolume[i] = "Music: " + toString(i) + "%";
		sVolume[i] = "SFX: " + toString(i) + "%";
	}
	mVolume[0] = "OFF";
	sVolume[0] = "OFF";
		
	auto musicVolume = std::make_shared<GUI::Slider>(getContext());
	musicVolume->setSize(sf::Vector2f(240, 70));
	musicVolume->setPosition(sf::Vector2f(x - 250, y));
	musicVolume->setPossibleValues(mVolume);
	musicVolume->setCurrentValue("Music: " + toString(getContext().music->getVolume()) + "%");
	musicVolume->setCallback([this](int volume)
	{
		getContext().music->setVolume(volume);
	});

	auto soundVolume = std::make_shared<GUI::Slider>(getContext());
	soundVolume->setSize(sf::Vector2f(240, 70));
	soundVolume->setPosition(sf::Vector2f(x + 10, y));
	soundVolume->setPossibleValues(sVolume);
	soundVolume->setCurrentValue("SFX: " + toString(getContext().sounds->getVolume()) + "%");
	soundVolume->setCallback([this](int volume)
	{
		getContext().sounds->setVolume(volume);
	});

	std::string currentRes = toString(getContext().window->getSize().x) + "x" + toString(getContext().window->getSize().y);

	auto resolution = std::make_shared<GUI::Slider>(getContext());
	resolution->setSize(sf::Vector2f(240, 70));
	resolution->setPosition(sf::Vector2f(x - 250, y + 90));
	resolution->setPossibleValues(resolutions);
	resolution->setCurrentValue(currentRes);
	resolution->setCallback([this](int id)
	{
		desiredMode = validModes[id];
	});

	auto apply = std::make_shared<GUI::Button>(getContext());
	apply->setPosition(x + 10, y + 90);
	apply->setText("Apply");
	apply->setCallback([this]()
	{
		applyChanges();
	});

	auto toggleVsyncButton = std::make_shared<GUI::Toggle>(getContext());
	toggleVsyncButton->setPosition(x - 250, y + 180);
	toggleVsyncButton->setText("vSync: OFF", "vSync: ON");
	toggleVsyncButton->setState(getContext().settings->vSync);
	toggleVsyncButton->setCallback([this](bool flag)
	{
		getContext().settings->vSync = flag;
	});

	auto toggleFS = std::make_shared<GUI::Toggle>(getContext());
	toggleFS->setPosition(x + 10, y + 180);
	toggleFS->setText("Windowed", "Full Screen");
	toggleFS->setState(getContext().settings->fullScreen);
	toggleFS->setCallback([this](bool flag)
	{
		getContext().settings->fullScreen = flag;
	});

	auto backButton = std::make_shared<GUI::Button>(getContext());
	backButton->setPosition(x - 120, y + 270);
	backButton->setText("Back");
	backButton->setCallback([this]()
	{
		requestStackPop();
		requestStackPush(States::Menu);
	});

	mGUIContainer.pack(musicVolume);
	mGUIContainer.pack(soundVolume);
	mGUIContainer.pack(resolution);
	mGUIContainer.pack(apply);
	mGUIContainer.pack(toggleFS);
	mGUIContainer.pack(toggleVsyncButton);
	mGUIContainer.pack(backButton);
}

void SettingsState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.draw(mBackgroundSprite);
	window.draw(mGUIContainer);
}

bool SettingsState::update(sf::Time)
{
	mGUIContainer.update();
	return true;
}

bool SettingsState::handleEvent(const sf::Event& event)
{
	mGUIContainer.handleEvent(event);
	return false;
}

void SettingsState::applyChanges()
{
	sf::RenderWindow& window = *getContext().window;
	
	sf::Uint32 mode = getContext().settings->fullScreen ? sf::Style::Fullscreen : sf::Style::Close;

	window.create(desiredMode, "Platformer", mode, sf::ContextSettings(32, 24, 8, 4, 2));

	scaleSpriteToFitWindow(mBackgroundSprite, *getContext().window);

	initializeButtons();

	window.setVerticalSyncEnabled(getContext().settings->vSync);
	window.setKeyRepeatEnabled(getContext().settings->keyRepeat);

	window.setIcon(icon_image.width, icon_image.height, icon_image.pixel_data);
}