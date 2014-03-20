#include <LevelSelectionState.h>
#include <ResourceHolder.hpp>
#include <MusicPlayer.hpp>
#include <Button.hpp>
#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include <Utility.h>

LevelSelectionState::LevelSelectionState(StateStack& stack, Context context)
: State(stack, context)
{
	mBackgroundSprite.setTexture(context.textures->get(Textures::MenuBackground));

	scaleSpriteToFitWindow(mBackgroundSprite, *context.window);

	initializeButtons();

	context.music->play(Music::MenuTheme);
}

void LevelSelectionState::selectLevel(Levels::ID level)
{
	getContext().levels->load(level);
}

void LevelSelectionState::initializeButtons()
{
	Context context = getContext();

	mGUIContainer.clear();

	float y = 0.5f * context.window->getSize().y;
	float x = 0.5f * context.window->getSize().x;
	
	auto level1 = std::make_shared<GUI::Button>(context);
	level1->setSize(sf::Vector2f(70, 70));
	level1->setPosition(x - 120, y);
	level1->setText("1");
	level1->setCallback([this]()
	{
		requestStackPop();
		requestStackPush(States::Game);

		selectLevel(Levels::ID::Level001);		
	});

	auto level2 = std::make_shared<GUI::Button>(context);
	level2->setSize(sf::Vector2f(70, 70));
	level2->setPosition(x - 35, y);
	level2->setText("2");
	level2->setCallback([this]()
	{
		requestStackPop();
		requestStackPush(States::Game);

		selectLevel(Levels::ID::Level002);
	});

	auto level3 = std::make_shared<GUI::Button>(context);
	level3->setSize(sf::Vector2f(70, 70));
	level3->setPosition(x + 50, y);
	level3->setText("3");
	level3->setCallback([this]()
	{
		requestStackPop();
		requestStackPush(States::Game);

		selectLevel(Levels::ID::Level003);
	});

	auto backButton = std::make_shared<GUI::Button>(context);
	backButton->setPosition(x - 120, y + 90);
	backButton->setText("Back");
	backButton->setCallback([this]()
	{
		requestStackPop();
		requestStackPush(States::Menu);
	});

	mGUIContainer.pack(level1);
	mGUIContainer.pack(level2);
	mGUIContainer.pack(level3);
	mGUIContainer.pack(backButton);
}

void LevelSelectionState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());

	window.draw(mBackgroundSprite);
	window.draw(mGUIContainer);
}

bool LevelSelectionState::update(sf::Time dt)
{
	mGUIContainer.update();
	return true;
}

bool LevelSelectionState::handleEvent(const sf::Event& event)
{
	mGUIContainer.handleEvent(event);
	return false;
}