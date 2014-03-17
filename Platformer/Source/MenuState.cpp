#include <MenuState.hpp>
#include <ResourceHolder.hpp>
#include <MusicPlayer.hpp>
#include <Button.hpp>
#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include <Utility.h>

MenuState::MenuState(StateStack& stack, Context context)
: State(stack, context)
{
	mBackgroundSprite.setTexture(context.textures->get(Textures::MenuBackground));

	scaleSpriteToFitWindow(mBackgroundSprite, *context.window);


	float y = 0.6f * context.window->getSize().y;
	float x = 0.5f * context.window->getSize().x;

	auto playButton = std::make_shared<GUI::Button>(context);
	playButton->setPosition(x - 255, y);
	playButton->setText("Play");
	playButton->setCallback([this]()
	{
		requestStackPop();
		requestStackPush(States::Game);
	});

	auto exitButton = std::make_shared<GUI::Button>(context);
	exitButton->setPosition(x + 15, y);
	exitButton->setText("Exit");
	exitButton->setCallback([this]()
	{
		requestStackPop();
	});

	auto toggleFsButton = std::make_shared<GUI::Button>(context);
	toggleFsButton->setPosition(x - 255, y + 100);
	toggleFsButton->setText("FullScreen");
	toggleFsButton->setCallback([this]()
	{
		toggleFullscreen();
	});

	mGUIContainer.pack(playButton);
	mGUIContainer.pack(exitButton);
	mGUIContainer.pack(toggleFsButton);

	context.music->play(Music::MenuTheme);
}

void MenuState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());

	window.draw(mBackgroundSprite);
	window.draw(mGUIContainer);
}

bool MenuState::update(sf::Time dt)
{
	mGUIContainer.update();
	return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
	mGUIContainer.handleEvent(event);
	return false;
}

void MenuState::toggleFullscreen()
{
	sf::RenderWindow& window = *getContext().window;

	std::vector<sf::VideoMode> resolution = sf::VideoMode::getFullscreenModes();

	sf::Vector2u max;
	max.x = resolution.front().width;
	max.y = resolution.front().height;

	sf::Vector2u currentSize = window.getSize();
	static sf::Vector2u prevSize = currentSize;

	if (currentSize.x == max.x && currentSize.y == max.y)
	{
		window.create(sf::VideoMode(prevSize.x, prevSize.y), "Platformer", sf::Style::Default, sf::ContextSettings(32, 24, 8, 4, 2));
	}
	else
	{
		window.create(sf::VideoMode(max.x, max.y), "Platformer", sf::Style::Fullscreen, sf::ContextSettings(32, 24, 8, 4, 2));
	}	
}