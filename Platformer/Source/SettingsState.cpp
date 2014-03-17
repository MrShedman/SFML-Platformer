#include <SettingsState.hpp>
#include <Utility.h>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RenderWindow.hpp>


SettingsState::SettingsState(StateStack& stack, Context context)
: State(stack, context)
, mGUIContainer()
{
	mBackgroundSprite.setTexture(context.textures->get(Textures::MenuBackground));

	scaleSpriteToFitWindow(mBackgroundSprite, *context.window);

	initializeButtons();
}

void SettingsState::initializeButtons()
{
	mGUIContainer.clear();

	float y = 0.5f * getContext().window->getSize().y;
	float x = 0.5f * getContext().window->getSize().x;

	auto backButton = std::make_shared<GUI::Button>(getContext());
	backButton->setPosition(x - 120, y);
	backButton->setText("Back");
	backButton->setCallback([this]()
	{
		requestStateClear();
		requestStackPush(States::Menu);
	});

	auto toggleFsButton = std::make_shared<GUI::Button>(getContext());
	toggleFsButton->setPosition(x - 120, y + 90);
	toggleFsButton->setText("FullScreen");
	toggleFsButton->setCallback([this]()
	{
		toggleFullscreen();
	});

	mGUIContainer.pack(backButton);
	mGUIContainer.pack(toggleFsButton);
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

void SettingsState::toggleFullscreen()
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
		window.create(sf::VideoMode(prevSize.x, prevSize.y), "Platformer", sf::Style::Close, sf::ContextSettings(32, 24, 8, 4, 2));
	}
	else
	{
		window.create(sf::VideoMode(max.x, max.y), "Platformer", sf::Style::Fullscreen, sf::ContextSettings(32, 24, 8, 4, 2));
	}

	scaleSpriteToFitWindow(mBackgroundSprite, *getContext().window);

	initializeButtons();

	window.setVerticalSyncEnabled(true);
	window.setKeyRepeatEnabled(false);
}